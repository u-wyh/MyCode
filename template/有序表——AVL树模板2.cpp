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
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

// 空间使用计数
int cnt = 0;
// 整棵树的头节点编号
int head = 0;

// 节点的key
int key[MAXN];
// 子树高度  是左儿子和右儿子的高度最大值加1
int height[MAXN];

// 记录左孩子的key
int ls[MAXN];
// 记录右孩子的key
int rs[MAXN];

// 节点key的计数  只是表示该节点的数量  不是子树大小
int keycount[MAXN];
// 子树的数字总数
int size[MAXN];

//以上的同一个节点的所有信息都是依靠下标实现的

void up(int i) {
    size[i] = size[ls[i]] + size[rs[i]] + keycount[i];
    //子树大小是  左子树  加上  右子树  以及自己的大小
    height[i] = max(height[ls[i]], height[rs[i]]) + 1;
}

// i节点为头的树左旋，返回左旋后头节点的空间编号
int leftRotate(int i) {
    int r = rs[i];//让右儿子变成头
    rs[i] = ls[r];//原来头的右儿子  变成  原来头的右儿子的左儿子
    ls[r] = i;//原来头的右儿子的左儿子 变成 原来的头
    //成功实现左旋

    up(i);
    up(r);
    //以i r为头的树发生了变化  向上更新信息
    return r;
}

// i节点为头的树右旋，返回右旋后头节点的空间编号  同上
int rightRotate(int i) {
    int l = ls[i];
    ls[i] = rs[l];
    rs[l] = i;
    up(i);
    up(l);
    return l;
}

// 检查i节点为头的树是否违规
// 如果命中了某种违规情况，就进行相应调整
// 返回树的头节点的空间编号
int maintain(int i) {
    int lh = height[ls[i]];
    int rh = height[rs[i]];
    //收集左右树高
    if (lh - rh > 1) {
        //左树比右树高1以上
        if (height[ls[ls[i]]] >= height[rs[ls[i]]]) {
            //LL型  右旋即可
            i = rightRotate(i);
        } else {
            //LR型  左树左旋一下  然后整体右旋
            ls[i] = leftRotate(ls[i]);
            i = rightRotate(i);
        }
    } else if (rh - lh > 1) {
        if (height[rs[rs[i]]] >= height[ls[rs[i]]]) {
            //RR型
            i = leftRotate(i);
        } else {
            //RL
            rs[i] = rightRotate(rs[i]);
            i = leftRotate(i);
        }
    }
    return i;
}

// 当前来到i号节点，num这个数字一定会加入以i为头的树  否则不会到这一步
// 树结构有可能变化，返回头节点编号
int add(int i, int num) {
    if (i == 0) {
        //这里表示从未出现过  赋予新编号
        key[++cnt] = num;
        keycount[cnt] = size[cnt] = height[cnt] = 1;
        //初始化信息
        return cnt;
    }
    if (key[i] == num) {
        //命中了信息就词频++  否则根据大小向左向右转移
        keycount[i]++;
    } else if (key[i] > num) {
        ls[i] = add(ls[i], num);
    } else {
        rs[i] = add(rs[i], num);
    }
    up(i);
    //以i为头结点的信息发生了变化   向上更新信息
    return maintain(i);
    //在完成加入一个数字的这一过程中   每到一个节点都会去判断一下是否违规
    //如果违规的话  就会左右旋  导致头结点改变
}

// 增加数字num，重复加入算多个词频
void add(int num) {
    head = add(head, num);
}

// 以i为头的树上，比num小的数字有几个
int small(int i, int num) {
    if (i == 0) {
        return 0;
    }
    if (key[i] >= num) {
        //如果当前值比要查询的数字大  那么去左儿子
        return small(ls[i], num);
    } else {
        //否则就是  左子树的大小  加上  当前节点的词频  然后去右子树
        return size[ls[i]] + keycount[i] + small(rs[i], num);
    }
}

// 查询num的排名，比num小的数字个数+1，就是num的排名
int getrank(int num) {
    return small(head, num) + 1;
}

// 以i号节点为头的树上，最左节点的编号一定是mostLeft  这个mostleft是之前求出来的最左边
// 删掉这个节点，并保证树的平衡性，返回头节点的编号
int removeMostLeft(int i, int mostLeft) {
    if (i == mostLeft) {
        return rs[i];
    } else {
        ls[i] = removeMostLeft(ls[i], mostLeft);
        //还有向左的路程  继续向左
        up(i);
        return maintain(i);
        //在删除一个数字的过程中  每个节点都必须要判断是否违规
    }
}

// 当前来到i号节点，以i为头的树一定会减少1个num
// 树结构有可能变化，返回头节点编号
int remove(int i, int num) {
    if (key[i] < num) {
        rs[i] = remove(rs[i], num);
    } else if (key[i] > num) {
        ls[i] = remove(ls[i], num);
    } else {
        //在这之前 都是在寻找该数字
        //现在找到该数字
        if (keycount[i] > 1) {
            //词频足够  不至于消除节点
            //我们所说的消除节点就是不再使用这个编号了  即使后来这个key对应的键再次恢复  我们会给他一个新的节点编号
            keycount[i]--;
        } else {
            if (ls[i] == 0 && rs[i] == 0) {
                //叶节点
                return 0;
            } else if (ls[i] != 0 && rs[i] == 0) {
                i = ls[i];//只有左孩子或者右孩子  也直接改变就好
            } else if (ls[i] == 0 && rs[i] != 0) {
                i = rs[i];
            } else {
                //左右两边都有孩子
                int mostLeft = rs[i];
                while (ls[mostLeft] != 0) {
                    mostLeft = ls[mostLeft];
                }
                //此时mostleft就是这颗以键值等于num的节点的树上大于num的最小值所在编号
                rs[i] = removeMostLeft(rs[i], mostLeft);//相当于将这个节点和rs[i]这棵树断联  然后这个节点去接替i这个节点的位置
                ls[mostLeft] = ls[i];
                rs[mostLeft] = rs[i];
                i = mostLeft;
            }
        }
    }
    up(i);
    //向上更新数字
    return maintain(i);
}

// 删除数字num，如果有多个，只删掉一个
void remove(int num) {
    if (getrank(num) != getrank(num + 1)) {
        //说明num一定存在
        //getrank作用是统计有多少个数字小于num  然后加一
        //他并不管这个数字是否存在
        //那么如果一个数字的num和num+1排名不同 说明这个数字一定存在
        head = remove(head, num);
    }
}

int index(int i, int x) {
    if (size[ls[i]] >= x) {
        return index(ls[i], x);
    } else if (size[ls[i]] + keycount[i] < x) {
        return index(rs[i], x - size[ls[i]] - keycount[i]);
    }
    return key[i];
}

//排名位于第 x 位的数。
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

//查询 x 的前驱（前驱定义为小于 x，且最大的数）
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

//查询 x 的后继（后继定义为大于 x，且最小的数）
int post(int num) {
    return post(head, num);
}

void clear() {
    memset(key + 1, 0, cnt * sizeof(int));
    memset(height + 1, 0, cnt * sizeof(int));
    memset(ls + 1, 0, cnt * sizeof(int));
    memset(rs + 1, 0, cnt * sizeof(int));
    memset(keycount + 1, 0, cnt * sizeof(int));
    memset(size + 1, 0, cnt * sizeof(int));
    cnt = 0;
    head = 0;
}

int main()
{
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
            cout << getrank(x) << endl;
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
