#include<iostream>


int main() {
    // 標準入力からのデータ取得
    int n;
    std::cin >> n;
    if (!(n <= 10000)) {
        std::cerr << "n is invalid.";
        exit(EXIT_FAILURE);
    }

    int s[n];
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
        for (int si=0; si<n; si++) {
            if (s[si] == t[ti]) {
                count++;
                break;
            }
        }
    }

    // 結果表示
    std::cout << count << std::endl;

    return 0;
}
