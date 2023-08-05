#include<cassert>
#include<cmath>
#include<iostream>


int calc_longest_common_sequence_length(std::string seq1, std::string seq2) {
    const int len1 = seq1.length();
    const int len2 = seq2.length();

    int lcs_lens[len1 + 1][len2 + 1];

    for (int i=0; i<=len1; i++) lcs_lens[i][0] = 0;
    for (int i=0; i<=len2; i++) lcs_lens[0][i] = 0;

    for (int i1=1; i1<=len1; i1++) {
        for (int i2=1; i2<=len2; i2++) {
            if (seq1[i1 - 1] == seq2[i2 - 1]) {
                lcs_lens[i1][i2] = lcs_lens[i1 - 1][i2 - 1] + 1;
            } else {
                lcs_lens[i1][i2] = std::max(lcs_lens[i1][i2 - 1], lcs_lens[i1 - 1][i2]);
            }
        }
    }
    return lcs_lens[len1][len2];
}


int main() {
    int datasetNum;
    std::cin >> datasetNum;
    assert(1 <= datasetNum && datasetNum <= 150);

    for (int i=0; i<datasetNum; i++) {
        std::string seq1, seq2;
        std::cin >> seq1 >> seq2;

        std::cout << calc_longest_common_sequence_length(seq1, seq2) << std::endl;;
    }

    return 0;
}
