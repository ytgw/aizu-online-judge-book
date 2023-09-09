#include<algorithm>
#include<cassert>
#include<iostream>
#include<vector>


class MinCoinNumCalculator {
public:
    MinCoinNumCalculator(const std::vector<int> coinTypes) {
        this->coinTypes = coinTypes;
        std::sort(this->coinTypes.begin(), this->coinTypes.end());
        assert(this->coinTypes[0] == 1);
    }

    int calcMinCoinNum(const int fee) {
        assert(fee > 0);
        coinNumMatrix = std::vector<std::vector<int>>(coinTypes.size(), std::vector<int>(fee + 1, 0));
        for (int maxCoinId = 0; maxCoinId < coinTypes.size(); maxCoinId++) {
            updateMatrix(maxCoinId);
        }
        return coinNumMatrix[coinTypes.size() - 1][fee];
    }

private:
    // コインのタイプで1,10,50,100などが昇順でソートされている
    std::vector<int> coinTypes;
    // minCoinNums[maxCoinId][fee]は、0-maxCoinTypeIdのコインで料金feeを払うのに最小のコイン数
    std::vector<std::vector<int>> coinNumMatrix;

    void updateMatrix(const int maxCoinId) {
        const int maxFee = coinNumMatrix[0].size();
        if (maxCoinId == 0) {
            for (int fee = 1; fee < maxFee; fee++) {
                coinNumMatrix[maxCoinId][fee] = fee;
            }
            return;
        }

        for (int fee = 1; fee < maxFee; fee++) {
            if (fee >= coinTypes[maxCoinId]) {
                coinNumMatrix[maxCoinId][fee] = std::min(
                    coinNumMatrix[maxCoinId - 1][fee],
                    coinNumMatrix[maxCoinId][fee - coinTypes[maxCoinId]] + 1
                );
            } else {
                coinNumMatrix[maxCoinId][fee] = coinNumMatrix[maxCoinId - 1][fee];
            }
        }
    }
};


int main() {
    int fee, coinTypeNum;
    std::cin >> fee >> coinTypeNum;

    std::vector<int> coinTypes;
    for (int i = 0; i < coinTypeNum; i++) {
        int coinType;
        std::cin >> coinType;
        coinTypes.push_back(coinType);
    }

    // 計算
    MinCoinNumCalculator calculator = MinCoinNumCalculator(coinTypes);
    std::cout << calculator.calcMinCoinNum(fee) << std::endl;

    return 0;
}
