#include<cassert>
#include<cmath>
#include<iostream>


int fibonacci(const int n) {
    assert(0 <= n);
    if (n == 0 || n == 1) return 1;

    int f1 = 1;
    int f2 = 1;
    int f;
    for (int i = 2; i <= n; i++) {
        f = f1 + f2;
        f2 = f1;
        f1 = f;
    }
    return f;
}


int main() {
    int n;
    std::cin >> n;
    assert(0 <= n && n <= 44);

    std::cout << fibonacci(n) << std::endl;

    return 0;
}
