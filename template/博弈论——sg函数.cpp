// 分裂游戏
// 一共有n个瓶子，编号为0 ~ n-1，第i瓶里装有nums[i]个糖豆，每个糖豆认为无差别
// 有两个玩家轮流取糖豆，每一轮的玩家必须选i、j、k三个编号，并且满足i < j <= k
// 当前玩家从i号瓶中拿出一颗糖豆，分裂成两颗糖豆，并且往j、k瓶子中各放入一颗，分裂的糖豆继续无差别
// 要求i号瓶一定要有糖豆，如果j == k，那么相当于从i号瓶中拿出一颗，向另一个瓶子放入了两颗
// 如果轮到某个玩家发现所有糖豆都在n-1号瓶里，导致无法行动，那么该玩家输掉比赛
// 先手希望知道，第一步如何行动可以保证自己获胜，要求返回字典序最小的行动
// 第一步从0号瓶拿出一颗糖豆，并且往2、3号瓶中各放入一颗，可以确保最终自己获胜
// 第一步从0号瓶拿出一颗糖豆，并且往11、13号瓶中各放入一颗，也可以确保自己获胜
// 本题要求每个瓶子的编号看做是一个字符的情况下，最小的字典序，所以返回"0 2 3"
// 如果先手怎么行动都无法获胜，返回"-1 -1 -1"
// 先手还希望知道自己有多少种第一步取糖的行动，可以确保自己获胜，返回方法数
// 测试链接 : https://www.luogu.com.cn/problem/P3185
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 21; // 最大瓶子数量
const int MAXV = 101; // SG 值的最大范围

int nums[MAXN]; // 每个瓶子中的糖豆数量
int sg[MAXN]; // 每个位置的 SG 值
bool appear[MAXV]; // 用于计算 SG 值的辅助数组

// 预处理 SG 值
void build() {
    for (int i = 1; i < MAXN; i++) {
        memset(appear, false, sizeof(appear)); // 重置 appear 数组
        for (int j = i - 1; j >= 0; j--) {
            for (int k = j; k >= 0; k--) {
                appear[sg[j] ^ sg[k]] = true; // 标记 SG 值的组合
            }
        }
        for (int s = 0; s < MAXV; s++) {
            if (!appear[s]) {
                sg[i] = s; // 找到最小的未出现的 SG 值
                break;
            }
        }
    }
}

// 计算当前状态的解
string compute(int n) {
    int eor = 0; // 所有糖果的 SG 值异或和
    for (int i = n - 1; i >= 0; i--) {
        if (nums[i] % 2 == 1) {
            eor ^= sg[i]; // 奇数个糖豆才参与异或
        }
    }
    if (eor == 0) {
        return "-1 -1 -1\n0"; // 无法获胜
    }
    int cnt = 0, a = -1, b = -1, c = -1, pos;
    for (int i = n - 1; i >= 1; i--) {
        if (nums[i] > 0) {
            for (int j = i - 1; j >= 0; j--) {
                for (int k = j; k >= 0; k--) {
                    pos = eor ^ sg[i] ^ sg[j] ^ sg[k]; // 计算新的 SG 值
                    if (pos == 0) {
                        cnt++; // 统计可行解的数量
                        if (a == -1) {
                            a = i;
                            b = j;
                            c = k; // 记录字典序最小的解
                        }
                    }
                }
            }
        }
    }
    return to_string(n - 1 - a) + " " + to_string(n - 1 - b) + " " + to_string(n - 1 - c) + "\n" + to_string(cnt);
}

int main() {
    build(); // 预处理 SG 值
    int t, n;
    cin >> t; // 测试用例数量
    while (t--) {
        cin >> n; // 瓶子数量
        for (int j = n - 1; j >= 0; j--) {
            cin >> nums[j]; // 输入每个瓶子中的糖豆数量
        }
        cout << compute(n) << endl; // 输出结果
    }
    return 0;
}
