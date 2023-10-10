#include<cassert>
#include<cmath>
#include<iostream>
#include<queue>
#include<set>
#include<map>
#include<vector>


class PuzzleState {
public:
    PuzzleState(const std::vector<int> positions, const unsigned int stepNum): positions(positions), stepNum(stepNum) {
        const unsigned int boardSize = 9;
        assert(positions.size() == boardSize);

        for (int i = 0; i < boardSize; i++) assert(hasElement(i));
    }

    bool hasElement(const unsigned int num) const {
        for (auto it = positions.cbegin(); it != positions.cend(); ++it) {
            if (*it == num) return true;
        }

        return false;
    }

    std::vector<int> getPositions() const {
        return positions;
    }

    unsigned int getStepNum() const {
        return stepNum;
    }

    bool isSolved() const {
        const unsigned int maxIdx = 8;

        if (positions[maxIdx] != 0) return false;

        for (int i = 0; i < maxIdx; i++) {
            if (positions[i] != i + 1) return false;
        }

        return true;
    }

    unsigned int getIndex(const unsigned int num) const {
        for (int i = 0; i < positions.size(); i++) {
            if (positions[i] == num) return i;
        }

        assert(false);
    }

    unsigned int getKey() const {
        const unsigned int size = 9;

        unsigned int key = 0;
        for (int i = 0; i < size; i++) {
            key += std::pow(9, i) * positions[i];
        }

        return key;
    }

private:
    std::vector<int> positions;
    unsigned int stepNum;
};


class EightPuzzleSolver {
public:
    EightPuzzleSolver(const std::vector<int> positions): initialPositions(positions) {}

    int calcAnswer() const {
        const unsigned int infinity = std::pow(2, 15);

        std::queue<PuzzleState> nextSearchStates;
        std::set<unsigned int> searchedKeys;

        nextSearchStates.push(PuzzleState(initialPositions, 0));
        unsigned int minSolvedStepNum = infinity;

        while (!nextSearchStates.empty()) {
            const PuzzleState state = nextSearchStates.front();
            nextSearchStates.pop();

            if (state.isSolved()) {
                minSolvedStepNum = std::min(minSolvedStepNum, state.getStepNum());
                break;
            }

            if (minSolvedStepNum < state.getStepNum()) continue;

            breadthFirstSearch(state, searchedKeys, nextSearchStates);
        }

        return minSolvedStepNum;
    }

private:
    const std::vector<int> initialPositions;

    unsigned int getSwappedKey(
        const std::vector<int> positions,
        const unsigned int idx1,
        const unsigned int idx2
    ) const {
        const unsigned int size = 9;

        unsigned int key = 0;
        for (int i = 0; i < size; i++) {
            int idx = i;
            if (idx == idx1) idx = idx2;
            if (idx == idx2) idx = idx1;
            key += std::pow(size, i) * positions[idx];
        }

        return key;
    }

    std::vector<int> createSwappedPositions(
        const std::vector<int> originalPositions,
        const unsigned int idx1,
        const unsigned int idx2
    ) const {
        std::vector<int> positions = originalPositions;
        std::swap(positions[idx1], positions[idx2]);
        return positions;
    }

    void update(
        const PuzzleState state,
        const unsigned int idx1,
        const unsigned int idx2,
        std::set<unsigned int>& searchedKeys,
        std::queue<PuzzleState>& nextSearchStates
    ) const {
        const auto swappedKey = getSwappedKey(state.getPositions(), idx1, idx2);
        if (searchedKeys.find(swappedKey) == searchedKeys.cend()) {
            searchedKeys.insert(swappedKey);
            const auto positions = createSwappedPositions(state.getPositions(), idx1, idx2);
            nextSearchStates.push(PuzzleState(positions, state.getStepNum() + 1));
        }
    }

    void breadthFirstSearch(
        const PuzzleState state,
        std::set<unsigned int>& searchedKeys,
        std::queue<PuzzleState>& nextSearchStates
    ) const {
        const unsigned int zeroIdx = state.getIndex(0);
        searchedKeys.insert(state.getKey());

        switch (zeroIdx) {
        case 0:
            update(state, zeroIdx, 1, searchedKeys, nextSearchStates);
            update(state, zeroIdx, 3, searchedKeys, nextSearchStates);
            break;
        case 1:
            update(state, zeroIdx, 0, searchedKeys, nextSearchStates);
            update(state, zeroIdx, 2, searchedKeys, nextSearchStates);
            update(state, zeroIdx, 4, searchedKeys, nextSearchStates);
            break;
        case 2:
            update(state, zeroIdx, 1, searchedKeys, nextSearchStates);
            update(state, zeroIdx, 5, searchedKeys, nextSearchStates);
            break;
        case 3:
            update(state, zeroIdx, 0, searchedKeys, nextSearchStates);
            update(state, zeroIdx, 4, searchedKeys, nextSearchStates);
            update(state, zeroIdx, 6, searchedKeys, nextSearchStates);
            break;
        case 4:
            update(state, zeroIdx, 1, searchedKeys, nextSearchStates);
            update(state, zeroIdx, 3, searchedKeys, nextSearchStates);
            update(state, zeroIdx, 5, searchedKeys, nextSearchStates);
            update(state, zeroIdx, 7, searchedKeys, nextSearchStates);
            break;
        case 5:
            update(state, zeroIdx, 2, searchedKeys, nextSearchStates);
            update(state, zeroIdx, 4, searchedKeys, nextSearchStates);
            update(state, zeroIdx, 8, searchedKeys, nextSearchStates);
            break;
        case 6:
            update(state, zeroIdx, 3, searchedKeys, nextSearchStates);
            update(state, zeroIdx, 7, searchedKeys, nextSearchStates);
            break;
        case 7:
            update(state, zeroIdx, 4, searchedKeys, nextSearchStates);
            update(state, zeroIdx, 6, searchedKeys, nextSearchStates);
            update(state, zeroIdx, 8, searchedKeys, nextSearchStates);
            break;
        case 8:
            update(state, zeroIdx, 5, searchedKeys, nextSearchStates);
            update(state, zeroIdx, 7, searchedKeys, nextSearchStates);
            break;
        default:
            break;
        }
    }
};


int main() {
    const unsigned int size = 9;
    std::vector<int> positions = std::vector<int>(size);
    for (int i = 0; i < size; i++) std::cin >> positions[i];

    EightPuzzleSolver solver = EightPuzzleSolver(positions);
    std::cout << solver.calcAnswer() << std::endl;

    return 0;
}
