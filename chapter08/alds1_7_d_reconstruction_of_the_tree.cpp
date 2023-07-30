#include<iostream>
#include<vector>


int find(const int array[], const int value, const int beginIdx, const int endIdx) {
    for (int i=beginIdx; i<endIdx; i++) {
        if (array[i] == value) {
            return i;
        }
    }

    // 存在しない場合
    return -1;
}


void calcPostOrder(
    const int preOrder[],
    const int inOrder[],
    const int nodeNum,
    const int preOrderBegin,
    const int inOrderBegin,
    const int postOrderBegin,
    int postOrder[]
) {
    const int root = preOrder[preOrderBegin];
    if (nodeNum < 0) {
        exit(EXIT_FAILURE);
    }
    if (nodeNum == 0) {
        return;
    }

    const int inOrderRootIdx = find(inOrder, root, inOrderBegin, inOrderBegin + nodeNum);
    if (inOrderRootIdx == -1) {
        std::cerr << "root is not find." << std::endl;
        exit(EXIT_FAILURE);
    }

    // 返り値作成
    const int leftNodeNum = inOrderRootIdx - inOrderBegin;
    const int rightNodeNum = nodeNum - leftNodeNum - 1;
    calcPostOrder(preOrder, inOrder, leftNodeNum, preOrderBegin + 1, inOrderBegin, postOrderBegin, postOrder);
    calcPostOrder(preOrder, inOrder, rightNodeNum, preOrderBegin + leftNodeNum + 1, inOrderRootIdx + 1, postOrderBegin + leftNodeNum, postOrder);
    postOrder[postOrderBegin + nodeNum - 1] = root;
    return;
}


int main() {
    // 標準入力からのデータ取得
    int nodeNum;
    std::cin >> nodeNum;
    if (!(1 <= nodeNum <= 100)) {
        std::cerr << "nodeNum is invalid.";
        exit(EXIT_FAILURE);
    }

    int preOrder[nodeNum], inOrder[nodeNum];
    for (int i=0; i<nodeNum; i++)  std::cin >> preOrder[i];
    for (int i=0; i<nodeNum; i++)  std::cin >> inOrder[i];


    // 結果表示
    int postOrder[nodeNum];
    const int root = preOrder[0];
    calcPostOrder(preOrder, inOrder, nodeNum, 0, 0, 0, postOrder);

    std::cout << postOrder[0];
    for (int i=1; i<nodeNum; i++) {
        std::cout << " " << postOrder[i];
    }
    std::cout << std::endl;

    return 0;
}
