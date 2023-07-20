#include <iostream>
#include <algorithm>
#include <cmath>


void printArray(const int array[], const int arraySize) {
    // 配列の表示
    std::cout << array[0];
    for (int i=1; i<arraySize; i++) {
        std::cout << " " << array[i];
    }
    std::cout << std::endl;
}


int insertionSort(int A[], const int n, const int g) {
    // 間隔gの挿入ソート
    // 引数の配列は変わる
    // 返り値は交換回数

    int cnt = 0;
    for (int i=g; i<=n-1; i++) {
        int v = A[i];
        int j = i - g;
        while (j >= 0 && A[j] > v) {
            A[j+g] = A[j];
            j -= g;
            cnt++;
        }
        A[j+g] = v;
    }

    return cnt;
}


int shellSort(int A[], const int n) {
    // シェルソート
    // 引数の配列は変わる
    // 返り値は交換回数

    int totalCnt = 0;
    int m = 0;
    int reverseG[n];

    // パラメータの設定
    reverseG[0] = 1;
    m = 1;
    while (true) {
        int value = 3 * reverseG[m-1] + 1;
        if (value > n) break;
        reverseG[m] = value;
        m++;
    }

    int G[m];
    for (int i=0; i<=m-1; i++) {
        G[i] = reverseG[m - 1 - i];
    }

    // ソート
    for (int i=0; i<=m-1; i++) {
        int cnt = insertionSort(A, n, G[i]);
        totalCnt += cnt;
    }

    // パラメータ表示
    std::cout << m << std::endl;
    printArray(G, m);

    return totalCnt;
}


int main() {
    // 配列のサイズの取得
    int N;
    std::cin >> N;
    if (!(1 <= N && N <= 1000000)) {
        std::cerr << "array_length is invalid" << std::endl;
        exit(1);
    }

    // 配列の取得
    int A[N];
    for (int i=0; i<N; i++) {
        std::cin >> A[i];
        if (!(0 <= A[i] && A[i] <= 1000000000)) {
            std::cerr << "array element is invalid" << std::endl;
            exit(1);
        }
    }

    // ソート
    const int cnt = shellSort(A, N);

    // 結果表示
    std::cout << cnt << std::endl;
    for (int i=0; i<N; i++) {
        std::cout << A[i] << std::endl;
    }

    return 0;
}
