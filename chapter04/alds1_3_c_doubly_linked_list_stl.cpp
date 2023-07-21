#include<iostream>
#include<list>


int main() {
    std::list<int> list;

    // 標準入力からのコマンド取得とコマンド実行
    int n;
    std::cin >> n;
    if (!(1 <= n && n <= 2000000)) {
        std::cerr << "n is invalid." << std::endl;
        exit(EXIT_FAILURE);
    }

    for (int i=0; i<n; i++) {
        std::string command;
        int key;

        std::cin >> command;
        if (command == "insert") {
            std::cin >> key;
            list.push_front(key);
        } else if (command == "delete") {
            std::cin >> key;
            for (std::list<int>::iterator it = list.begin(); it != list.end(); it++) {
                if (*it == key) {
                    list.erase(it);
                    break;
                }
            }
        } else if (command == "deleteFirst") {
            list.pop_front();
        } else if (command == "deleteLast") {
            list.pop_back();
        } else {
            std::cerr << "Command is invalid." << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    // 結果表示
    for (std::list<int>::iterator it = list.begin(); it != list.end(); it++) {
        if (it != list.begin()) {
            std::cout << " ";
        }
        std::cout << *it;
    }
    std::cout << std::endl;

    return 0;
}
