#include<iostream>
#include<cmath>


bool isLoadable(const int weights[], const int maxWeightNum, const int truckNum, const int maxLoad) {
    int loadableWeightNumber = 0;

    for (int truckIdx=0; truckIdx<truckNum; truckIdx++) {
        int totalWeight = 0;
        while (loadableWeightNumber < maxWeightNum) {
            int newWeight = totalWeight + weights[loadableWeightNumber];
            if (newWeight > maxLoad) {
                break;
            }
            totalWeight = newWeight;
            loadableWeightNumber++;
        }
    }

    return loadableWeightNumber >= maxWeightNum;
}


int calcMinMaxLoad(const int weights[], const int maxWeightNum, const int truckNum, const int searchedMinLoad, const int searchedMaxLoad) {
    int left = searchedMinLoad;
    int right = searchedMaxLoad;
    while (left < right) {
        const int middle = (left + right) / 2;
        if (isLoadable(weights, maxWeightNum, truckNum, middle)) {
            right = middle;
        } else {
            left = middle + 1;
        }
    }

    return right;
}


int main() {
    // 標準入力からのデータ取得
    int maxWeightNum, truckNum;
    std::cin >> maxWeightNum >> truckNum;
    if (!(1 <= maxWeightNum && maxWeightNum <= std::pow(10, 5))) {
        std::cerr << "maxWeightNum is invalid.";
        exit(EXIT_FAILURE);
    }
    if (!(1 <= truckNum && truckNum <= std::pow(10, 5))) {
        std::cerr << "truckNum is invalid.";
        exit(EXIT_FAILURE);
    }

    int weights[maxWeightNum];
    for (int i=0; i<maxWeightNum; i++) {
        std::cin >> weights[i];
        if (!(1 <= weights[i] && weights[i] <= std::pow(10, 4))) {
            std::cerr << "weights[i] is invalid.";
            exit(EXIT_FAILURE);
        }
    }

    // 計算
    const int searchMin = 1, searchMax = maxWeightNum * std::pow(10, 4);
    const int maxLoad = calcMinMaxLoad(weights, maxWeightNum, truckNum, searchMin, searchMax);

    // 結果出力
    std::cout << maxLoad << std::endl;

    return 0;
}
