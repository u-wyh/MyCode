// 平衡因子影响替罪羊树的实验
// 一旦，max(左树节点数，右树节点数) > 平衡因子 * 整树节点数，就会发生重构
// 平衡因子范围是(0.5, 1.0)，否则无意义
// 平衡因子等于0.5时，树高很小，查询效率高，但是重构发生很频繁
// 平衡因子等于1.0时，重构完全不发生，但是树高很大，查询效率低
// 保证查询效率、同时保证重构的节点总数不多，0.7为最常用的平衡因子
// 这保证了查询效率，因为树高几乎是O(log n)
// 同时重构触发的时机合适，单次调整的均摊代价为O(log n)
#include <bits/stdc++.h>
using namespace std;

// 全局变量
double ALPHA = 0.7;
int maxx = 10000;
int cost = 0;
int head = 0;
int cnt = 0;
const int MAXN = 100001;
int key[MAXN];
int occurrence[MAXN]; // 修改为 occurrence
int ls[MAXN];
int rs[MAXN];
int size[MAXN];
int diff[MAXN];
int collect[MAXN];
int ci = 0;
int top = 0;
int father = 0;
int side = 0;

// 统计树高
int deep(int i) {
    if (i == 0) {
        return 0;
    }
    return max(deep(ls[i]), deep(rs[i])) + 1;
}

// 初始化节点
int init(int num) {
    key[++cnt] = num;
    ls[cnt] = rs[cnt] = 0;
    occurrence[cnt] = size[cnt] = diff[cnt] = 1; // 修改为 occurrence
    return cnt;
}

// 更新节点信息
void up(int i) {
    size[i] = size[ls[i]] + size[rs[i]] + occurrence[i]; // 修改为 occurrence
    diff[i] = diff[ls[i]] + diff[rs[i]] + (occurrence[i] > 0 ? 1 : 0); // 修改为 occurrence
}

// 中序遍历
void inorder(int i) {
    if (i != 0) {
        inorder(ls[i]);
        if (occurrence[i] > 0) { // 修改为 occurrence
            collect[++ci] = i;
        }
        inorder(rs[i]);
    }
}

// 构建树
int build(int l, int r) {
    if (l > r) {
        return 0;
    }
    int m = (l + r) / 2;
    int h = collect[m];
    ls[h] = build(l, m - 1);
    rs[h] = build(m + 1, r);
    up(h);
    return h;
}

// 重建树
void rebuild() {
    if (top != 0) {
        ci = 0;
        inorder(top);
        if (ci > 0) {
            cost += ci; // 统计重构节点数
            if (father == 0) {
                head = build(1, ci);
            } else if (side == 1) {
                ls[father] = build(1, ci);
            } else {
                rs[father] = build(1, ci);
            }
        }
    }
}

// 判断是否平衡
bool balance(int i) {
    return ALPHA * diff[i] >= max(diff[ls[i]], diff[rs[i]]);
}

// 插入节点
void add(int i, int f, int s, int num) {
    if (i == 0) {
        if (f == 0) {
            head = init(num);
        } else if (s == 1) {
            ls[f] = init(num);
        } else {
            rs[f] = init(num);
        }
    } else {
        if (key[i] == num) {
            occurrence[i]++; // 修改为 occurrence
        } else if (key[i] > num) {
            add(ls[i], i, 1, num);
        } else {
            add(rs[i], i, 2, num);
        }
        up(i);
        if (!balance(i)) {
            top = i;
            father = f;
            side = s;
        }
    }
}

// 插入数字
void add(int num) {
    top = father = side = 0;
    add(head, 0, 0, num);
    rebuild();
}

// 查找小于等于给定值的节点数量
int small(int i, int num) {
    if (i == 0) {
        return 0;
    }
    if (key[i] >= num) {
        return small(ls[i], num);
    } else {
        return size[ls[i]] + occurrence[i] + small(rs[i], num); // 修改为 occurrence
    }
}

// 获取排名
int getRank(int num) { // 修改为 getRank
    return small(head, num) + 1;
}

// 获取第x小的值
int index(int i, int x) {
    if (size[ls[i]] >= x) {
        return index(ls[i], x);
    } else if (size[ls[i]] + occurrence[i] < x) { // 修改为 occurrence
        return index(rs[i], x - size[ls[i]] - occurrence[i]); // 修改为 occurrence
    }
    return key[i];
}

// 获取第x小的值（外部调用）
int index(int x) {
    return index(head, x);
}

// 获取前驱
int pre(int num) {
    int kth = getRank(num); // 修改为 getRank
    if (kth == 1) {
        return INT_MIN;
    } else {
        return index(kth - 1);
    }
}

// 获取后继
int post(int num) {
    int kth = getRank(num + 1); // 修改为 getRank
    if (kth == size[head] + 1) {
        return INT_MAX;
    } else {
        return index(kth);
    }
}

// 删除节点
void remove(int i, int f, int s, int num) {
    if (key[i] == num) {
        occurrence[i]--; // 修改为 occurrence
    } else if (key[i] > num) {
        remove(ls[i], i, 1, num);
    } else {
        remove(rs[i], i, 2, num);
    }
    up(i);
    if (!balance(i)) {
        top = i;
        father = f;
        side = s;
    }
}

// 删除数字
void remove(int num) {
    if (getRank(num) != getRank(num + 1)) { // 修改为 getRank
        top = father = side = 0;
        remove(head, 0, 0, num);
        rebuild();
    }
}

// 清空树
void clear() {
    fill(key + 1, key + cnt + 1, 0);
    fill(occurrence + 1, occurrence + cnt + 1, 0); // 修改为 occurrence
    fill(ls + 1, ls + cnt + 1, 0);
    fill(rs + 1, rs + cnt + 1, 0);
    fill(size + 1, size + cnt + 1, 0);
    fill(diff + 1, diff + cnt + 1, 0);
    cnt = 0;
    head = 0;
}

int main() {
    ALPHA = 0.72; // 设置平衡因子
    int max_value = 10000; // 修改变量名为 max_value 以避免与 max 函数冲突
    cout << "测试开始" << endl;
    cost = 0; // 清空重构节点计数
    for (int num = 1; num <= max_value; num++) {
        add(num);
    }
    cout << "插入数字 : " << "1~" << max_value << endl;
    cout << "平衡因子 : " << ALPHA << endl;
    cout << "树的高度 : " << deep(head) << endl;
    cout << "重构节点 : " << cost << endl;
    cout << "测试结束" << endl;
    clear();
    return 0;
}
