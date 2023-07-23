#include<iostream>
#include<cmath>


void printArray(const int array[], const int arraySize) {
    // 配列の表示
    std::cout << array[0];
    for (int i=1; i<arraySize; i++) {
        std::cout << " " << array[i];
    }
    std::cout << std::endl;
}


void countingSort(const int inputArray[], int outputArray[], const int arraySize, const int maxElement) {
    int counts[maxElement+1];
    for (int i=0; i<=maxElement; i++) counts[i] = 0;

    // countsに出現回数を記録
    for (int j=0; j<arraySize; j++) counts[inputArray[j]]++;

    // counts[i]にi以下の数の出現数を入れる
    for (int i=1; i<=maxElement; i++) counts[i] += counts[i-1];

    for (int j=arraySize-1; j>=0; j--) {
        outputArray[counts[inputArray[j]]-1] = inputArray[j];
        counts[inputArray[j]]--;
    }
}


int main() {
    // 配列のサイズの取得
    int arraySize;
    std::cin >> arraySize;
    if (!(1 <= arraySize && arraySize <= 2 * std::pow(10,6))) {
        std::cerr << "arraySize is invalid" << std::endl;
        exit(EXIT_FAILURE);
    }

    // 配列の取得
    int inputArray[arraySize], outputArray[arraySize];
    const int maxElement = std::pow(10,4);
    for (int i=0; i<arraySize; i++) {
        std::cin >> inputArray[i];
        if (!(0 <= inputArray[i] && inputArray[i] <= maxElement)) {
            std::cerr << "array element is invalid" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    // ソート
    countingSort(inputArray, outputArray, arraySize, maxElement);

    // 結果表示
    printArray(outputArray, arraySize);

    return 0;
}
