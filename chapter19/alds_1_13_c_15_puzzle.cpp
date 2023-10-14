#include<iostream>
#include<queue>
#include<set>
#include<vector>


const unsigned int LENGTH = 4;
const unsigned int ELEMENT_NUM = LENGTH * LENGTH;
const unsigned int MAX_STEP = 45;


class PuzzlePositions {
public:
    PuzzlePositions(const std::vector<int> positions): positions(positions) {
        manhattanDest = calcManhattanDest();
    }

    PuzzlePositions createSwappedPositions(const int idx1, const int idx2) const {
        std::vector<int> newPositions = positions;
        std::swap(newPositions[idx1], newPositions[idx2]);
        return PuzzlePositions(newPositions);
    }

    std::vector<int> getPositions() const {
        return positions;
    }

    int getIndex(const int value) const {
        for (int i = 0; i < ELEMENT_NUM; i++) {
            if (positions[i] == value) return i;
        }

        return -1;
    }

    int getManhattanDest() const {
        return manhattanDest;
    }

    bool isSolved() const {
        const int maxIdx = ELEMENT_NUM - 1;

        if (positions[maxIdx] != 0) return false;

        for (int i = 0; i < maxIdx; i++) {
            if (positions[i] != i + 1) return false;
        }

        return true;
    }

    bool operator < (const PuzzlePositions p) const {
        for (int i = 0; i < ELEMENT_NUM; i++) {
            if (positions[i] == p.positions[i]) continue;
            return positions[i] < p.positions[i];
        }
        return false;
    }

private:
    std::vector<int> positions;
    int manhattanDest;

    int calcManhattanDest() const {
        unsigned int manhattanDest = 0;

        for (int value = 1; value < ELEMENT_NUM; value++) {
            int presentIdx = getIndex(value);
            int desiredIdx = value - 1;
            const int diff = std::abs(desiredIdx - presentIdx);
            const int tate = diff / LENGTH;
            const int yoko = diff % LENGTH;

            manhattanDest += tate + yoko;
        }

        return manhattanDest;
    }
};


class PuzzleState {
public:
    PuzzleState(const PuzzlePositions p, const int stepNum): puzzlePositions(p), stepNum(stepNum) {}

    PuzzlePositions getPositions() const {
        return puzzlePositions;
    }

    int getStepNum() const {
        return stepNum;
    }

    int getCost() const {
        return stepNum + puzzlePositions.getManhattanDest();
    }

    bool operator < (const PuzzleState p) const {
        // 不等号が入れ替わりに注意
        return (getCost() > p.getCost());
    }

private:
    PuzzlePositions puzzlePositions;
    int stepNum;
    int cost;
};


class PuzzleSolver {
public:
    PuzzleSolver(const std::vector<int> positions): initialPositions(positions) {}

    int calcAnswer() const {
        std::set<PuzzlePositions> searchedPositions;
        std::priority_queue<PuzzleState> priorityQueue;

        priorityQueue.push(PuzzleState(PuzzlePositions(initialPositions), 0));
        while (!priorityQueue.empty()) {
            const auto state = priorityQueue.top();
            priorityQueue.pop();
            searchedPositions.insert(state.getPositions());

            if (state.getPositions().isSolved()) return state.getCost();
            if (state.getCost() > MAX_STEP) continue;

            breadthFirstSearch(state, searchedPositions, priorityQueue);
        }

        return -1;
    }

private:
    const std::vector<int> initialPositions;

    void pushUnSearchedPuzzleIntoQueue(
        const PuzzleState state,
        const unsigned int positionIdx1,
        const unsigned int positionIdx2,
        std::set<PuzzlePositions>& searchedPositions,
        std::priority_queue<PuzzleState>& priorityQueue
    ) const {
        const auto newPositions = state.getPositions().createSwappedPositions(positionIdx1, positionIdx2);
        const auto newState = PuzzleState(newPositions, state.getStepNum() + 1);

        const bool isSearched = searchedPositions.find(newPositions) != searchedPositions.cend();
        const bool hasHighCost = newState.getCost() > MAX_STEP;
        if ((!isSearched) && (!hasHighCost)) {
            priorityQueue.push(newState);
        }
    }

    void breadthFirstSearch(
        const PuzzleState state,
        std::set<PuzzlePositions>& searchedPositions,
        std::priority_queue<PuzzleState>& priorityQueue
    ) const {
        const unsigned int zeroIdx = state.getPositions().getIndex(0);
        const unsigned int quotient = zeroIdx / LENGTH;
        const unsigned int remainder = zeroIdx % LENGTH;

        if (quotient >= 1) pushUnSearchedPuzzleIntoQueue(state, zeroIdx, zeroIdx - LENGTH, searchedPositions, priorityQueue);
        if (quotient <= 2) pushUnSearchedPuzzleIntoQueue(state, zeroIdx, zeroIdx + LENGTH, searchedPositions, priorityQueue);
        if (remainder >= 1) pushUnSearchedPuzzleIntoQueue(state, zeroIdx, zeroIdx - 1, searchedPositions, priorityQueue);
        if (remainder <= 2) pushUnSearchedPuzzleIntoQueue(state, zeroIdx, zeroIdx + 1, searchedPositions, priorityQueue);
    }
};


int main() {
    auto positions = std::vector<int>(ELEMENT_NUM);
    for (int i = 0; i < ELEMENT_NUM; i++) std::cin >> positions[i];

    PuzzleSolver solver = PuzzleSolver(positions);
    std::cout << solver.calcAnswer() << std::endl;

    return 0;
}
