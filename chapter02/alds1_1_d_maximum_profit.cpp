#include <iostream>
#include <algorithm>

int main() {
    // 価格配列のサイズの取得
    int n;
    std::cin >> n;
    if (n < 2 || 200000 < n) {
        std::cerr << "n is invalid" << std::endl;
        exit(1);
    }

    // 価格配列の取得
    int R[n];
    for (int i=0; i<n; i++) {
        std::cin >> R[i];
        if (R[i] < 1 || 1000000000 < R[i]) {
            std::cerr << "Rt is invalid" << std::endl;
            exit(1);
        }
    }

    // 利益計算
    int min_value = std::min(R[0], R[1]);
    int max_profit = R[1] - R[0];
    for (int i=2; i<n; i++) {
        max_profit = std::max(max_profit, R[i] - min_value);
        min_value = std::min(min_value, R[i]);
    }

    // 結果出力
    std::cout << max_profit << std::endl;
    return 0;
}
