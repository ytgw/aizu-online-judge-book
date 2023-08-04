#include<iostream>
#include<map>


int main() {
    std::map<std::string, bool> hash;

    // 標準入力からの命令取得と実行
    int commandNum;
    std::cin >> commandNum;

    std::string command, keyStr;
    for (int i=0; i<commandNum; i++) {
        std::cin >> command >> keyStr;

        if (command == "insert") {
            hash[keyStr] = true;
        } else if (command == "find") {
            const bool hasKey = (hash.find(keyStr) != hash.end());
            if (hasKey) {
                std::cout << "yes" << std::endl;
            } else {
                std::cout << "no" << std::endl;
            }
        } else {
            std::cerr << "Command is invalid." << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
