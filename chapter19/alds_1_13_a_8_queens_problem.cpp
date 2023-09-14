#include<cassert>
#include<iostream>
#include<stack>
#include<vector>


class QueensProblemSolver {
public:
    QueensProblemSolver(const std::vector<int> queenColumns): initialQueenColumns(queenColumns) {}

    void printSolution() const {
        std::vector<int> queenColumns = initialQueenColumns;
        bool canPut = putQueen(queenColumns, 0);
        assert(canPut);

        printBoard(queenColumns);
    }

private:
    // queenColumns[i]はi行目のQueenの位置を表す。-1は位置不明を示す。
    const std::vector<int> initialQueenColumns;

    bool canAttack(const int queenRow, const int queenColumn, const int checkRow, const int checkColumn) const {
        if (queenRow == checkRow) return true;
        if (queenColumn == checkColumn) return true;

        // 斜め
        if (std::abs(checkRow - queenRow) == std::abs(checkColumn - queenColumn)) return true;

        return false;
    }

    bool canAttack(const std::vector<int> queenColumns, const int checkRow, const int checkColumn) const {
        for (int queenRow = 0; queenRow < queenColumns.size(); queenRow++) {
            int queenColumn = queenColumns[queenRow];

            if (queenColumn == -1) continue;

            if (canAttack(queenRow, queenColumn, checkRow, checkColumn)) return true;
        }

        return false;
    }

    bool putQueen(std::vector<int>& queenColumns, const int row) const {
        // row以降の行にQueenを置けたらtrueを返す。

        const int boardSize = queenColumns.size();

        // row >= boardSizeのときは、0-boardSizeまでQueenを置けたということでtrue
        if (row >= boardSize) {
            return true;
        }

        // 初期にQueenが配置されている行は、それ以降に置けるかどうかを返す。
        if (initialQueenColumns[row] != -1) {
            queenColumns[row] = initialQueenColumns[row];
            return putQueen(queenColumns, row + 1);
        }

        // それ以外
        for (int column = 0; column < boardSize; column++) {
            // デバッグ用
            // if (canAttack(queenColumns, row, column)) {
            //     printf("(%d, %d): true\n", row, column);
            // } else {
            //     printf("(%d, %d): false\n", row, column);
            // }

            if (canAttack(queenColumns, row, column)) continue;

            queenColumns[row] = column;
            bool canPut = putQueen(queenColumns, row + 1);
            if (canPut) {
                return true;
            } else {
                queenColumns[row] = -1;
            }
        }

        return false;
    }

    void printBoard(const std::vector<int> queenColumns) const {
        const int boardSize = queenColumns.size();
        for (int row = 0; row < boardSize; row++) {
            const int queenColumn = queenColumns[row];
            for (int column = 0; column < boardSize; column++) {
                if (column == queenColumn) std::cout << "Q";
                else std::cout << ".";
            }
            std::cout << std::endl;
        }
    }
};


int main() {
    int queenNum;
    std::cin >> queenNum;

    const int boardSize = 8;
    // queenColumns[i]はi行目のQueenの位置を表す。
    std::vector<int> queenColumns = std::vector<int>(boardSize, -1);
    for (int _ = 0; _ < queenNum; _++) {
        int row, column;
        std::cin >> row >> column;
        queenColumns[row] = column;
    }

    QueensProblemSolver solver = QueensProblemSolver(queenColumns);
    solver.printSolution();

    return 0;
}
