#include<cassert>
#include<cmath>
#include<iostream>
#include<vector>


const int infinity = std::pow(2,31) - 1;


bool contains(const std::vector<int> vector, const int value) {
    for (int i = 0; i < vector.size(); i++) {
        if (value == vector[i]) return true;
    }
    return false;
}


std::vector<int> createMinWeights(const int *adjMatrix, const std::vector<int> mstIds, const int vertexNum) {
    // mstIds内のvertexから隣接頂点への最小の辺の重みを返す。

    std::vector<int> minWeights(vertexNum);

    for (int i = 0; i < vertexNum; i++) {
        if (contains(mstIds, i)) {
            minWeights[i] = infinity;
            continue;
        }

        int weight = infinity;
        for (int j = 0; j < mstIds.size(); j++) {
            int mstId = mstIds[j];
            weight = std::min(weight, adjMatrix[i * vertexNum + mstId]);
        }
        minWeights[i] = weight;
    }

    return minWeights;
}


int getMinIdx(const std::vector<int> vector) {
    int minIdx = 0;
    for (int i=1; i<vector.size(); i++) {
        if (vector[i] < vector[minIdx]) {
            minIdx = i;
        }
    }
    return minIdx;
}


int prim(const int *adjMatrix, const int vertexNum) {
    // 最小全域木の辺の重みの総和を返す。

    int totalWeight = 0;
    std::vector<int> mstIds;
    mstIds.push_back(0);

    while (mstIds.size() < vertexNum) {
        // mstIds内のvertexから隣接頂点への最小の辺の重み
        std::vector<int> minWeights = createMinWeights(adjMatrix, mstIds, vertexNum);

        int minIdx = getMinIdx(minWeights);
        totalWeight += minWeights[minIdx];
        mstIds.push_back(minIdx);
    }

    return totalWeight;
}


int main() {
    int vertexNum;
    std::cin >> vertexNum;
    assert(1 <= vertexNum && vertexNum <= 100);

    int adjMatrix[vertexNum][vertexNum];
    for (int i = 0; i < vertexNum; i++) {
        for (int j = 0; j < vertexNum; j++) {
            int weight;
            std::cin >> weight;
            assert(-1 <= weight && weight <= 2000);
            if (weight == -1) {
                weight = infinity;
            }
            adjMatrix[i][j] = weight;
        }
    }

    std::cout << prim((int*)adjMatrix, vertexNum) << std::endl;

    return 0;
}
