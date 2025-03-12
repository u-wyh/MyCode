// 跳表的实现(C++版)
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
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
#include <bits/stdc++.h>

using namespace std;

const int MAXL = 20;
//这个值的选取是 2的MAXL次方 是  最接近大于MAXN的最小值
const int MAXN = 100001;

int cnt;//用于记录节点编号 和AVL一样
int key[MAXN];//用于记录当前节点对应的键值是多少
int key_count[MAXN];//用于记录当前值出现了多少次
int level[MAXN];//用于记录该节点最多有多少层   初始时随机生成
int next_node[MAXN][MAXL + 1];//用于记录该节点的第i层指向的下一个节点是什么
int len[MAXN][MAXL + 1];//记录该节点的第i层到下一个数字之间有多少个数字  对应第一层的数字个数  左开右闭

void build() {
    cnt = 1;
    key[cnt] = INT_MIN;//第一个节点的编号永远记1
    level[cnt] = MAXL;//它的层数直接设置为最多层
}
//初始化表头  整张表 越往右 值越大

void clear() {
    memset(key + 1, 0, cnt * sizeof(int));
    memset(key_count + 1, 0, cnt * sizeof(int));
    memset(level + 1, 0, cnt * sizeof(int));
    for (int i = 1; i <= cnt; i++) {
        memset(next_node[i], 0, (MAXL + 1) * sizeof(int));
        memset(len[i], 0, (MAXL + 1) * sizeof(int));
    }
    cnt = 0;
}

int randomLevel() {
    //随机生成新节点的层数值 并且永远不会更改
    int ans = 1;
    while ((std::rand() / double(RAND_MAX)) < 0.5) {
        ans++;
    }
    return min(ans, MAXL);
}

// 当前在i号节点的h层，返回key为num的节点，空间编号是多少
int find(int i, int h, int num) {
    while (next_node[i][h] != 0 && key[next_node[i][h]] < num) {
        //自己的下一个节点不是0  说明还有指向的东西
        //并且指向的下一个值小于num 说明还可以再这一层上继续往右寻找
        //和链表有些类似
        i = next_node[i][h];
    }
    //这个while结束后 下一个节点要么是0 即空
    //要么是大于等于num的数字
    //如果下一个数字大于num  那么说明需要去下一层寻找
    //即使下一个数字就是num  但现在不是最底层 即不是第一层
    //那么我们还是向下  因为这样肯定错不了  我们只想要在第一层找到节点
    //并且即使下一个节点就是空  我们也是在第一层的时候结束它
    if (h == 1) {
        if (next_node[i][h] != 0 && key[next_node[i][h]] == num) {
            //next_node[i][h]表示节点i的第h层的下一个节点
            return next_node[i][h];
        } else {
            //到了最应该找到他的位置却还是没有找到  那么就是不存在  返回0
            return 0;
        }
    }
    return find(i, h - 1, num);
    //当前节点一定是小于num的  下一个一定是大于等于num的
    //在当前节点向下一层继续找
}

// 当前在i号节点的h层，num增加一个词频
void addCount(int i, int h, int num) {
    while (next_node[i][h] != 0 && key[next_node[i][h]] < num) {
        i = next_node[i][h];
    }
    if (h == 1) {
        key_count[next_node[i][h]]++;
    } else {
        //只要不是第一层 那么就要递归
        //增加词频会对线上的中间数字数量产生影响
        addCount(i, h - 1, num);
    }
    len[i][h]++;
    //在一开始i已经是下一个节点就是大于等于num的了
    //该num节点一定存在  所以如果是大于它的 那么说明就是层数太高了
    //不管层数怎么样 i的h层这条线一定会经过num  因为左开右闭
}

