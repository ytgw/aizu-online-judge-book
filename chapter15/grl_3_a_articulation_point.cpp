#include<algorithm>
#include<cassert>
#include<cmath>
#include<iostream>
#include<set>
#include<stack>
#include<vector>


class Vertex {
public:
    Vertex() : parentId(nil), discoverOrder(infinity), lowestNum(infinity) {}

    void addConnectedId(const int id) {
        connectedIds.insert(id);
    }

    void set(const bool isDiscovered, const int parentId, const int discoverOrder) {
        this->isDiscovered = isDiscovered;
        this->parentId = parentId;
        this->discoverOrder = discoverOrder;
    }

    bool setLowestNum(const int lowestNum) {
        if (this->lowestNum > lowestNum) {
            this->lowestNum = lowestNum;
            return true;
        } else {
            return false;
        }
    }

    bool hasParent() const {
        return parentId != nil;
    }

    void print() const {
        printf(
            "{isDiscovered: %s, parentId: %d, discoverOrder: %d, lowestNum: %d}",
            isDiscovered ? "true" : "false",
            parentId,
            discoverOrder,
            lowestNum
        );
    }

    int getNilId() const {
        return nil;
    }

    bool isDiscovered;
    int parentId, discoverOrder, lowestNum;
    std::set<int> connectedIds;

private:
    static const int infinity = 1 << 30;
    static const int nil = -1;
};


class ArticulationPointFinder {
public:
    ArticulationPointFinder(const int vertexNum) {
        vertexes = std::vector<Vertex>(vertexNum);
    }

    void setEdge(const int vertexId1, const int vertexId2) {
        vertexes[vertexId1].addConnectedId(vertexId2);
        vertexes[vertexId2].addConnectedId(vertexId1);
    }

    void printArticulationPoints(const bool shouldPrintDebugInfo) {
        const int rootId = 0;

        depthFirstSearch(rootId, shouldPrintDebugInfo);


        const auto articulationPoints = findArticulationPoints(rootId);
        for (auto it = articulationPoints.begin(); it != articulationPoints.end(); ++it) {
            std::cout << (*it) << std::endl;
        }
    }

private:
    std::vector<Vertex> vertexes;

    void printVertexes() const {
        for (int id = 0; id < vertexes.size(); id++) {
            std::cout << "id " << id << ": ";
            vertexes[id].print();
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void updateAncestorLowestNums(const int vertexId) {
        // 自分自身の更新
        int lowestNum = vertexes[vertexId].discoverOrder;

        const auto connectedIds = vertexes[vertexId].connectedIds;
        for (auto id = connectedIds.begin(); id != connectedIds.end(); ++id) {
            if (vertexes[vertexId].parentId == *id) continue;
            if (!vertexes[*id].isDiscovered) continue;

            const int connectedDiscoverOrder = vertexes[*id].discoverOrder;
            lowestNum = std::min(lowestNum, connectedDiscoverOrder);
        }

        vertexes[vertexId].setLowestNum(lowestNum);

        // 先祖の更新
        int id = vertexId;
        while (vertexes[id].hasParent()) {
            const int parentId = vertexes[id].parentId;
            vertexes[parentId].setLowestNum(lowestNum);
            id = parentId;
        }
    }

    void depthFirstSearch(const int rootId, const bool shouldPrintDebugInfo) {
        const int vertexNum = vertexes.size();

        int discoverOrder = 0, nil = Vertex().getNilId();
        std::stack<int> discoverIdStack;


        vertexes[rootId].set(true, nil, discoverOrder);
        vertexes[rootId].setLowestNum(discoverOrder);
        discoverOrder++;
        discoverIdStack.push(rootId);
        while (!discoverIdStack.empty()) {
            if (shouldPrintDebugInfo) printVertexes();

            const int currentId = discoverIdStack.top();

            int nextId = nil;
            const auto connectedIds = vertexes[currentId].connectedIds;
            for (auto id = connectedIds.begin(); id != connectedIds.end(); ++id) {
                if (vertexes[*id].isDiscovered) continue;

                nextId = *id;
                break;
            }

            if (nextId != nil) {
                vertexes[nextId].set(true, currentId, discoverOrder);
                updateAncestorLowestNums(nextId);
                discoverOrder++;

                discoverIdStack.push(nextId);
            } else {
                discoverIdStack.pop();
            }
        }
    }

    std::set<int> findArticulationPoints(const int rootId) const {
        std::set<int> articulationPoints;

        // rootの判定
        int rootChildNum = 0;
        const auto connectedIds = vertexes[rootId].connectedIds;
        for (auto id = connectedIds.begin(); id != connectedIds.end(); ++id) {
            if (vertexes[*id].parentId == rootId) rootChildNum++;
        }
        if (rootChildNum >= 2) articulationPoints.insert(rootId);

        // root以外の判定
        for (int id = 0; id < vertexes.size(); id++) {
            const int parentId = vertexes[id].parentId;
            if (parentId == rootId || id == rootId) continue;

            if (vertexes[parentId].discoverOrder <= vertexes[id].lowestNum) articulationPoints.insert(parentId);
        }

        return articulationPoints;
    }
};


int main() {
    int vertexNum, edgeNum;
    std::cin >> vertexNum >> edgeNum;
    assert(1 <= vertexNum && vertexNum <= std::pow(10,5));
    assert(0 <= edgeNum && edgeNum <= std::pow(10,5));

    auto finder = ArticulationPointFinder(vertexNum);
    for (int i = 0; i < edgeNum; i++) {
        int vertexId1, vertexId2;
        std::cin >> vertexId1 >> vertexId2;
        finder.setEdge(vertexId1, vertexId2);
    }

    finder.printArticulationPoints(false);

    return 0;
}
