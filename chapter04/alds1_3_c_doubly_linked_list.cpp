#include<iostream>


class Node {
public:
    int key;
    Node *prev, *next;
};


class DoublyLinkedList {
public:
    DoublyLinkedList() {
        initialize();
    }
    ~DoublyLinkedList() {
        Node *cur = nil->next;
        while(cur != nil) {
            Node *presentNode = cur;
            cur = cur->next;
            delete presentNode;
        }
        delete nil;
    }
    void initialize() {
        nil = new Node();
        nil->prev = nil;
        nil->next = nil;
    }
    Node* lineSearch(int key) const {
        Node *cur = nil->next;
        while( cur != nil && cur->key != key) {
            cur = cur->next;
        }
        return cur;
    }
    void insert(int key) {
        // 先頭に挿入
        Node *x = new Node();
        x->key = key;

        x->next = nil->next;
        nil->next->prev = x;

        nil->next = x;
        x->prev = nil;
    }
    void deleteFirst() {
        deleteNode(nil->next);
    }
    void deleteLast() {
        deleteNode(nil->prev);
    }
    void deleteKey(int key) {
        deleteNode(lineSearch(key));
    }
    void print() const {
        Node *cur = nil->next;
        std::cout << cur->key;
        cur = cur->next;

        while(cur != nil) {
            std::cout << " " << cur->key;
            cur = cur->next;
        }
        std::cout << std::endl;
    }
private:
    Node *nil;  // 番兵ノード
    void deleteNode(Node *t) {
        if (t == nil) return;
        t->prev->next = t->next;
        t->next->prev = t->prev;
        delete t;
    }
};


int main() {
    DoublyLinkedList list;

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
            list.insert(key);
        } else if (command == "delete") {
            std::cin >> key;
            list.deleteKey(key);
        } else if (command == "deleteFirst") {
            list.deleteFirst();
        } else if (command == "deleteLast") {
            list.deleteLast();
        } else {
            std::cerr << "Command is invalid." << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    // 結果表示
    list.print();

    return 0;
}
