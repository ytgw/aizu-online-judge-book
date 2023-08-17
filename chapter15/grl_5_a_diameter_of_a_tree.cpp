#include<algorithm>
#include<array>
#include<cassert>
#include<cmath>
#include<iostream>
#include<set>
#include<stack>
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
    const int source, destination, weight;
};


class Graph {
public:
    Graph(const int nodeNum) {
        outEdges = std::vector<std::vector<Edge>>(nodeNum);
    }

    void addEdge(const int source, const int destination, const int weight) {
        outEdges[source].push_back(Edge(source, destination, weight));
        outEdges[destination].push_back(Edge(destination, source, weight));
    }

    int calcDiameter() const {
        const int startId = findFarthestNode(0).first;
        const int diameter = findFarthestNode(startId).second;
        return diameter;
    }

private:
    std::vector<std::vector<Edge>> outEdges;

    std::pair<int, int> findFarthestNode(const int startId) const {
        const int nodeNum = outEdges.size();
        const int infinity = std::pow(10, 9);
        auto distances = std::vector<int>(nodeNum, -1);
        auto isSearched = std::vector<bool>(nodeNum, false);

        isSearched[startId] = true;
        distances[startId] = 0;
        depthFirstSearch(startId, distances, isSearched);

        const int farthestId = getMaxIndex(distances);
        const int farthestDistance = distances[farthestId];
        return std::pair(farthestId, farthestDistance);
    }

    void depthFirstSearch(const int nodeId, std::vector<int>& distances, std::vector<bool>& isSearched) const {
        for (auto edge = outEdges[nodeId].cbegin(); edge != outEdges[nodeId].cend(); ++edge) {
            const int nextId = (*edge).getDestination();
            const int weight = (*edge).getWeight();

            if (isSearched[nextId]) continue;

            isSearched[nextId] = true;
            distances[nextId] = distances[nodeId] + weight;
            depthFirstSearch(nextId, distances, isSearched);
        }
    }

    int getMaxIndex(const std::vector<int> vector) const {
        int maxIndex = 0;
        for (int i = 0; i < vector.size(); i++) {
            if (vector[maxIndex] < vector[i]) {
                maxIndex = i;
            }
        }
        return maxIndex;
    }
};


int main() {
    int nodeNum;
    std::cin >> nodeNum;
    assert(1 <= nodeNum && nodeNum <= std::pow(10,5));

    auto graph = Graph(nodeNum);
    for (int i = 0; i < nodeNum - 1; i++) {
        int source, destination, weight;
        std::cin >> source >> destination >> weight;
        assert(0 <= source && source <= nodeNum - 1);
        assert(0 <= destination && destination <= nodeNum - 1);
        assert(0 <= weight && weight <= 1000);

        graph.addEdge(source, destination, weight);
    }

    std::cout << graph.calcDiameter() << std::endl;

    return 0;
}
