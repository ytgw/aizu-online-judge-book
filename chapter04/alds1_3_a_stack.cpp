#include<iostream>
#include<string>


class Stack {
public:
    Stack() {
        m_top = 0;
    }
    void initialize() {
        m_top = 0;
    }
    bool isEmpty() const {
        return m_top == 0;
    }
    bool isFull() const {
        return m_top >= m_size - 1;
    }
    void push(const int x) {
        if (isFull()) {
            std::cerr << "Stack is full." << std::endl;
            exit(1);
        }
        m_top++;
        m_stack[m_top] = x;
    }
    int pop() {
        if (isEmpty()) {
            std::cerr << "Stack is empty." << std::endl;
            exit(1);
        }
        m_top--;
        return m_stack[m_top + 1];
    }
private:
    const static int m_size = 1000;
    int m_top;
    int m_stack[m_size];
};


int main() {
    Stack stack = Stack();

    while (true) {
        std::string str;
        int num1, num2;

        std::cin >> str;
        if (std::cin.eof()) {
            break;
        }

        if (str == "+") {
            num1 = stack.pop();
            num2 = stack.pop();
            stack.push(num1 + num2);
        } else if (str == "-") {
            num1 = stack.pop();
            num2 = stack.pop();
            stack.push(num2 - num1);
        } else if (str == "*") {
            num1 = stack.pop();
            num2 = stack.pop();
            stack.push(num1 * num2);
        } else {
            stack.push(std::stoi(str));
        }
    }

    // 結果の表示
    std::cout << stack.pop() << std::endl;

    return 0;
}
