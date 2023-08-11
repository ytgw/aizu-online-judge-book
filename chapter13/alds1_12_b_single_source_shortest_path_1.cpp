#include<cassert>
#include<cmath>
#include<iostream>
#include<vector>


const int infinity = std::pow(2,30);


class Dijkstra {
public:
    Dijkstra(const int *adjMatrix, const int vertexNum) : vertexNum(vertexNum) {
        distances = new int[vertexNum];
        this->adjMatrix = new int[vertexNum * vertexNum];

        for (int i = 0; i < vertexNum; i++) {
            for (int j = 0; j < vertexNum; j++) {
                const int weight = adjMatrix[i * vertexNum + j];
                setAdjMatrix(i, j, weight);
            }
        }
    }

    ~Dijkstra() {
        delete[] distances;
        delete[] adjMatrix;
    }

    std::vector<int> search(const int startIdx) {
        initializeDistances();
        initializeNonSeachIds();
        distances[startIdx] = 0;

        while (nonSearchIds.size() > 0) {
            // nonSearchIds内で距離が最小のidを取得
            const int minId = getMinNonSeachIds();

            deleteId(minId);

            // distancesの更新
            for (int i = 0; i < vertexNum; i++) {
                const int distance = distances[minId] + getAdjMatrix(minId, i);
                if (distance < distances[i]) {
                    distances[i] = distance;
                }
            }

            // printNonSearchIds();
            // printNonSearchDistances();
            // printDistances();
            // std::cout << std::endl;
        }

        auto result = std::vector<int>(vertexNum);
        for (int i = 0; i < vertexNum; i++) result[i] = distances[i];
        return result;
    }

private:
    const int vertexNum;
    int *distances, *adjMatrix;
    std::vector<int> nonSearchIds;

    int getAdjMatrix(const int i, const int j) const {
        return adjMatrix[i * vertexNum + j];
    }

    void setAdjMatrix(const int i, const int j, const int weight) {
        adjMatrix[i * vertexNum + j] = weight;
    }

    void initializeDistances() {
        for (int i = 0; i < vertexNum; i++) distances[i] = infinity;
    }

    void initializeNonSeachIds() {
        nonSearchIds = std::vector<int>(vertexNum);
        for (int i = 0; i < vertexNum; i++) nonSearchIds[i] = i;
    }

    int getMinNonSeachIds() const {
        // nonSearchIds内で距離が最小のidを取得
        int minId = nonSearchIds[0];
        for (int i = 0; i < nonSearchIds.size(); i++) {
            const int id = nonSearchIds[i];
            if (distances[id] < distances[minId]) {
                minId = id;
            }
        }
        return minId;
    }

    void deleteId(const int id) {
        for (int i = 0; i < nonSearchIds.size(); i++) {
            if (nonSearchIds[i] == id) {
                nonSearchIds.erase(nonSearchIds.begin() + i);
                return;
            }
        }
    }

    void printNonSearchIds() const {
        std::cout << "nonSearchIds: ";
        for (int i = 0; i < nonSearchIds.size(); i++) {
            std::cout << nonSearchIds[i] << ", ";
        }
        std::cout << std::endl;
    }

    void printDistances() const {
        std::cout << "distances: ";
        for (int i = 0; i < vertexNum; i++) {
            int distance = distances[i];
            if (distance >= infinity) distance = -1;
            printf("%2d, ", distance);
        }
        std::cout << std::endl;
    }

    void printNonSearchDistances() const {
        std::cout << "nonSearchDistances: ";
        for (int i = 0; i < nonSearchIds.size(); i++) {
            const int id = nonSearchIds[i];
            int distance = distances[id];
            if (distance >= infinity) distance = -1;
            printf("{id=%d, dist=%d}, ", id, distance);
        }
        std::cout << std::endl;
    }
};


int main() {
    int vertexNum;
    std::cin >> vertexNum;
    assert(1 <= vertexNum && vertexNum <= 100);

    int adjMatrix[vertexNum][vertexNum];
    for (int i=0; i<vertexNum; i++) {
        for (int j=0; j<vertexNum; j++) {
            adjMatrix[i][j] = infinity;
        }
    }

    // 隣接行列の取得
    for (int _ = 0; _ < vertexNum; _++) {
        int id1, outputDegree;
        std::cin >> id1 >> outputDegree;
        assert(0 <= id1 && id1 <= vertexNum - 1);

        for (int _ = 0; _ < outputDegree; _++) {
            int id2, weight;
            std::cin >> id2 >> weight;
            assert(0 <= id2 && id2 <= vertexNum - 1);
            assert(0 <= weight && weight <= std::pow(10,5));
            adjMatrix[id1][id2] = weight;
        }
    }

    // 最短距離の出力
    auto dijkstra = Dijkstra((int*)adjMatrix, vertexNum);
    std::vector<int> distances = dijkstra.search(0);
    for (int i = 0; i < vertexNum; i++) {
        std::cout << i << " " << distances[i] << std::endl;
    }

    return 0;
}
