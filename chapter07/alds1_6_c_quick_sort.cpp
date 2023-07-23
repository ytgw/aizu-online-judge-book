#include<iostream>
#include<cmath>


class Card {
public:
    // デフォルトコンストラクタ
    // 配列宣言時など引数を初期化時に与えられない場合に利用
    Card() : m_suit('?'), m_value(0) {}

    // コンストラクタ
    Card(const char suit, const int value) : m_suit(suit), m_value(value) {
        if (!(suit == 'S' || suit == 'H' || suit == 'C' || suit == 'D')){
            std::cerr << "suit " << suit << " is invalid" << std::endl;
            exit(1);
        }
        if (!(1 <= value && value <= std::pow(10,9))) {
            std::cerr << "value " << value << " is invalid" << std::endl;
            exit(1);
        }
    }

    int getValue() const {
        return m_value;
    }

    char getSuit() const {
        return m_suit;
    }

    void print() const {
        std::cout << m_suit << " " << m_value << std::endl;
    }

private:
    char m_suit;
    int m_value;
};


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


int partition(Card cards[], const int p, const int r) {
    // cards[r].getValue()より小さい領域と、大きい領域に分ける
    // 返り値は分割したインデックス

    const int x = cards[r].getValue();
    int i = p - 1;
    for (int j=p; j<r; j++) {
        if (cards[j].getValue() <= x) {
            i++;
            std::swap(cards[i], cards[j]);
        }
    }
    std::swap(cards[i+1], cards[r]);

    return i+1;
}


void quickSort(Card cards[], const int p, const int r) {
    // クイックソート
    // 引数の配列は実行後に変更される

    if (p < r) {
        const int q = partition(cards, p, r);
        quickSort(cards, p, q - 1);
        quickSort(cards, q + 1, r);
    }
}


int main() {
    // 配列のサイズの取得
    int cardNum;
    std::cin >> cardNum;
    if (!(1 <= cardNum && cardNum <= std::pow(10,5))) {
        std::cerr << "cardNum is invalid." << std::endl;
        exit(1);
    }

    // 配列の取得
    Card sortedCards[cardNum];
    Card initialCards[cardNum];
    for (int i=0; i<cardNum; i++) {
        char suit;
        int value;
        std::cin >> suit >> value;
        sortedCards[i] = Card(suit, value);
        initialCards[i] = Card(suit, value);
    }

    // ソート
    quickSort(sortedCards, 0, cardNum-1);

    // 結果表示
    if (isStable(initialCards, sortedCards, cardNum)) {
        std::cout << "Stable" << std::endl;
    } else {
        std::cout << "Not stable" << std::endl;
    }

    for (int i=0; i<cardNum; i++) {
        sortedCards[i].print();
    }

    return 0;
}
