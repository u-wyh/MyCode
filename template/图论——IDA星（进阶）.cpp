//https://acm.hdu.edu.cn/showproblem.php?pid=1667
//https://www.cnblogs.com/LuckyGlass-blog/p/9061081.html
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <deque>
using namespace std;

// 定义棋盘转换和移动规则
const int initialPositions[][3] = {
    {1, 0}, {1, 1}, {1, 0}, {1, 1}, {1, 2}, {1, 2}, {2, 0, 2}, {1, 2},
    {2, 1, 2}, {1, 2}, {1, 2}, {1, 0}, {1, 1}, {1, 3}, {1, 3}, {2, 0, 3},
    {1, 3}, {2, 1, 3}, {1, 3}, {1, 3}, {1, 0}, {1, 1}, {1, 0}, {1, 1}
};
const int movements[][8] = {
    {0, 0, 2, 2, 2, 3, 2, 4}, {1, 0, 2, 4, 2, 3, 4, 4}, {2, 1, 0, 2, 2, 1, 2, 4},
    {3, 1, 0, 4, 2, 1, 4, 4}, {1, 1, 2, 4, 2, 3, 4, 4}, {0, 1, 2, 2, 2, 3, 2, 4},
    {3, 0, 0, 4, 2, 1, 4, 4}, {2, 0, 0, 2, 2, 1, 2, 4}
};
const int inverseMovements[8] = {5, 4, 7, 6, 1, 0, 3, 2}; // 逆移动，用于撤销操作

deque<int> lines[4]; // 存储四行的方块
int currentDepth; // 当前搜索深度
char solution[107]; // 存储解决方案

// 获取指定位置的迭代器
deque<int>::iterator getPosition(int row, int col) {
    return lines[row].begin() + col;
}

// 计算当前配置的优先级（中心方块统一程度）
//计算预期的函数
int getPriority() {
    int counts[4] = {0};
    counts[*getPosition(0, 2)]++; counts[*getPosition(2, 3)]++; counts[*getPosition(1, 2)]++;
    counts[*getPosition(0, 3)]++; counts[*getPosition(1, 3)]++;
    counts[*getPosition(0, 4)]++; counts[*getPosition(3, 3)]++; counts[*getPosition(1, 4)]++;
    return 8 - max(max(counts[1], counts[2]), counts[3]);
}

// 执行移动操作
void performMove(int moveType) {
    if (movements[moveType][1]) { // 循环移动
        //将最后一个移到前面
        int last = lines[movements[moveType][0]].back();
        lines[movements[moveType][0]].pop_back();
        lines[movements[moveType][0]].push_front(last);
    } else { // 顺序移动
        int first = lines[movements[moveType][0]].front();
        lines[movements[moveType][0]].pop_front();
        lines[movements[moveType][0]].push_back(first);
    }
    *getPosition(movements[moveType][2], movements[moveType][3]) =
        *getPosition(movements[moveType][0], movements[moveType][4]);
    *getPosition(movements[moveType][5], movements[moveType][6]) =
        *getPosition(movements[moveType][0], movements[moveType][7]);
}

// 撤销移动操作
void undoMove(int moveType) {
    performMove(inverseMovements[moveType]);
}

// 使用A*搜索算法寻找解决方案
bool aStarSearch(int depth) {
    int priority = getPriority();
    if (depth + priority > currentDepth)
        return false;
    if (priority == 0)
        return true;

    for (int i = 0; i < 8; i++) {
        solution[depth] = i + 'A';
        performMove(i);

        if (aStarSearch(depth + 1))
            return true;

        undoMove(i);
        solution[depth] = '\0';
    }

    return false;
}

int main() {
    while (true) {
        for (int i = 0; i < 4; i++) lines[i].clear();
        char input[105];
        fgets(input, sizeof(input), stdin);
        if (input[0] == '0') break;

        // 解析输入，初始化棋盘
        for (int i = 0, j = 0; i < 24; i++, j += 2) {
            for (int k = 1; k <= initialPositions[i][0]; k++) {
                lines[initialPositions[i][k]].push_back(input[j] - '0');
            }
        }

        currentDepth = 0;
        memset(solution, '\0', sizeof(solution));

        // 搜索解决方案
        while (!aStarSearch(0)) {
            currentDepth++;
        }

        if (currentDepth == 0) {
            printf("No moves needed\n");
        } else {
            printf("%s\n", solution);
        }

        // 输出中心方块的符号
        printf("%d\n", *getPosition(0, 2));
    }

    return 0;
}
