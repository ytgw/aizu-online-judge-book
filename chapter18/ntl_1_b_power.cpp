#include<cmath>
#include<iostream>


unsigned long long calcPowerResidual(
    const unsigned long long base,
    const unsigned long long exponent,
    const unsigned long long divide
) {
    // base^ex % divideを返す。

    if (exponent == 0) return 1 % divide;

    const int newBase = (base * base) % divide;
    const int newExponent = exponent / 2;
    int residual = calcPowerResidual(newBase, newExponent, divide);
    if (exponent % 2 != 0) {
        residual = ((residual % divide) * (base % divide)) % divide;
    }

    return residual;
}


int main() {
    const unsigned long long divide = std::pow(10, 9) + 7;
    unsigned long long base, exponent;
    std::cin >> base >> exponent;

    std::cout << calcPowerResidual(base, exponent, divide) << std::endl;

    return 0;
}
