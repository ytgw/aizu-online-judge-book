#include<algorithm>
#include<cassert>
#include<iostream>
#include<vector>


class Item {
public:
    Item(const int value, const int weight): value(value), weight(weight) {}
    int getValue() const {
        return value;
    }
    int getWeight() const {
        return weight;
    }

private:
    int value, weight;
};


class KnapsackProblemSolver {
public:
    KnapsackProblemSolver(const int maxWeight, const std::vector<Item> items): maxWeight(maxWeight) {
        this->items = items;
    }

    int calcMaxValue() {
        initialize();
        for (int maxItemId = 1; maxItemId < items.size(); maxItemId++) {
            updateMatrix(maxItemId);
        }
        return valueMatrix[items.size() - 1][maxWeight];
    }

private:
    const int maxWeight;
    std::vector<Item> items;
    // valueMatrix[maxItemId][weight]は、0-maxItemIdのItemで合計重量weight内で最大の価値
    std::vector<std::vector<int>> valueMatrix;

    void initialize() {
        valueMatrix = std::vector<std::vector<int>>(items.size(), std::vector<int>(maxWeight + 1, 0));

        const int itemValue = items[0].getValue();
        const int itemWeight = items[0].getWeight();
        for (int weight = 1; weight <= maxWeight; weight++) {
            int value;
            if (weight >= itemWeight) {
                value = itemValue;
            } else {
                value = 0;
            }
            valueMatrix[0][weight] = value;
        }
    }

    void updateMatrix(const int maxItemId) {
        assert(maxItemId >= 1);

        const int itemValue = items[maxItemId].getValue();
        const int itemWeight = items[maxItemId].getWeight();

        for (int weight = 1; weight <= maxWeight; weight++) {
            if (weight >= itemWeight) {
                valueMatrix[maxItemId][weight] = std::max(
                    valueMatrix[maxItemId - 1][weight],
                    valueMatrix[maxItemId - 1][weight - itemWeight] + itemValue
                );
            } else {
                valueMatrix[maxItemId][weight] = valueMatrix[maxItemId - 1][weight];
            }
        }
    }
};


int main() {
    int itemNum, maxWeight;
    std::cin >> itemNum >> maxWeight;

    std::vector<Item> items;
    for (int i = 0; i < itemNum; i++) {
        int value, weight;
        std::cin >> value >> weight;
        assert(value > 0);
        assert(weight > 0);
        items.push_back(Item(value, weight));
    }

    // 計算
    auto solver = KnapsackProblemSolver(maxWeight, items);
    std::cout << solver.calcMaxValue() << std::endl;

    return 0;
}
