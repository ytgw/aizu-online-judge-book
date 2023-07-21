#include<iostream>
#include<stack>


int main() {
    std::stack<int> stack;

    while (true) {
        std::string str;
        int num1, num2;

        std::cin >> str;
        if (std::cin.eof()) {
            break;
        }

        if (str == "+") {
            num1 = stack.top(); stack.pop();
            num2 = stack.top(); stack.pop();
            stack.push(num1 + num2);
        } else if (str == "-") {
            num1 = stack.top(); stack.pop();
            num2 = stack.top(); stack.pop();
            stack.push(num2 - num1);
        } else if (str == "*") {
            num1 = stack.top(); stack.pop();
            num2 = stack.top(); stack.pop();
            stack.push(num1 * num2);
        } else {
            stack.push(std::stoi(str));
        }
    }

    // 結果の表示
    std::cout << stack.top() << std::endl;

    return 0;
}
