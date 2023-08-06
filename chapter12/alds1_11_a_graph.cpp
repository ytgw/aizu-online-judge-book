#include<cassert>
#include<cmath>
#include<iostream>


int main() {
    int nodeNum;
    std::cin >> nodeNum;
    assert(1 <= nodeNum && nodeNum <= 100);

    // 隣接行列の初期化
    int AdjacentMatrix[nodeNum][nodeNum];
    for (int i=0; i<nodeNum; i++) {
        for (int j=0; j<nodeNum; j++) {
            AdjacentMatrix[i][j] = 0;
        }
    }

    for (int i=0; i<nodeNum; i++) {
        int nodeId, degree;
        std::cin >> nodeId >> degree;
        assert(1<= nodeId && nodeId <= nodeNum);
        assert(degree < nodeNum);

        for (int j=0; j<degree; j++) {
            int adjNodeId;
            std::cin >> adjNodeId;
            assert(1<= adjNodeId && adjNodeId <= nodeNum);
            AdjacentMatrix[nodeId - 1][adjNodeId - 1] = 1;
        }
    }

    for (int i=0; i<nodeNum; i++) {
        std::cout << AdjacentMatrix[i][0];
        for (int j=1; j<nodeNum; j++) {
            std::cout << " " << AdjacentMatrix[i][j];
        }
        std::cout << std::endl;
    }

    return 0;
}
