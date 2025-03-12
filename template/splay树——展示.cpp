#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 100001;

// 整棵树的头节点编号
int head = 0;

// 分配了多少节点编号
int cnt = 0;

// key[i]    : 编号为i的节点的key
int key[MAXN];

// father[i] : 编号为i的节点的父节点编号
int father[MAXN];

// ls[i]     : 编号为i的节点的左孩子编号（原left）
int ls[MAXN];

// rs[i]     : 编号为i的节点的右孩子编号（原right）
int rs[MAXN];

// size[i]   : 以编号为i的节点做头的子树，一共有多少个节点
int size[MAXN];

// 更新节点i的大小信息
void up(int i) {
    size[i] = size[ls[i]] + size[rs[i]] + 1;
}

// 判断编号为i的节点，是其父亲的什么儿子
// 0代表左儿子（现改为ls），1代表右儿子（现改为rs）
int lr(int i) {
    return rs[father[i]] == i ? 1 : 0;
}

// 编号为i的节点上升一步，在结构上做调整
void rotate(int i) {
    int f = father[i], g = father[f], soni = lr(i), sonf = lr(f);
    if (soni == 1) {
        //是父亲节点的右孩子
        //那么就直接左旋
        rs[f] = ls[i];//父亲节点的右孩子变成i节点的左孩子
        if (rs[f] != 0) {//这里实际上指是i节点的右孩子不是空
            father[rs[f]] = f;
        }
        ls[i] = f;//i节点的左孩子设置为父亲节点  左旋完成
    } else {
        ls[f] = rs[i]; ;
        if (ls[f] != 0) {
            father[ls[f]] = f;
        }
        rs[i] = f;
    }
    if (g != 0) {
        //如果爷爷节点不是空
        if (sonf == 1) {
            //那么以前父亲节点是爷爷节点的什么儿子 如今i节点就是什么儿子
            rs[g] = i;
        } else {
            ls[g] = i;
        }
    }
    father[f] = i;//原来父亲节点的父亲变为i
    father[i] = g;//i的父亲节点变为原来的爷爷
    up(f);//之所以不用将g也调整  是因为他的子树大小没有发生变化
    up(i);
}

// 编号为i的节点提根，变成编号为goal的节点的儿子
// 如果goal == 0，表示把编号为i的节点变成整棵树的头
void splay(int i, int goal) {
    int f = father[i], g = father[f];
    while (f != goal) {
        //父亲不是目标 那么就说明还没有完成任务
        if (g != goal) {
            //爷爷不是目标  那么i节点至少要跳到爷爷节点上面
            //那么要么是  之字形  要么是  一字型
            //根据左右儿子判断
            if (lr(i) == lr(f)) {
                rotate(f);
            } else {
                rotate(i);
            }
        }
        rotate(i);//如果爷爷就是目标 那么向上一次就可以了
        f = father[i];
        g = father[f];
    }
    if (goal == 0) {
        head = i;
    }
}

// 构建一字型长链
int build1(int l, int r) {
    int h = cnt + 1;
    for (int i = l, last = 0; i <= r; i++, last = cnt) {
        key[++cnt] = i;
        father[cnt] = last;
        ls[cnt] = rs[cnt] = 0; // 原 left[cnt] = right[cnt] = 0;
        size[cnt] = r - i + 1;
        if (last != 0) {
            rs[last] = cnt; // 原 right[last] = cnt;
        }
    }
    return h;
}

// 构建之字形长链
int build2(int l, int r, int fa) {
    if (l > r) {
        return 0;
    }
    key[++cnt] = l;
    father[cnt] = fa;
    ls[cnt] = rs[cnt] = 0; // 原 left[cnt] = right[cnt] = 0;
    int h = cnt;
    if (l < r) {
        key[++cnt] = r;
        father[cnt] = h;
        ls[cnt] = rs[cnt] = 0; // 原 left[cnt] = right[cnt] = 0;
        int c = cnt;
        rs[h] = c; // 原 right[h] = c;
        ls[c] = build2(l + 1, r - 1, c); // 原 left[c] = build2(l + 1, r - 1, c);
        up(c);
    }
    up(h);
    return h;
}

// 返回以i为头的树的高度
int height(int i) {
    if (i == 0) {
        return 0;
    }
    return max(height(ls[i]), height(rs[i])) + 1; // 原 max(height(left[i]), height(right[i])) + 1;
}

int main() {
    cout << "构建一字型长链" << endl;
    cout << "最下方节点执行splay，观察高度变化" << endl;
    head = build1(1, 1000);
    cout << "splay之前的链长度 : " << height(head) << endl;
    splay(cnt, 0);
    cout << "splay之后的链长度 : " << height(head) << endl;

    cout << "==================" << endl;

    cout << "构建之字型长链" << endl;
    cout << "最下方节点执行splay，观察高度变化" << endl;
    head = build2(1, 1000, 0);
    cout << "splay之前的链长度 : " << height(head) << endl;
    splay(cnt, 0);
    cout << "splay之后的链长度 : " << height(head) << endl;

    return 0;
}
