#include<iostream>


class Process {
public:
    Process() : m_name(""), m_time(0) {}
    Process(std::string name, int time) {
        if (!(1 <= name.size() && name.size() <= 10)) {
            std::cerr << "Name is invalid." << std::endl;
            exit(1);
        }
        if (!(1 <= time && time <= 50000)) {
            std::cerr << "Time is invalid." << std::endl;
            exit(1);
        }
        m_name = name;
        m_time = time;
    }
    std::string getName() const {
        return m_name;
    }
    int getTime() const {
        return m_time;
    }

private:
    std::string m_name;
    int m_time;
};


template <class T> class Queue {
public:
    Queue(const int size) : m_size(size), m_head(0), m_tail(0) {
        m_queue = new T[size];
    }
    ~Queue() {
        delete[] m_queue;
    }
    void initialize() {
        m_head = 0;
        m_tail = 0;
    }
    bool isEmpty() const {
        return m_head == m_tail;
    }
    bool isFull() const {
        return m_head == (m_tail + 1) % m_size;
    }
    void enqueue(const T x) {
        if (isFull()) {
            std::cerr << "Queue is full." << std::endl;
            exit(1);
        }
        m_queue[m_tail] = x;
        m_tail = (m_tail + 1) % m_size;
    }
    T dequeue() {
        if (isEmpty()) {
            std::cerr << "Queue is empty." << std::endl;
            exit(1);
        }
        T x = m_queue[m_head];
        m_head = (m_head + 1) % m_size;
        return x;
    }

private:
    const int m_size;
    int m_tail;
    int m_head;
    T* m_queue;
};


int main() {
    Queue<Process> queue = Queue<Process>(1000000);

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
        queue.enqueue(Process(name, time));
    }

    // 結果算出
    int totalTime = 0;
    while (!queue.isEmpty()) {
        Process p = queue.dequeue();

        int elapsedTime = std::min(p.getTime(), q);
        int residualTime = p.getTime() - elapsedTime;
        totalTime += elapsedTime;

        if (residualTime <= 0) {
            std::cout << p.getName() << " " << totalTime << std::endl;
        } else {
            queue.enqueue(Process(p.getName(), residualTime));
        }
    }

    return 0;
}
