#include<iostream>
#include<cmath>


bool binarySearch(const int sortedArray[], const int arraySize, const int key) {
    // keyが含まれているときtrueを返す。
    int leftIdx = 0;
    int rightIdx = arraySize;
    while (leftIdx < rightIdx) {
        int middleIdx = (leftIdx + rightIdx) / 2;
        int num = sortedArray[middleIdx];
        if (num == key) {
            return true;
        } else if (num < key) {
            leftIdx = middleIdx + 1;
        } else {
            rightIdx = middleIdx;
        }
    }
    return false;
}


int main() {
    // 標準入力からのデータ取得
    int n;
    std::cin >> n;
    if (!(n <= std::pow(10, 9))) {
        std::cerr << "n is invalid.";
        exit(EXIT_FAILURE);
    }

    // 高速化のための番兵用に配列サイズを増やす
    int s[n];
    for (int i=0; i<n; i++) {
        std::cin >> s[i];
        if (!(0 <= s[i] && s[i] <= std::pow(10, 9))) {
            std::cerr << "s[i] is invalid.";
            exit(EXIT_FAILURE);
        }
    }

    int q;
    std::cin >> q;
    if (!(q <= 50000)) {
        std::cerr << "q is invalid.";
        exit(EXIT_FAILURE);
    }

    int t[q];
    for (int i=0; i<q; i++) {
        std::cin >> t[i];
        if (!(0 <= t[i] && t[i] <= std::pow(10, 9))) {
            std::cerr << "t[i] is invalid.";
            exit(EXIT_FAILURE);
        }
    }

    // 結果算出
    int count = 0;
    for (int ti=0; ti<q; ti++) {
        if (binarySearch(s, n, t[ti])) {
            count++;
        }
    }

    // 結果表示
    std::cout << count << std::endl;

    return 0;
}
