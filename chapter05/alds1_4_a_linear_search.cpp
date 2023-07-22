#include<iostream>


int main() {
    // 標準入力からのデータ取得
    int n;
    std::cin >> n;
    if (!(n <= 10000)) {
        std::cerr << "n is invalid.";
        exit(EXIT_FAILURE);
    }

    // 高速化のための番兵用に配列サイズを増やす
    int s[n+1];
    for (int i=0; i<n; i++) {
        std::cin >> s[i];
        if (!(0 <= s[i] && s[i] <= 1000000000)) {
            std::cerr << "s[i] is invalid.";
            exit(EXIT_FAILURE);
        }
    }

    int q;
    std::cin >> q;
    if (!(q <= 500)) {
        std::cerr << "q is invalid.";
        exit(EXIT_FAILURE);
    }

    int t[q];
    for (int i=0; i<q; i++) {
        std::cin >> t[i];
        if (!(0 <= t[i] && t[i] <= 1000000000)) {
            std::cerr << "t[i] is invalid.";
            exit(EXIT_FAILURE);
        }
    }

    // 結果算出
    int count = 0;
    for (int ti=0; ti<q; ti++) {
        // 番兵を使うことで比較処理を減らす
        s[n] = t[ti];

        int si = 0;
        while (s[si] != t[ti]) si++;

        if (si < n) count++;
    }

    // 結果表示
    std::cout << count << std::endl;

    return 0;
}
