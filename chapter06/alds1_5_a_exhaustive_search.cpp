#include<iostream>


bool isAbleToSolve(const int array[], const int arraySize, const int idx, const int m) {
    if (m == 0) return true;
    if (idx >= arraySize) return false;

    const bool whenToUseIdx = isAbleToSolve(array, arraySize, idx+1, m-array[idx]);
    const bool whenNotToUseIdx = isAbleToSolve(array, arraySize, idx+1, m);
    return whenToUseIdx || whenNotToUseIdx;
}

int main() {
    // 標準入力からのデータ取得
    int n;
    std::cin >> n;
    if (!(n <= 20)) {
        std::cerr << "n is invalid." << std::endl;
        exit(EXIT_FAILURE);
    }

    int a[n];
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        if (!(1 <= a[i] && a[i] <= 2000)) {
            std::cerr << "a[i] is invalid." << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    int q;
    std::cin >> q;
    if (!(q <= 200)) {
        std::cerr << "q is invalid." << std::endl;
        exit(EXIT_FAILURE);
    }

    int m[q];
    for (int i = 0; i < q; i++) {
        std::cin >> m[i];
        if (!(1 <= m[i] && m[i] <= 2000)) {
            std::cerr << "m[i] is invalid." << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    // 結果
    for (int i = 0; i < q; i++) {
        const int idx = 0;
        if (isAbleToSolve(a, n, idx, m[i])) {
            std::cout << "yes" << std::endl;
        } else {
            std::cout << "no" << std::endl;
        }
    }

    return 0;
}
