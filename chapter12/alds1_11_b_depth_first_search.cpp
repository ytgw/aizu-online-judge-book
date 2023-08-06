#include<cassert>
#include<cmath>
#include<iostream>
#include<vector>


class Vertex {
public:
    Vertex() : isSearched(false), discoverTime(0), finishTime(0) {}
    void print() const {
        printf("discoverTime: %d, finishTime: %d, adjIds: [", discoverTime, finishTime);
        for (int i=0; i<adjIds.size(); i++) {
            printf("%d, ", adjIds[i]);
        }
        printf("]\n");
    }
    int discoverTime, finishTime;
    bool isSearched;
    std::vector<int> adjIds;
};


int depthFirstSeach(Vertex vertexes[], const int id, int time) {
    // 現在時刻を返す

    // std::cout << id << " ";
    // vertexes[id].print();

    if (vertexes[id].isSearched) return time;
    vertexes[id].isSearched = true;

    time++;
    vertexes[id].discoverTime = time;

    const auto adjIds = vertexes[id].adjIds;
    for (int i=0; i<adjIds.size(); i++) {
        time = depthFirstSeach(vertexes, adjIds[i], time);
    }

    time++;
    vertexes[id].finishTime = time;
    return time;
}


int main() {
    int vertexNum;
    std::cin >> vertexNum;
    assert(1 <= vertexNum && vertexNum <= 100);

    Vertex vertexes[vertexNum + 1];  // 1オリジン
    for (int _=0; _<vertexNum; _++) {
        int id, degree;
        std::cin >> id >> degree;
        assert(1<= id && id <= vertexNum);
        assert(degree < vertexNum);

        for (int _=0; _<degree; _++) {
            int adjId;
            std::cin >> adjId;
            assert(1<= adjId && adjId <= vertexNum);

            vertexes[id].adjIds.push_back(adjId);
        }
    }

    // 探索
    int time = 0;
    for (int id=1; id<=vertexNum; id++) {
        if (!vertexes[id].isSearched) {
            time = depthFirstSeach(vertexes, id, time);
        }
    }

    // 結果表示
    for (int id=1; id<=vertexNum; id++) {
        Vertex vertex = vertexes[id];
        std::cout << id << " " << vertex.discoverTime << " " << vertex.finishTime << std::endl;
    }

    return 0;
}
