#include<iostream>
#include<queue>


int main() {
    std::queue<std::pair<std::string, int> > queue;

    // 標準入力からのデータ取得
    int n, q;
    std::cin >> n;
    std::cin >> q;
    if (!(1 <= n && n <= 100000)) {
        std::cerr << "process number is invalid." << std::endl;
        exit(1);
    }
    if (!(1 <= q && q <= 1000)) {
        std::cerr << "q is invalid." << std::endl;
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        std::string name;
        int time;
        std::cin >> name;
        std::cin >> time;
        if (!(1 <= name.size() && name.size() <= 10)) {
            std::cerr << "Name is invalid." << std::endl;
            exit(1);
        }
        if (!(1 <= time && time <= 50000)) {
            std::cerr << "Time is invalid." << std::endl;
            exit(1);
        }
        queue.push(std::pair(name, time));
    }

    // 結果算出
    int totalTime = 0;
    while (!queue.empty()) {
        std::pair<std::string, int> p = queue.front(); queue.pop();

        int elapsedTime = std::min(p.second, q);
        int residualTime = p.second - elapsedTime;
        totalTime += elapsedTime;

        if (residualTime <= 0) {
            std::cout << p.first << " " << totalTime << std::endl;
        } else {
            queue.push(std::pair(p.first, residualTime));
        }
    }

    return 0;
}
