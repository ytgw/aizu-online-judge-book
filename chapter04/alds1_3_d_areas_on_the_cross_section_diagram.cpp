#include<iostream>
#include<stack>
#include<vector>


class PositionAreaPair {
public:
    PositionAreaPair(int position, int area) : position(position), area(area) {}
    const int position;
    const int area;
};


int main() {
    // 標準入力からのデータ取得
    std::string str;
    std::cin >> str;
    if (!(1 <= str.size() && str.size() <= 20000)) {
        std::cerr << "String is invalid.";
        exit(EXIT_FAILURE);
    }

    // 断面積計算
    std::stack<int> positions;
    int totalArea = 0;
    std::stack<PositionAreaPair > positionAreaPairs;
    for (int i=0; i<str.size(); i++) {
        char c = str[i];
        if (c == '\\') {
            positions.push(i);
        } else if (c == '/') {
            if (!positions.empty()) {
                // /から始まるときなどにエラーを起こさないようにする
                int position = positions.top();
                positions.pop();
                totalArea += (i - position);

                // 各面積の算出
                int area = i - position;
                while (true) {
                    if (positionAreaPairs.empty()) break;

                    // 水たまりが分かれているとき
                    bool isSeparate = (positionAreaPairs.top().position < position);
                    if (isSeparate) break;

                    // 水たまりがつながっているとき
                    area += positionAreaPairs.top().area;
                    positionAreaPairs.pop();
                }
                positionAreaPairs.push(PositionAreaPair(position, area));
            }
        } else if (c == '_') {
            // 何もしない
        } else {
            std::cerr << "Char is invalid.";
            exit(EXIT_FAILURE);
        }
    }

    // 結果の表示
    // 総面積
    std::cout << totalArea << std::endl;

    // 面積数
    std::cout << positionAreaPairs.size();

    // 各面積
    std::vector<int> areas;
    while (!positionAreaPairs.empty()) {
        areas.push_back(positionAreaPairs.top().area);
        positionAreaPairs.pop();
    }
    for (int i = areas.size()-1; i>=0; i--) {
        std::cout << " " << areas[i];
    }
    std::cout << std::endl;

    return 0;
}
