#include<iostream>
#include<cmath>


void printArrayWithPartition(const int array[], const int arraySize, const int partitionIdx) {
    // 配列の表示
    std::cout << array[0];
    for (int i=1; i<arraySize; i++) {
        if (i == partitionIdx) {
            std::cout << " [" << array[i] << "]";
        } else {
            std::cout << " " << array[i];
        }
    }
    std::cout << std::endl;
}


int partition(int array[], const int p, const int r) {
    const int x = array[r];
    int i = p - 1;
    for (int j=p; j<r; j++) {
        if (array[j] <= x) {
            i++;
            std::swap(array[i], array[j]);
        }
    }
    std::swap(array[i+1], array[r]);

    return i+1;
}


int main() {
    // 配列のサイズの取得
    int arraySize;
    std::cin >> arraySize;
    if (!(1 <= arraySize && arraySize <= 5 * std::pow(10,5))) {
        std::cerr << "arraySize is invalid" << std::endl;
        exit(1);
    }

    // 配列の取得
    int array[arraySize];
    for (int i=0; i<arraySize; i++) {
        std::cin >> array[i];
        if (!(0 <= array[i] && array[i] <= std::pow(10,9))) {
            std::cerr << "array element is invalid" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    // パーティション
    const int partitionIdx = partition(array, 0, arraySize-1);

    // 結果表示
    printArrayWithPartition(array, arraySize, partitionIdx);

    return 0;
}
