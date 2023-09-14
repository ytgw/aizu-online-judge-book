#include<cassert>
#include<cmath>
#include<iostream>


int calcGreatestCommonDivisor(const int n1, const int n2) {
    assert(n1 > 0);
    assert(n2 > 0);

    int residual, min;
    if (n1 > n2) {
        residual = n1 % n2;
        min = n2;
    } else {
        residual = n2 % n1;
        min = n1;
    }

    if (residual == 0) return min;

    return calcGreatestCommonDivisor(min, residual);
}


int main() {
    int n1, n2;
    std::cin >> n1 >> n2;

    std::cout << calcGreatestCommonDivisor(n1, n2) << std::endl;

    return 0;
}
