#include<cassert>
#include<cmath>
#include<iostream>


class MatrixChainMultiplication {
public:
    MatrixChainMultiplication(const int matrixRows[], const int matrixColumns[], const int matrixNum) : matrixNum(matrixNum) {
        // 1オリジン
        this->matrixRows = new int[matrixNum + 1];
        this->matrixColumns = new int[matrixNum + 1];
        this->minProductNumMatrix = new int[(matrixNum + 1) * (matrixNum + 1)];

        for (int i=1; i<=matrixNum; i++) {
            this->matrixRows[i] = matrixRows[i];
            this->matrixColumns[i] = matrixColumns[i];
        }
    }

    ~MatrixChainMultiplication() {
        delete[] matrixRows;
        delete[] matrixColumns;
        delete[] minProductNumMatrix;
    }

    int calcMinProductNum() {
        for (int i=1; i<=matrixNum; i++) {
            setValue(i, i, 0);
        }

        for (int updateColumn = 2; updateColumn <= matrixNum; updateColumn++) {
            update(updateColumn);
            // printMinProductNumMatrix();
            // std::cout << std::endl;
        }

        return getValue(1, matrixNum);
    }


private:
    const int matrixNum;
    int *minProductNumMatrix, *matrixRows, *matrixColumns;

    int getIdx(const int i, const int j) const {
        return i * (matrixNum + 1) + j;
    }

    int getValue(const int i, const int j) const {
        return minProductNumMatrix[getIdx(i, j)];
    }

    void setValue(const int i, const int j, const int value) {
        minProductNumMatrix[getIdx(i, j)] = value;
    }

    void printMinProductNumMatrix() const {
        // デバッグ用
        for (int i=1; i<=matrixNum; i++) {
            for (int j=1; j<=matrixNum; j++) {
                int value = -1;
                if (i <= j) value = getValue(i, j);
                printf("%6d, ", value);
            }
            std::cout << std::endl;
        }
    }

    void update(const int updateColumn) {
        // results[1 ~ updateColumn-1][1 ~ updateColumn-1] から results[*][updateColumn]を算出
        for (int updateRow = updateColumn - 1; updateRow >= 1; updateRow--) {
            const int infinity = std::pow(2, 31) - 1;
            int minProductNum = infinity;

            for (int k = updateRow; k < updateColumn; k++) {
                // Mi...MkとMk+1...Mjに分ける
                const int productNum = matrixRows[updateRow] * matrixColumns[k] * matrixColumns[updateColumn];
                const int productNumK = getValue(updateRow, k) + getValue(k+1, updateColumn) + productNum;
                minProductNum = std::min(minProductNum, productNumK);
            }
            setValue(updateRow, updateColumn, minProductNum);
        }
    }
};


int main() {
    int matrixNum;
    std::cin >> matrixNum;
    assert(1 <= matrixNum && matrixNum <= 100);

    int matrixRows[matrixNum + 1], matrixColumns[matrixNum + 1];  // 1オリジン
    for (int i=1; i<=matrixNum; i++) {
        std::cin >> matrixRows[i] >> matrixColumns[i];

        assert(1 <= matrixRows[i] && matrixRows[i] <= 100);
        assert(1 <= matrixColumns[i] && matrixColumns[i] <= 100);
    }

    MatrixChainMultiplication multiplication = MatrixChainMultiplication(matrixRows, matrixColumns, matrixNum);
    std::cout << multiplication.calcMinProductNum() << std::endl;

    return 0;
}
