#include<cassert>
#include<cmath>
#include<iostream>
#include<queue>
#include<set>
#include<vector>


const int infinity = std::pow(2,30);


class Dijkstra {
public:
    Dijkstra(const int vertexNum) : vertexNum(vertexNum) {
        distances = new int[vertexNum];
        isSearched = new bool[vertexNum];
        adjList = new std::vector<std::pair<int, int> >[vertexNum];
    }

    ~Dijkstra() {
        delete[] distances;
        delete[] isSearched;
        delete[] adjList;
    }

    std::vector<int> search(const int startIdx) {
        initialize();
        distances[startIdx] = 0;
        isSearched[startIdx] = 0;

        std::priority_queue<std::pair<int, int> > distanceIdPairs;
        distanceIdPairs.push(std::pair(0, startIdx));

        while (!distanceIdPairs.empty()) {
            auto pair = distanceIdPairs.top();
            distanceIdPairs.pop();
            const int minId = pair.second;
            isSearched[minId] = true;

            for (int i = 0; i < adjList[minId].size(); i++) {
                const int adjId = adjList[minId][i].first;
                const int adjWeight = adjList[minId][i].second;

                if (isSearched[adjId]) continue;

                const int distance = distances[minId] + adjWeight;
                if (distance < distances[adjId]) {
                    distances[adjId] = distance;
                    distanceIdPairs.push(std::pair(-distance, adjId));
                }
            }
        }


        auto result = std::vector<int>(vertexNum);
        for (int i = 0; i < vertexNum; i++) result[i] = distances[i];
        return result;
    }

    void setWeight(const int i, const int j, const int weight) {
        for (int k = 0; k < adjList[i].size(); k++) {
            if (adjList[i][k].first == j) {
                adjList[i][k].second = weight;
                return;
            }
        }
        adjList[i].push_back(std::make_pair(j, weight));
    }

private:
    const int vertexNum;
    int *distances;
    bool *isSearched;
    std::vector<std::pair<int, int> > *adjList;  // firstがid, secondがweight

    int getWeight(const int i, const int j) const {
        for (int k = 0; k < adjList[i].size(); k++) {
            if (adjList[i][k].first == j) {
                return adjList[i][k].second;
            }
        }
        return infinity;
    }

    void initialize() {
        for (int i = 0; i < vertexNum; i++) {
            distances[i] = infinity;
            isSearched[i] = false;
        }
    }
};


int main() {
    int vertexNum;
    std::cin >> vertexNum;
    assert(1 <= vertexNum && vertexNum <= 10000);

    // 隣接行列の取得
    auto dijkstra = Dijkstra(vertexNum);
    for (int _ = 0; _ < vertexNum; _++) {
        int id1, outputDegree;
        std::cin >> id1 >> outputDegree;
        assert(0 <= id1 && id1 <= vertexNum - 1);

        for (int _ = 0; _ < outputDegree; _++) {
            int id2, weight;
            std::cin >> id2 >> weight;
            assert(0 <= id2 && id2 <= vertexNum - 1);
            assert(0 <= weight && weight <= std::pow(10,5));
            dijkstra.setWeight(id1, id2, weight);
        }
    }

    // 最短距離の出力
    std::vector<int> distances = dijkstra.search(0);
    for (int i = 0; i < vertexNum; i++) {
        std::cout << i << " " << distances[i] << std::endl;
    }

    return 0;
}
