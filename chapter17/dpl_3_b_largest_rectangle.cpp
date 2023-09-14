#include<algorithm>
#include<cassert>
#include<iostream>
#include<vector>
#include<stack>


class LargestRectangleSolver {
public:
    LargestRectangleSolver(const std::vector<std::vector<int>> tiles): tiles(tiles) {}
    int calcArea() const {
        const std::vector<std::vector<int>> histograms = createHistograms();

        int maxArea = -1;
        for (int h = 0; h < tiles.size(); h++) {
            maxArea = std::max(maxArea, calcMaxAreaFromHistogram(histograms[h]));
        }

        return maxArea;
    }

private:
    const std::vector<std::vector<int>> tiles;

    bool isDirty(const int tile) const {
        if (tile == 0) return false;
        if (tile == 1) return true;
        assert(false);
    }

    std::vector<std::vector<int>> createHistograms() const {
        const int height = tiles.size();
        const int width = tiles[0].size();

        auto histograms = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
        for (int w = 0; w < width; w++) {
            if (isDirty(tiles[0][w])) {
                histograms[0][w] = 0;
            } else {
                histograms[0][w] = 1;
            }
        }

        for (int h = 1; h < height; h++) {
            for (int w = 0; w < width; w++) {
                if (isDirty(tiles[h][w])) {
                    histograms[h][w] = 0;
                } else {
                    histograms[h][w] = histograms[h - 1][w] + 1;
                }
            }
        }

        return histograms;
    }

    int calcMaxAreaFromHistogram(const std::vector<int> histogram) const {
        const int width = histogram.size();
        std::stack<std::pair<int, int>> rectangles;

        int maxArea = -1;
        for (int w = 0; w < width; w++) {
            const int rectLeft = w;
            const int rectHeight = histogram[w];
            std::pair<int, int> rectangle = std::pair(rectLeft, rectHeight);

            if (rectangles.empty()) {
                rectangles.push(rectangle);
                continue;
            }

            int stackHeight = rectangles.top().second;
            if (stackHeight < rectHeight) {
                rectangles.push(rectangle);
                continue;
            }

            if (stackHeight == rectHeight) {
                continue;
            }

            // stackHeight > rectHeightの場合
            int stackLeft;
            while (!rectangles.empty() && rectangles.top().second > rectHeight) {
                stackLeft = rectangles.top().first;
                const int stackHeight = rectangles.top().second;
                rectangles.pop();
                maxArea = std::max(maxArea, stackHeight * (w - stackLeft));
            }
            rectangle = std::pair(stackLeft, rectHeight);
            rectangles.push(rectangle);
        }

        while (!rectangles.empty()) {
            const int stackLeft = rectangles.top().first;
            const int stackHeight = rectangles.top().second;
            rectangles.pop();
            maxArea = std::max(maxArea, stackHeight * (width - stackLeft));
        }

        return maxArea;
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
    auto solver = LargestRectangleSolver(tiles);
    std::cout << solver.calcArea() << std::endl;

    return 0;
}
