#include<iostream>
#include<cmath>
#include<cassert>


void maxHeapify(int heapKeys[], const int id, const int heapSize) {
    const int leftId = 2 * id;
    const int rightId = 2 * id + 1;

    // 左右の子と字分のうち最大のノードを選択
    int largestId = id;
    if (leftId <= heapSize && heapKeys[leftId] > heapKeys[largestId]) {
        largestId = leftId;
    }
    if (rightId <= heapSize && heapKeys[rightId] > heapKeys[largestId]) {
        largestId = rightId;
    }

    if (largestId != id) {
        std::swap(heapKeys[id], heapKeys[largestId]);
        maxHeapify(heapKeys, largestId, heapSize);
    }
}


void buildMaxHeap(int heapKeys[], const int heapSize) {
    for (int id = heapSize / 2; id >= 1; id--) {
        maxHeapify(heapKeys, id, heapSize);
    }
}


int main() {
    int heapSize;
    std::cin >> heapSize;
    assert(1 <= heapSize && heapSize <= 5 * std::pow(10,5));

    int heapKeys[heapSize + 1];  // 1オリジンの配列とする
    for (int i=1; i<=heapSize; i++) {
        std::cin >> heapKeys[i];
        assert(-2 * std::pow(10,9) <= heapKeys[i] and heapKeys[i] <= 2 * std::pow(10,9));
    }

    buildMaxHeap(heapKeys, heapSize);
    for (int i=1; i<=heapSize; i++) {
        std::cout << " " << heapKeys[i];
    }
    std::cout << std::endl;

    return 0;
}
