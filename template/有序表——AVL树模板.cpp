// AVL树的实现(java版)
// 实现一种结构，支持如下操作，要求单次调用的时间复杂度O(log n)
// 1，增加x，重复加入算多个词频
// 2，删除x，如果有多个，只删掉一个
// 3，查询x的排名，x的排名为，比x小的数的个数+1
// 4，查询数据中排名为x的数
// 5，查询x的前驱，x的前驱为，小于x的数中最大的数，不存在返回整数最小值
// 6，查询x的后继，x的后继为，大于x的数中最小的数，不存在返回整数最大值
// 所有操作的次数 <= 10^5
// -10^7 <= x <= +10^7
// 测试链接 : https://www.luogu.com.cn/problem/P3369
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include <iostream>
#include <algorithm>
#include <climits>
#include <cstring>
using namespace std;
const int MAXN = 100001;

int cnt = 0;//用于赋予节点编号
int head = 0;//整棵树的头结点  这个节点是可以变化的  会根据树的形态调整
int key[MAXN];//节点的权值
int height[MAXN];//节点的树高  左右孩子树高的最大值加上一
int ls[MAXN];
int rs[MAXN];//左右孩子节点编号  注意这个也不是有值之后就保持不变的   会根据树的形态发生相应变化
int key_count[MAXN];//统计这个节点上的数字出现了多少次  词频统计
int size[MAXN];//以该节点为首的子树上所有数字的词频之和

void up(int i) {
    size[i] = size[ls[i]] + size[rs[i]] + key_count[i];
    height[i] = max(height[ls[i]], height[rs[i]]) + 1;
}

//左右旋 目的把形态不符合AVL树调整成AVL树
//函数的作用是将以i为首的子树左右旋  并返回最终树的头结点
int leftRotate(int i) {
    int r = rs[i];
    rs[i] = ls[r];
    ls[r] = i;
    up(i);
    up(r);
    return r;
}

int rightRotate(int i) {
    int l = ls[i];
    ls[i] = rs[l];
    rs[l] = i;
    up(i);
    up(l);
    return l;
}

//将这个节点为首的树调整好  使之不违反AVL树的定义  即左右孩子树高不超过一
//并返回调整好后的头结点
int maintain(int i) {
    int lh = height[ls[i]];
    int rh = height[rs[i]];
    if (lh - rh > 1) {
        if (height[ls[ls[i]]] >= height[rs[ls[i]]]) {
            i = rightRotate(i);
        } else {
            ls[i] = leftRotate(ls[i]);
            i = rightRotate(i);
        }
    } else if (rh - lh > 1) {
        if (height[rs[rs[i]]] >= height[ls[rs[i]]]) {
            i = leftRotate(i);
        } else {
            rs[i] = rightRotate(rs[i]);
            i = leftRotate(i);
        }
    }
    return i;
}

//在以i节点为首的子树上加入一个num  并返回调整过后的头结点
int add(int i, int num) {
    if (i == 0) {
        //表示这是第一次出现
        key[++cnt] = num;
        key_count[cnt] = size[cnt] = height[cnt] = 1;
        //新建一个节点
        return cnt;
    }
    if (key[i] == num) {
        key_count[i]++;
    } else if (key[i] > num) {
        ls[i] = add(ls[i], num);
    } else {
        rs[i] = add(rs[i], num);
    }
    up(i);
    //每次都要向上汇总  确保数据正确
    return maintain(i);
    //调整树的结构  使之平衡
}

//加入一个值为num的数字
void add(int num) {
    head = add(head, num);
}

//查询以i节点为首的子树上小于num的数字的数量
int getRank(int i, int num) {
    if (i == 0) {
        return 0;
    }
    if (key[i] >= num) {
        return getRank(ls[i], num);
    } else {
        return size[ls[i]] + key_count[i] + getRank(rs[i], num);
    }
}

//查询num这个数字排名  也就是所有比他小的数字数量加一
int getRank(int num) {
    return getRank(head, num) + 1;
}

int removeMostLeft(int i, int mostLeft) {
    if (i == mostLeft) {
        return rs[i];
    } else {
        ls[i] = removeMostLeft(ls[i], mostLeft);
        up(i);
        return maintain(i);
    }
}

//查询以i节点为首的子树上删去一个num
int remove(int i, int num) {
    if (key[i] < num) {
        rs[i] = remove(rs[i], num);
    } else if (key[i] > num) {
        ls[i] = remove(ls[i], num);
    } else {
        if (key_count[i] > 1) {
            key_count[i]--;
        } else {
            if (ls[i] == 0 && rs[i] == 0) {
                return 0;
            } else if (ls[i] != 0 && rs[i] == 0) {
                i = ls[i];
            } else if (ls[i] == 0 && rs[i] != 0) {
                i = rs[i];
            } else {
                int mostLeft = rs[i];
                while (ls[mostLeft] != 0) {
                    mostLeft = ls[mostLeft];
                }
                rs[i] = removeMostLeft(rs[i], mostLeft);
                ls[mostLeft] = ls[i];
                rs[mostLeft] = rs[i];
                i = mostLeft;
            }
        }
    }
    up(i);
    return maintain(i);
}

//在树上删除数字num
void remove(int num) {
    if (getRank(num) != getRank(num + 1)) {
        //表示这个数字存在
        head = remove(head, num);
    }
}

int index(int i, int x) {
    if (size[ls[i]] >= x) {
        return index(ls[i], x);
    } else if (size[ls[i]] + key_count[i] < x) {
        return index(rs[i], x - size[ls[i]] - key_count[i]);
    }
    return key[i];
}

int index(int x) {
    return index(head, x);
}

int pre(int i, int num) {
    if (i == 0) {
        return INT_MIN;
    }
    if (key[i] >= num) {
        return pre(ls[i], num);
    } else {
        return max(key[i], pre(rs[i], num));
    }
}

int pre(int num) {
    return pre(head, num);
}

int post(int i, int num) {
    if (i == 0) {
        return INT_MAX;
    }
    if (key[i] <= num) {
        return post(rs[i], num);
    } else {
        return min(key[i], post(ls[i], num));
    }
}

int post(int num) {
    return post(head, num);
}

void clear() {
    memset(key + 1, 0, cnt * sizeof(int));
    memset(height + 1, 0, cnt * sizeof(int));
    memset(ls + 1, 0, cnt * sizeof(int));
    memset(rs + 1, 0, cnt * sizeof(int));
    memset(key_count + 1, 0, cnt * sizeof(int));
    memset(size + 1, 0, cnt * sizeof(int));
    cnt = 0;
    head = 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1, op, x; i <= n; i++) {
        cin >> op >> x;
        if (op == 1) {
            add(x);
        } else if (op == 2) {
            remove(x);
        } else if (op == 3) {
            cout << getRank(x) << endl;
        } else if (op == 4) {
            cout << index(x) << endl;
        } else if (op == 5) {
            cout << pre(x) << endl;
        } else {
            cout << post(x) << endl;
        }
    }
    clear();
    return 0;
}
