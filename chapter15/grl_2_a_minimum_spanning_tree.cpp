#include<algorithm>
#include<cassert>
#include<cmath>
#include<iostream>
#include<vector>


class Edge {
public:
    Edge(const int source, const int destination, const int weight) : source(source), destination(destination), weight(weight) {}

    int getSource() const {
        return source;
    }

    int getDestination() const {
        return destination;
    }

    int getWeight() const {
        return weight;
    }

private:
    int source, destination, weight;  // constをつけるとソート箇所でコンパイルエラーが発生
};


class DisjointSet {
public:
    DisjointSet(const int elementNum) : elementNum(elementNum) {
        parents = std::vector<int>(elementNum);

        for (int i = 0; i < elementNum; i++) {
            makeSet(i);
        }
    }

    void unite(const int x, const int y) {
        const int root = findRoot(x);
        updateParents(x, root);
        updateParents(y, root);
        // print();
    }

    bool same(const int x, const int y) const {
        if (findRoot(x) == findRoot(y)) {
            return true;
        } else {
            return false;
        }
    }

private:
    const int elementNum;
    std::vector<int> parents;

    void makeSet(const int x) {
        parents[x] = x;
    }

    void updateParents(int x, const int root) {
        while (x != parents[x]) {
            int parent = parents[x];
            parents[x] = root;
            x = parent;
        }
        parents[x] = root;
    }

    int findRoot(int x) const {
        while (x != parents[x]) {
            x = parents[x];
        }
        return x;
    }

    void print() const {
        std::cout << "(x, set(x)): ";
        for (int i = 0; i < elementNum; i++) {
            printf("(id=%d, parent=%d, root=%d), ", i, parents[i], findRoot(i));
        }
        std::cout << std::endl;
    }
};


int kruskal(const int nodeNum, std::vector<Edge>& edges) {
    std::sort(
        edges.begin(),
        edges.end(),
        [](const Edge e1, const Edge e2) {return e1.getWeight() < e2.getWeight();}
    );

    DisjointSet vertexSet = DisjointSet(nodeNum);
    std::vector<Edge> minimumSpanningTreeEdges;

    int totalWeight = 0;
    for (auto edge = edges.cbegin(); edge != edges.cend(); ++edge) {
        const int sourceVertex = (*edge).getSource();
        const int destinationVertex = (*edge).getDestination();
        if (!vertexSet.same(sourceVertex, destinationVertex)) {
            vertexSet.unite(sourceVertex, destinationVertex);
            totalWeight += (*edge).getWeight();
        }
    }

    return totalWeight;
}


int main() {
    int nodeNum, edgeNum;
    std::cin >> nodeNum >> edgeNum;
    assert(1 <= nodeNum && nodeNum <= std::pow(10,4));
    assert(0 <= edgeNum && edgeNum <= std::pow(10,5));

    std::vector<Edge> edges;
    for (int i = 0; i < edgeNum; i++) {
        int source, destination, weight;
        std::cin >> source >> destination >> weight;
        assert(0 <= source && source <= nodeNum - 1);
        assert(0 <= destination && destination <= nodeNum - 1);
        assert(0 <= weight && weight <= std::pow(10,4));

        edges.push_back(Edge(source, destination, weight));
    }

    std::cout << kruskal(nodeNum, edges) << std::endl;

    return 0;
}
