#include<cassert>
#include<cmath>
#include<iostream>
#include<queue>
#include<vector>


class Vertex {
public:
    Vertex() : isVisited(false), componentId(-1) {}
    void print() const {
        printf("isVisited: %d, componentId: %d, adjIds: [", isVisited, componentId);
        for (int i=0; i<adjIds.size(); i++) {
            printf("%d, ", adjIds[i]);
        }
        printf("]\n");
    }
    bool isVisited;
    int componentId;
    std::vector<int> adjIds;
};


void breadthFirstSearch(Vertex vertexes[], const int startVertexId, const int componentId) {
    std::queue<int> queue;

    vertexes[startVertexId].isVisited = true;
    vertexes[startVertexId].componentId = componentId;
    queue.push(startVertexId);

    while (!queue.empty()) {
        int id = queue.front();
        queue.pop();

        for (int i = 0; i < vertexes[id].adjIds.size(); i++) {
            int adjId = vertexes[id].adjIds[i];
            if (!vertexes[adjId].isVisited) {
                vertexes[adjId].isVisited = true;
                vertexes[adjId].componentId = componentId;
                queue.push(adjId);
            }
        }
    }
}


void calcConnectedComponents(Vertex vertexes[], const int vertexNum) {
    for (int i = 0; i < vertexNum; i++) {
        if (!vertexes[i].isVisited) {
            breadthFirstSearch(vertexes, i, i);
        }
    }
}


int main() {
    int userNum;
    std::cin >> userNum;
    assert(2 <= userNum && userNum <= std::pow(10,5));

    int friendNum;
    std::cin >> friendNum;
    assert(0 <= friendNum && friendNum <= std::pow(10,5));

    // 友人関係の取得
    Vertex users[userNum];
    for (int _ = 0; _ < friendNum; _++) {
        int id1, id2;
        std::cin >> id1 >> id2;
        assert(0 <= id1 && id1 <= userNum - 1);
        assert(0 <= id2 && id2 <= userNum - 1);

        users[id1].adjIds.push_back(id2);
        users[id2].adjIds.push_back(id1);
    }

    // 連結部分の探索
    calcConnectedComponents(users, userNum);

    // 質問の取得と回答
    int questionNum;
    std::cin >> questionNum;
    assert(1 <= questionNum <= 10000);

    for (int _ = 0; _ < questionNum; _++) {
        int id1, id2;
        std::cin >> id1 >> id2;
        assert(0 <= id1 && id1 <= userNum - 1);
        assert(0 <= id2 && id2 <= userNum - 1);

        if (users[id1].componentId == users[id2].componentId) {
            std::cout << "yes" << std::endl;
        } else {
            std::cout << "no" << std::endl;
        }
    }

    return 0;
}
