#include<iostream>
#include<cmath>
#include<cassert>


void printParentKey(const int heapKeys[], const int id) {
    if (id <= 1) return;

    const int parentID = id / 2;
    std::cout << "parent key = " << heapKeys[parentID - 1] << ", ";
}


void printLeftKey(const int heapKeys[], const int id, const int heapSize) {
    const int leftID = 2 * id;
    if (leftID > heapSize) return;

    std::cout << "left key = " << heapKeys[leftID - 1] << ", ";
}


void printRightKey(const int heapKeys[], const int id, const int heapSize) {
    const int rightID = 2 * id + 1;
    if (rightID > heapSize) return;

    std::cout << "right key = " << heapKeys[rightID - 1] << ", ";
}


int main() {
    int heapSize;
    std::cin >> heapSize;
    assert(heapSize <= 250);

    int heapKeys[heapSize];
    for (int i=0; i<heapSize; i++) {
        std::cin >> heapKeys[i];
        assert(-2 * std::pow(10,9) <= heapKeys[i] and heapKeys[i] <= 2 * std::pow(10,9));
    }

    for (int i=0; i<heapSize; i++) {
        std::cout << "node " << i + 1;
        std::cout << ": key = " << heapKeys[i] << ", ";
        printParentKey(heapKeys, i + 1);
        printLeftKey(heapKeys, i + 1, heapSize);
        printRightKey(heapKeys, i + 1, heapSize);
        std::cout << std::endl;
    }

    return 0;
}