// 当前在i号节点的h层，插入空间编号为j的节点
// 返回值：从i号节点出发，直到把空间编号为j的节点插入，底层总共有多少数字比key[j]小
// 返回值很重要，因为上游需要这个信息来改动指针的长度信息
int addNode(int i, int h, int j) {
    int rightCnt = 0;
    //用于统计i节点到  下一个节点大于等于key[j] 的节点中间距离
    while (next_node[i][h] != 0 && key[next_node[i][h]] < key[j]) {
        rightCnt += len[i][h];
        i = next_node[i][h];
    }
    if (h == 1) {
        next_node[j][h] = next_node[i][h];
        next_node[i][h] = j;
        len[j][h] = key_count[next_node[j][h]];//直接就是词频  因为这是最底层
        len[i][h] = key_count[next_node[i][h]];//这个地方也可以是1   毕竟这是新建节点  一定是1
        return rightCnt;
    } else {
        int downCnt = addNode(i, h - 1, j);
        if (h > level[j]) {
            len[i][h]++;
        } else {
            next_node[j][h] = next_node[i][h];
            next_node[i][h] = j;
            len[j][h] = len[i][h] + 1 - downCnt - key_count[j];
            len[i][h] = downCnt + key_count[j];
        }
        return rightCnt + downCnt;
    }
}

// 增加num，重复加入算多个词频
void add(int num) {
    if (find(1, MAXL, num) != 0) {
        addCount(1, MAXL, num);
    } else {
        key[++cnt] = num;
        key_count[cnt] = 1;
        level[cnt] = randomLevel();
        addNode(1, MAXL, cnt);
    }
}

// 当前在i号节点的h层，num减少一个词频
void removeCount(int i, int h, int num) {
    while (next_node[i][h] != 0 && key[next_node[i][h]] < num) {
        i = next_node[i][h];
    }
    if (h == 1) {
        key_count[next_node[i][h]]--;
    } else {
        removeCount(i, h - 1, num);
    }
    len[i][h]--;
}

// 当前在i号节点的h层，删除空间编号为j的节点
void removeNode(int i, int h, int j) {
    if (h < 1) {
        return;
    }
    while (next_node[i][h] != 0 && key[next_node[i][h]] < key[j]) {
        i = next_node[i][h];
    }
    if (h > level[j]) {
        len[i][h]--;
    } else {
        next_node[i][h] = next_node[j][h];
        len[i][h] += len[j][h] - 1;
    }
    removeNode(i, h - 1, j);
}

// 删除x，如果有多个，只删掉一个
void remove(int num) {
    int j = find(1, MAXL, num);
    if (j != 0) {
        //节点存在
        if (key_count[j] > 1) {
            removeCount(1, MAXL, num);
        } else {
            removeNode(1, MAXL, j);
        }
    }
}

// 当前在i号节点的h层，查询有多少个数字比num小
int small(int i, int h, int num) {
    int rightCnt = 0;
    while (next_node[i][h] != 0 && key[next_node[i][h]] < num) {
        rightCnt += len[i][h];
        i = next_node[i][h];
    }
    if (h == 1) {
        return rightCnt;
    } else {
        return rightCnt + small(i, h - 1, num);
    }
}

// 查询num的排名
int getRank(int num) {
    return small(1, MAXL, num) + 1;
}

// 当前在i号节点的h层，查询排名第x的key是什么
int index(int i, int h, int x) {
    int c = 0;
    while (next_node[i][h] != 0 && c + len[i][h] < x) {
        c += len[i][h];
        i = next_node[i][h];
    }
    if (h == 1) {
        return key[next_node[i][h]];
    } else {
        return index(i, h - 1, x - c);
    }
}

// 查询排名第x的key是什么
int index(int x) {
    return index(1, MAXL, x);
}

int pre(int i, int h, int num) {
    while (next_node[i][h] != 0 && key[next_node[i][h]] < num) {
        i = next_node[i][h];
    }
    if (h == 1) {
        return i == 1 ? INT_MIN : key[i];
    } else {
        return pre(i, h - 1, num);
    }
}

// 查询num的前驱
int pre(int num) {
    return pre(1, MAXL, num);
}

int post(int i, int h, int num) {
    while (next_node[i][h] != 0 && key[next_node[i][h]] < num) {
        i = next_node[i][h];
    }
    if (h == 1) {
        if (next_node[i][h] == 0) {
            return INT_MAX;
        }
        if (key[next_node[i][h]] > num) {
            return key[next_node[i][h]];
        }
        i = next_node[i][h];
        if (next_node[i][h] == 0) {
            return INT_MAX;
        } else {
            return key[next_node[i][h]];
        }
    } else {
        return post(i, h - 1, num);
    }
}

// 查询num的后继
int post(int num) {
    return post(1, MAXL, num);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));
    build();
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
