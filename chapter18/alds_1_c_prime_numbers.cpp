#include<cassert>
#include<cmath>
#include<iostream>


bool isPrime(const int number) {
    // numberが素数ならtrueを返す。
    assert(number >= 0);

    if (number == 1) return false;

    // numberまでの剰余でなく、sqrt(number)までの剰余を見ればいい。
    const int sqrt = std::sqrt(number);
    for (int i = 2; i <= sqrt; i++) {
        if (number % i == 0) {
            return false;
        }
    }

    return true;
}


int main() {
    int size;
    std::cin >> size;

    int count = 0;
    for (int _ = 0; _ < size; _++) {
        int number;
        std::cin >> number;
        if (isPrime(number)) {
            count++;
        }
    }

    std::cout << count << std::endl;

    return 0;
}
