#include<cassert>
#include<cmath>
#include<iostream>
#include<vector>
#include<queue>


class DAG {
public:
    DAG(const int vertexNum) {
        allOrigins = std::vector<std::vector<int>>(vertexNum);
    }

    void setEdge(const int origin, const int destination) {
        allOrigins[destination].push_back(origin);
    }

    void printTopologicalSortResult() const {
        const int vertexNum = allOrigins.size();
        auto isCompleted = std::vector<bool>(vertexNum, false);

        // sort
        std::queue<int> sortedVertex;
        while (sortedVertex.size() < vertexNum) {
            for (int i = 0; i < vertexNum; i++) {
                if (isCompleted[i]) continue;

                auto origins = allOrigins[i];
                bool shouldPush = true;
                for (int j = 0; j < origins.size(); j++) {
                    int origin = origins[j];
                    shouldPush = shouldPush && isCompleted[origin];
                }

                if (shouldPush) {
                    sortedVertex.push(i);
                    isCompleted[i] = true;
                }
            }
        }

        // print
        for (int _ = 0; _ < vertexNum; _++) {
            std::cout << sortedVertex.front() << std::endl;
            sortedVertex.pop();
        }
    }

private:
    std::vector<std::vector<int>> allOrigins;
};


int main() {
    int vertexNum, edgeNum;
    std::cin >> vertexNum >> edgeNum;
    assert(1 <= vertexNum && vertexNum <= std::pow(10,4));
    assert(0 <= edgeNum && edgeNum <= std::pow(10,5));

    DAG dag = DAG(vertexNum);
    for (int i = 0; i < edgeNum; i++) {
        int origin, destination;
        std::cin >> origin >> destination;
        dag.setEdge(origin, destination);
    }

    dag.printTopologicalSortResult();

    return 0;
}
