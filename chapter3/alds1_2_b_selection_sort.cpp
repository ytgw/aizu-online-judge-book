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


int selectionSort(int array[], const int arraySize) {
    // 選択ソート
    // 引数の配列は実行後に変更される
    // 返り値は交換回数

    int swapCount = 0;
    for (int i=0; i<=arraySize-1; i++) {
        int minIdx = i;
        for (int j=i; j<=arraySize-1; j++) {
            if (array[j] < array[minIdx]) {
                minIdx = j;
            }
        }

        if (i != minIdx) {
            std::swap(array[i], array[minIdx]);
            swapCount++;
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
    const int swapCount = selectionSort(A, N);

    // 結果表示
    printArray(A, N);
    std::cout << swapCount << std::endl;

    return 0;
}
