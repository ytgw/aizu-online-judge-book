#include <iostream>
#include <algorithm>
#include <string>


struct Card {
public:
    // デフォルトコンストラクタ
    // 配列宣言時など引数を初期化時に与えられない場合に利用
    Card() : m_suit('?'), m_value(0) {}

    // コンストラクタ
    Card(const std::string str) {
        const char suit = str[0];
        const int value = std::stoi(str.substr(1));

        if (!(suit == 'S' || suit == 'H' || suit == 'C' || suit == 'D')){
            std::cerr << "suit " << suit << " is invalid" << std::endl;
            exit(1);
        }
        if (!(1 <= value && value <= 9)) {
            std::cerr << "value " << value << " is invalid" << std::endl;
            exit(1);
        }

        this->m_suit = suit;
        this->m_value = value;
    }

    int getValue() const {
        return m_value;
    }

    char getSuit() const {
        return m_suit;
    }

    std::string toString() const {
        return m_suit + std::to_string(m_value);
    }

private:
    char m_suit;
    int m_value;
};


void printCards(const Card cards[], const int cardNum) {
    std::cout << cards[0].toString();
    for (int i=1; i<cardNum; i++) {
        std::cout << " " << cards[i].toString();
    }
    std::cout << std::endl;
}


int bubbleSort(Card cards[], const int cardNum) {
    // バブルソート
    // 引数の配列は実行後に変更される
    // 返り値は交換回数

    int swapCount = 0;
    for (int i=0; i<=cardNum-1; i++) {
        for (int j=cardNum-1; j>=i+1; j--) {
            if (cards[j].getValue() < cards[j-1].getValue()) {
                std::swap(cards[j], cards[j-1]);
                swapCount += 1;
            }
        }
    }

    return swapCount;
}


int selectionSort(Card cards[], const int cardNum) {
    // 選択ソート
    // 引数の配列は実行後に変更される
    // 返り値は交換回数

    int swapCount = 0;
    for (int i=0; i<=cardNum-1; i++) {
        int minIdx = i;
        for (int j=i; j<=cardNum-1; j++) {
            if (cards[j].getValue() < cards[minIdx].getValue()) {
                minIdx = j;
            }
        }

        if (i != minIdx) {
            std::swap(cards[i], cards[minIdx]);
            swapCount++;
        }
    }

    return swapCount;
}


std::string getSuits(const int value, const Card cards[], const int cardNum) {
    std::string suits = "";
    for (int i=0; i<cardNum; i++) {
        if (cards[i].getValue() == value) {
            suits += cards[i].getSuit();
        }
    }
    return suits;
}


bool isStable(const Card initialCards[], const Card sortedCards[], const int cardNum) {
    // ソート前後で安定にソートされている場合にtrueを返す

    for (int i=0; i<cardNum; i++) {
        const int value = sortedCards[i].getValue();

        const std::string initialSuits = getSuits(value, initialCards, cardNum);
        const std::string sortedSuits = getSuits(value, sortedCards, cardNum);

        if (initialSuits != sortedSuits) {
            return false;
        }
    }
    return true;
}


bool isStableWithStableSortedCards(const Card stableSortedCards[], const Card sortedCards[], const int cardNum) {
    // ソート前後で安定にソートされている場合にtrueを返す
    // 安定ソートされたソート結果を使うことで高速化する

    for (int i=0; i<cardNum; i++) {
        if (stableSortedCards[i].getSuit() != sortedCards[i].getSuit()) {
            return false;
        }
    }
    return true;
}


int main() {
    // 配列のサイズの取得
    int N;
    std::cin >> N;
    if (!(1 <= N && N <= 36)) {
        std::cerr << "array_length is invalid" << std::endl;
        exit(1);
    }

    // 配列の取得
    Card initialCards[N];
    Card bubbleSortCards[N];
    Card selectionSortCards[N];
    for (int i=0; i<N; i++) {
        std::string cardStr;
        std::cin >> cardStr;
        initialCards[i] = Card(cardStr);
        bubbleSortCards[i] = Card(cardStr);
        selectionSortCards[i] = Card(cardStr);
    }

    // ソート
    bubbleSort(bubbleSortCards, N);
    selectionSort(selectionSortCards, N);

    // 結果表示
    printCards(bubbleSortCards, N);
    std::cout << "Stable" << std::endl;

    printCards(selectionSortCards, N);
    if (isStableWithStableSortedCards(bubbleSortCards, selectionSortCards, N)) {
        std::cout << "Stable" << std::endl;
    } else {
        std::cout << "Not stable" << std::endl;
    }

    return 0;
}
