#include<cassert>
#include<cmath>
#include<iostream>
#include<vector>


class WarshallFloyd {
public:
    WarshallFloyd(const int vertexNum) {
        distanceMatrix = std::vector<std::vector<long long> >(vertexNum, std::vector<long long>(vertexNum));

        for (int i = 0; i < vertexNum; i++) {
            for (int j = 0; j < vertexNum; j++) {
                distanceMatrix[i][j] = infinity;
            }
            distanceMatrix[i][i] = 0;
        }
    }

    void setWeight(const int i, const int j, const long long weight) {
        distanceMatrix[i][j] = weight;
    }

    void updateDistanceMatrix() {
        const int vertexNum = distanceMatrix.size();
        for (int k = 0; k < vertexNum; k++) {
            for (int i = 0; i < vertexNum; i++) {
                for (int j = 0; j < vertexNum; j++) {
                    if (distanceMatrix[i][k] == infinity || distanceMatrix[k][j] == infinity) continue;
                    distanceMatrix[i][j] = std::min(distanceMatrix[i][j], distanceMatrix[i][k] + distanceMatrix[k][j]);
                }
            }
        }
    }

    void print() const {
        // Negative Cycleのとき
        if (hasNegativeCycle()) {
            std::cout << "NEGATIVE CYCLE" << std::endl;
            return;
        }

        // Negative Cycleでないとき
        const int vertexNum = distanceMatrix.size();
        for (int i = 0; i < vertexNum; i++) {
            std::cout << getDistanceString(i, 0);
            for (int j = 1; j < vertexNum; j++) {
                std::cout << " " << getDistanceString(i, j);
            }
            std::cout << std::endl;
        }
    }

private:
    std::vector<std::vector<long long> > distanceMatrix;
    const long long infinity = std::pow(2, 60);

    bool hasNegativeCycle() const {
        for (int i = 0; i < distanceMatrix.size(); i++) {
            if (distanceMatrix[i][i] < 0) {
                return true;
            }
        }

        return false;
    }

    std::string getDistanceString(const int i, const int j) const {
        std::string str;
        const long long distance = distanceMatrix[i][j];
        if (distance == infinity) {
            str = "INF";
        } else {
            str = std::to_string(distance);
        }
        return str;
    }
};


int main() {
    int vertexNum, edgeNum;
    std::cin >> vertexNum >> edgeNum;
    assert(1 <= vertexNum && vertexNum <= 100);
    assert(0 <= edgeNum && edgeNum <= 9900);

    WarshallFloyd warshallFloyd = WarshallFloyd(vertexNum);
    for (int i = 0; i < edgeNum; i++) {
        int origin, destination;
        long long weight;
        std::cin >> origin >> destination >> weight;
        warshallFloyd.setWeight(origin, destination, weight);
    }

    warshallFloyd.updateDistanceMatrix();
    warshallFloyd.print();

    return 0;
}
