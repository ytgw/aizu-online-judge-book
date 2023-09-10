#include<algorithm>
#include<cassert>
#include<iostream>
#include<vector>
#include<set>


class LongestIncreasingSubsequenceSolver {
public:
    LongestIncreasingSubsequenceSolver(const std::vector<int> numbers): numbers(numbers) {}

    int calcSubsequenceSize() {
        // minLastValues[i]は長さi+1の増加部分列の最後の要素の最小値
        std::set<int> minLastValues;
        minLastValues.insert(numbers[0]);
        for (int i = 1; i < numbers.size(); i++) {
            updateMinValues(numbers[i], minLastValues);
        }
        return minLastValues.size();
    }

private:
    std::vector<int> numbers;

    void updateMinValues(const int number, std::set<int>& minLastValues) {
        auto it = minLastValues.lower_bound(number);
        if (it != minLastValues.cend()) {
            minLastValues.erase(*it);
        }
        minLastValues.insert(number);
    }
};


int main() {
    int size;
    std::cin >> size;

    std::vector<int> numbers = std::vector<int>(size);
    for (int i = 0; i < size; i++) {
        std::cin >> numbers[i];
    }

    // 計算
    auto solver = LongestIncreasingSubsequenceSolver(numbers);
    std::cout << solver.calcSubsequenceSize() << std::endl;

    return 0;
}
