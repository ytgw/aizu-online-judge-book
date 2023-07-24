#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
#include<numeric>


using Cycle = std::vector<int>;


std::vector<Cycle> getCycles(const int inputArray[], const int arraySize, const int maxElement) {
    bool isChecked[arraySize];
    int sortedArray[arraySize];
    for (int i=0; i<arraySize; i++) {
        sortedArray[i] = inputArray[i];
        isChecked[i] = false;
    }
    std::sort(sortedArray, sortedArray + arraySize);

    int sortedIdx[maxElement];
    for (int i=0; i<arraySize; i++) sortedIdx[sortedArray[i]] = i;

    std::vector<Cycle> cycles;
    for (int i=0; i<arraySize; i++) {
        if (isChecked[i]) continue;
        Cycle cycle;
        int cursor = i;
        while (!isChecked[cursor]) {
            isChecked[cursor] = true;
            int v = inputArray[cursor];
            cycle.push_back(v);
            cursor = sortedIdx[v];
        }
        cycles.push_back(cycle);
    }

    return cycles;
}


int solve(const int inputArray[], const int arraySize) {
    std::pair<const int*, const int*> minmax = std::minmax_element(inputArray, inputArray + arraySize);
    const int minElement = *minmax.first;
    const int maxElement = *minmax.second;

    std::vector<Cycle> cycles = getCycles(inputArray, arraySize, maxElement);

    int cost = 0;
    for (int i=0; i<cycles.size(); i++) {
        Cycle cycle = cycles[i];
        const int totalCycleWeight = std::accumulate(cycle.begin(), cycle.end(), 0);
        const int minCycleWeight = *std::min_element(cycle.begin(), cycle.end());
        const int cycleSize = cycle.size();

        int costInCycle = totalCycleWeight + (cycleSize - 2) * minCycleWeight;
        int costOutOfCycle = totalCycleWeight + minCycleWeight + (cycleSize + 1) * minElement;
        cost += std::min(costInCycle, costOutOfCycle);
    }
    return cost;
}


int main() {
    // 配列のサイズの取得
    int arraySize;
    std::cin >> arraySize;
    if (!(1 <= arraySize && arraySize <= 1000)) {
        std::cerr << "arraySize is invalid" << std::endl;
        exit(EXIT_FAILURE);
    }

    // 配列の取得
    int array[arraySize];
    for (int i=0; i<arraySize; i++) {
        std::cin >> array[i];
        if (!(0 <= array[i] && array[i] <= std::pow(10,4))) {
            std::cerr << "array element is invalid" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    // コスト算出
    const int minimumCost = solve(array, arraySize);

    // 結果表示
    std::cout << minimumCost << std::endl;

    return 0;
}
