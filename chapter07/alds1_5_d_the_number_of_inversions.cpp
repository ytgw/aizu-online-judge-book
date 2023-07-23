#include<iostream>
#include<cmath>


long long merge(int array[], const int left, const int mid, const int right) {
    // マージソートのユーティリティ
    // 引数の配列は変わる
    // 返り値は反点数

    const int n1 = mid - left, n2 = right - mid;
    int leftArray[n1 + 1], rightArray[n2 + 1];
    for (int i=0; i<n1; i++) leftArray[i] = array[left + i];
    for (int i=0; i<n2; i++) rightArray[i] = array[mid + i];

    const int infinity = int(std::pow(10,10));
    leftArray[n1] = infinity;
    rightArray[n2] = infinity;

    int i = 0, j = 0;
    long long inversionNum = 0;
    for (int k=left; k<right; k++) {
        if (leftArray[i] <= rightArray[j]) {
            array[k] = leftArray[i];
            i++;
        } else {
            array[k] = rightArray[j];
            inversionNum += n1 - i;
            j++;
        }
    }
    return inversionNum;
}


long long mergeSort(int array[], const int left, const int right) {
    // マージソート
    // 引数の配列は変わる
    // 返り値は反点数

    long long inversionNum = 0;
    if (left + 1 < right) {
        int mid = (left + right) / 2;
        inversionNum += mergeSort(array, left, mid);
        inversionNum += mergeSort(array, mid, right);
        inversionNum += merge(array, left, mid, right);
    }
    return inversionNum;
}


int main() {
    // 配列のサイズの取得
    int arraySize;
    std::cin >> arraySize;
    if (!(1 <= arraySize && arraySize <= 2 * std::pow(10,5))) {
        std::cerr << "arraySize is invalid" << std::endl;
        exit(EXIT_FAILURE);
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

    // ソート
    const long long inversionNum = mergeSort(array, 0, arraySize);

    // 結果表示
    std::cout << inversionNum << std::endl;

    return 0;
}
