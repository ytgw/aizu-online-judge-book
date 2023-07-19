#include <iostream>
#include <algorithm>


void printArray(const int array[], const int arraySize) {
    // 配列の表示
    std::cout << array[0];
    for (int i=1; i<arraySize; i++) {
        std::cout << " " << array[i];
    }
    std::cout << std::endl;
}


int bubbleSort(int array[], const int arraySize) {
    // バブルソート
    // 引数の配列は実行後に変更される
    // 返り値は交換回数
    int flag = true;
    int swapCount = 0;
    while (flag) {
        flag = false;
        for (int j=arraySize-1; j>=1; j--) {
            if (array[j] < array[j-1]) {
                std::swap(array[j], array[j-1]);
                swapCount += 1;
                flag = true;
            }
        }
    }
    return swapCount;
}


int main() {
    // 配列のサイズの取得
    int N;
    std::cin >> N;
    if (!(1 <= N && N <= 100)) {
        std::cerr << "array_length is invalid" << std::endl;
        exit(1);
    }

    // 配列の取得
    int A[N];
    for (int i=0; i<N; i++) {
        std::cin >> A[i];
        if (!(0 <= A[i] && A[i] <= 1000)) {
            std::cerr << "array element is invalid" << std::endl;
            exit(1);
        }
    }

    // ソート
    const int swapCount = bubbleSort(A, N);

    // 結果表示
    printArray(A, N);
    std::cout << swapCount << std::endl;

    return 0;
}
