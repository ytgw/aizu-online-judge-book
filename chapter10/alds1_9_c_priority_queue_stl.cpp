#include<iostream>
#include<cassert>
#include<cmath>
#include<queue>


int main() {
    std::priority_queue<int> queue;
    while (true) {
        std::string command;
        std::cin >> command;
        if (command == "end") {
            break;
        } else if (command == "insert") {
            int key;
            std::cin >> key;
            queue.push(key);
        } else if (command == "extract") {
            std::cout << queue.top() << std::endl;
            queue.pop();
        } else {
            std::cerr << "Command is invalid." << std::endl;
        }
    }

    return 0;
}
