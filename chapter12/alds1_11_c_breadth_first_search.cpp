#include<cassert>
#include<cmath>
#include<iostream>
#include<queue>
#include<vector>


class Vertex {
public:
    Vertex() : isVisited(false), distance(-1) {}
    void print() const {
        printf("isVisited: %d, distance: %d, adjIds: [", isVisited, distance);
        for (int i=0; i<adjIds.size(); i++) {
            printf("%d, ", adjIds[i]);
        }
        printf("]\n");
    }
    bool isVisited;
    int distance;
    std::vector<int> adjIds;
};


void breadthFirstSearch(Vertex vertexes[], const int startVertexId) {
    std::queue<int> queue;

    vertexes[startVertexId].isVisited = true;
    vertexes[startVertexId].distance = 0;
    queue.push(startVertexId);

    while (!queue.empty()) {
        int id = queue.front();
        queue.pop();
        int distance = vertexes[id].distance;

        for (int i = 0; i < vertexes[id].adjIds.size(); i++) {
            int adjId = vertexes[id].adjIds[i];
            if (!vertexes[adjId].isVisited) {
                vertexes[adjId].isVisited = true;
                vertexes[adjId].distance = distance + 1;
                queue.push(adjId);
            }
        }
    }
}


int main() {
    int vertexNum;
    std::cin >> vertexNum;
    assert(1 <= vertexNum && vertexNum <= 100);

    Vertex vertexes[vertexNum + 1];  // 1オリジン
    for (int _=0; _<vertexNum; _++) {
        int id, degree;
        std::cin >> id >> degree;
        assert(1 <= id && id <= vertexNum);
        assert(degree < vertexNum);

        for (int _=0; _<degree; _++) {
            int adjId;
            std::cin >> adjId;
            assert(1<= adjId && adjId <= vertexNum);

            vertexes[id].adjIds.push_back(adjId);
        }
    }

    // 探索
    breadthFirstSearch(vertexes, 1);

    // 結果表示
    for (int i = 1; i <= vertexNum; i++) {
        std::cout << i << " " << vertexes[i].distance << std::endl;
    }

    return 0;
}
