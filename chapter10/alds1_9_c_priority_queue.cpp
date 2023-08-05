#include<iostream>
#include<cmath>
#include<cassert>


class Heap {
public:
    Heap() : heapSize(0) {}

    void insert(const int key) {
        assert(0 <= key && key <= 2 * std::pow(10,9));
        heapSize++;
        heap[heapSize] = -1;
        heapIncreaseKey(heapSize, key);
    }

    int extractMax() {
        assert(heapSize >= 1);

        const int max = heap[1];
        heap[1] = heap[heapSize];
        heapSize--;
        maxHeapify(1);
        return max;
    }

private:
    static const int maxHeapSize = 2000000;
    int heap[maxHeapSize + 1];  // 1オリジン
    int heapSize;

    int getParentId(const int id) {
        assert(id >= 2);
        return id / 2;
    }

    void heapIncreaseKey(const int id, const int key) {
        assert(key >= heap[id]);
        heap[id] = key;

        int nodeId = id;
        while (nodeId > 1 && heap[getParentId(nodeId)] < heap[nodeId]) {
            std::swap(heap[nodeId], heap[getParentId(nodeId)]);
            nodeId = getParentId(nodeId);
        }
    }

    void maxHeapify(const int id) {
        const int leftId = 2 * id;
        const int rightId = 2 * id + 1;

        // 左右の子と字分のうち最大のノードを選択
        int largestId = id;
        if (leftId <= heapSize && heap[leftId] > heap[largestId]) {
            largestId = leftId;
        }
        if (rightId <= heapSize && heap[rightId] > heap[largestId]) {
            largestId = rightId;
        }

        if (largestId != id) {
            std::swap(heap[id], heap[largestId]);
            maxHeapify(largestId);
        }
    }

};


int main() {
    Heap heap;
    while (true) {
        std::string command;
        std::cin >> command;
        if (command == "end") {
            break;
        } else if (command == "insert") {
            int key;
            std::cin >> key;
            heap.insert(key);
        } else if (command == "extract") {
            std::cout << heap.extractMax() << std::endl;
        } else {
            std::cerr << "Command is invalid." << std::endl;
        }
    }

    return 0;
}
