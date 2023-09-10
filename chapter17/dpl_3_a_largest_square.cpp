#include<algorithm>
#include<cassert>
#include<iostream>
#include<vector>
#include<set>


class LargestSquareSolver {
public:
    LargestSquareSolver(const std::vector<std::vector<int>> tiles): tiles(tiles) {}
    int calcArea() const {
        const int height = tiles.size();
        const int width = tiles[0].size();

        // lengthMatrix[h][w]はh,wを右下にした正方形の辺の長さを格納する。
        auto lengthMatrix = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
        initialize(lengthMatrix);

        for (int h = 1; h < height; h++) {
            for (int w = 1; w < width; w++) {
                if (tiles[h][w] == 1) {
                    lengthMatrix[h][w] = 0;
                    continue;
                }

                if (tiles[h][w] == 0) {
                    int length = std::min(lengthMatrix[h-1][w], lengthMatrix[h][w-1]);
                    length = std::min(length, lengthMatrix[h-1][w-1]);
                    lengthMatrix[h][w] = length + 1;
                    continue;
                }

                assert(false);
            }
        }

        const int maxLength = getMaxElement(lengthMatrix);
        return maxLength * maxLength;
    }

private:
    const std::vector<std::vector<int>> tiles;

    void initialize(std::vector<std::vector<int>>& lengthMatrix) const {
        const int height = tiles.size();
        const int width = tiles[0].size();

        for (int h = 0; h < height; h++) {
            if (tiles[h][0] == 0) lengthMatrix[h][0] = 1;
            else if (tiles[h][0] == 1) lengthMatrix[h][0] = 0;
            else assert(false);
        }

        for (int w = 0; w < width; w++) {
            if (tiles[0][w] == 0) lengthMatrix[0][w] = 1;
            else if (tiles[0][w] == 1) lengthMatrix[0][w] = 0;
            else assert(false);
        }
    }

    int getMaxElement(const std::vector<std::vector<int>> lengthMatrix) const {
        const int height = tiles.size();
        const int width = tiles[0].size();

        int maxElement = lengthMatrix[0][0];
        for (int h = 0; h < height; h++) {
            for (int w = 0; w < width; w++) {
                maxElement = std::max(maxElement, lengthMatrix[h][w]);
            }
        }

        return maxElement;
    }
};


int main() {
    int height, width;
    std::cin >> height >> width;

    auto tiles = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            std::cin >> tiles[h][w];
        }
    }

    // 計算
    auto solver = LargestSquareSolver(tiles);
    std::cout << solver.calcArea() << std::endl;

    return 0;
}
