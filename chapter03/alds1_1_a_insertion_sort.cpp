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


void insertionSort(int array[], const int arraySize) {
    // 挿入ソート
    // 引数の配列は変わる
    for (int i=1; i<arraySize; i++) {
        int v = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > v) {
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = v;

        // 結果表示
        printArray(array, arraySize);
    }
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

    // 初期状態表示
    printArray(A, N);

    // ソート
    insertionSort(A, N);

    return 0;
}
