#include<iostream>


class Dictionary {
public:
    Dictionary() {
        m_table = new int[m_tableSize];
        for (int i=0; i<m_tableSize; i++) {
            m_table[i] = m_nill;
        }
    }
    ~Dictionary() {
        delete[] m_table;
    }
    bool find(const std::string keyStr) const {
        // 存在するときtrueを返す。
        const long long key = getKey(keyStr);
        for (int collisionNum=0; collisionNum<m_tableSize; collisionNum++) {
            const int tableIdx = hash(key, collisionNum);
            if (m_table[tableIdx] == key) return true;
            if (m_table[tableIdx] == m_nill) return false;
        }
        std::cerr << "can not find key." << std::endl;
        exit(EXIT_FAILURE);
    }
    void insert(const std::string keyStr) {
        const long long key = getKey(keyStr);
        for (int collisionNum=0; collisionNum<m_tableSize; collisionNum++) {
            const int tableIdx = hash(key, collisionNum);
            if (m_table[tableIdx] == m_nill) {
                m_table[tableIdx] = key;
                return;
            }
        }
        std::cerr << "can not insert key." << std::endl;
        exit(EXIT_FAILURE);
    }

private:
    const int m_tableSize = 1046527;
    const int m_nill = -1;
    int* m_table;

    int getChar(const char ch) const {
        // 文字から数字に変換する。
        if (ch == 'A') return 1;
        if (ch == 'C') return 2;
        if (ch == 'G') return 3;
        if (ch == 'T') return 4;
        return 0;
    }
    long long getKey(const std::string keyStr) const {
        // 文字列から数値のkeyに変換する。
        long long key = 0, p = 1;
        for (int i=0; i<keyStr.size(); i++) {
            const int charNum = 5;
            key += p * getChar(keyStr[i]);
            p *= charNum;
        }
        return key;
    }

    int hash1(const long long key) const {
        return key % m_tableSize;
    }
    int hash2(const long long key) const {
        return 1 + (key % (m_tableSize - 1));
    }
    int hash(const long long key, const int i) const {
        return (hash1(key) + i*hash2(key)) % m_tableSize;
    }
};


int main() {
    Dictionary hash;

    // 標準入力からの命令取得と実行
    int commandNum;
    std::cin >> commandNum;

    std::string command, keyStr;
    for (int i=0; i<commandNum; i++) {
        std::cin >> command >> keyStr;

        if (command == "insert") {
            hash.insert(keyStr);
        } else if (command == "find") {
            if (hash.find(keyStr)) {
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
