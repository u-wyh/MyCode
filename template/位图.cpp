#include <iostream>
#include <vector>
#include <unordered_set>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
using namespace std;

// 位图的实现
class Bitset {
public:
    std::vector<int> set;

    // n个数字 : 0~n-1
    Bitset(int n) {
        // a/b如果结果想向上取整，可以写成 : (a+b-1)/b
        // 前提是a和b都是非负数
        set.resize((n + 31) / 32);
    }

    void add(int num) {
        set[num / 32] |= 1 << (num % 32);
    }

    void remove(int num) {
        set[num / 32] &= ~(1 << (num % 32));
    }

    void reverse(int num) {
        set[num / 32] ^= 1 << (num % 32);
    }

    bool contains(int num) const {
        return ((set[num / 32] >> (num % 32)) & 1) == 1;
    }
};

// 对数器测试
int main() {
    srand(time(0)); // 初始化随机数种子

    int n = 1000;
    int testTimes = 10000;
    std::cout << "测试开始" << std::endl;

    // 实现的位图结构
    Bitset bitSet(n);
    // 直接用unordered_set做对比测试
    std::unordered_set<int> hashSet;

    std::cout << "调用阶段开始" << std::endl;
    for (int i = 0; i < testTimes; i++) {
        double decide = static_cast<double>(rand()) / RAND_MAX;
        // number -> 0 ~ n-1，等概率得到
        int number = rand() % n;
        if (decide < 0.333) {
            bitSet.add(number);
            hashSet.insert(number);
        } else if (decide < 0.666) {
            bitSet.remove(number);
            hashSet.erase(number);
        } else {
            bitSet.reverse(number);
            if (hashSet.find(number) != hashSet.end()) {
                hashSet.erase(number);
            } else {
                hashSet.insert(number);
            }
        }
    }
    std::cout << "调用阶段结束" << std::endl;
    std::cout << "验证阶段开始" << std::endl;
    for (int i = 0; i < n; i++) {
        if (bitSet.contains(i) != (hashSet.find(i) != hashSet.end())) {
            std::cout << "出错了!" << std::endl;
            break; // 可以选择在这里终止程序，或者继续检查所有元素
        }
        else{
            cout<<"第"<<setw(4)<<i<<"组测试正确"<<endl;
        }
    }
    std::cout << "验证阶段结束" << std::endl;
    std::cout << "测试结束" << std::endl;

    return 0;
}
