//线段树  P4344
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

// 读取整数
template<typename T>
inline void read(T &FF) {
    T RR = 1; FF = 0; char CH = cin.get();
    for (; !isdigit(CH); CH = cin.get()) if (CH == '-') RR = -1;
    for (; isdigit(CH); CH = cin.get()) FF = (FF << 1) + (FF << 3) + (CH ^ 48);
    FF *= RR;
}

// 写入整数
template<typename T>
inline void write(T x) {
    if (x < 0) putchar('-'), x *= -1;
    if (x > 9) write(x / 10);
    putchar(x % 10 + 48);
}

// 写入整数并换行
template<typename T>
inline void writen(T x) {
    write(x);
    puts("");
}

const int N = 2e5 + 10;

// 线段树结构体
struct Tree {
    int left, right, leftMax, rightMax, sum, tag, length, answer;
};

// 线段树数组
vector<Tree> t(N * 4);

// 读取输入参数
int n, m, l0, r0, l1, r1, f;

// 更新当前节点的信息
void pushUp(int num) {
    t[num].sum = t[num * 2].sum + t[num * 2 + 1].sum;
    if (t[num * 2].leftMax == t[num * 2].length)
        t[num].leftMax = t[num * 2].length + t[num * 2 + 1].leftMax;
    else
        t[num].leftMax = t[num * 2].leftMax;
    if (t[num * 2 + 1].rightMax == t[num * 2 + 1].length)
        t[num].rightMax = t[num * 2 + 1].length + t[num * 2].rightMax;
    else
        t[num].rightMax = t[num * 2 + 1].rightMax;
    t[num].answer = max(max(t[num * 2].answer, t[num * 2 + 1].answer), t[num * 2].rightMax + t[num * 2 + 1].leftMax);
}

// 将节点标记为全1   这个区间的所有数字应该全部改为0
//懒住了
void down1(int num) {
    t[num].answer = t[num].leftMax = t[num].rightMax = t[num].length;
    t[num].sum = 0;
    t[num].tag = 1;
}

// 将节点标记为全2   这个区间的所有数字应该全部改为1
//懒住了
void down2(int num) {
    t[num].answer = t[num].leftMax = t[num].rightMax = 0;
    t[num].sum = t[num].length;
    t[num].tag = 2;
}

// 下推标记
void pushDown(int num) {
    if (t[num].tag == 1) {
        down1(num * 2);
        down1(num * 2 + 1);
        t[num].tag = 0;
    }
    if (t[num].tag == 2) {
        down2(num * 2);
        down2(num * 2 + 1);
        t[num].tag = 0;
    }
    //每次只向下更新一层
}

// 构建线段树
void build(int num, int left, int right) {
    t[num].tag = 0;
    t[num].left = left;
    t[num].right = right;
    t[num].length = right - left + 1;
    if (left == right) {
        t[num].sum = 1;
        t[num].answer = t[num].leftMax = t[num].rightMax = 0;
        return;
    }
    int mid = (left + right) / 2;
    build(num * 2, left, mid);
    build(num * 2 + 1, mid + 1, right);
    pushUp(num);
}

// 修改区间  将xy区间的数字进行修改  根据z的指示修改
void change(int num, int x, int y, int z) {
    if (t[num].left >= x && t[num].right <= y) {
        if (z == 1)
            down1(num);//懒住
        if (z == 2)
            down2(num);//懒住
        return;
    }
    pushDown(num);
    if (t[num * 2].right >= x)
        change(num * 2, x, y, z);
    if (t[num * 2 + 1].left <= y)
        change(num * 2 + 1, x, y, z);
    //如果当前区间没有命中要求  那么向下传递  然后向上汇总
    pushUp(num);
}

// 查询区间1的数量
int query0(int num, int x, int y) {
    if (t[num].left >= x && t[num].right <= y)
        return t[num].sum;
    pushDown(num);
    if (t[num * 2].right < x)
        return query0(num * 2 + 1, x, y);
    if (t[num * 2 + 1].left > y)
        return query0(num * 2, x, y);
    return query0(num * 2, x, y) + query0(num * 2 + 1, x, y);
}

// 查询区间0的数量
int query1(int num, int x, int y) {
    if (t[num].left >= x && t[num].right <= y)
        return t[num].length - t[num].sum;
    pushDown(num);
    if (t[num * 2].right < x)
        return query1(num * 2 + 1, x, y);
    if (t[num * 2 + 1].left > y)
        return query1(num * 2, x, y);
    return query1(num * 2, x, y) + query1(num * 2 + 1, x, y);
}

// 执行操作1
void performOperation1() {
    read(l1);
    read(r1);
    int x = query0(1, l0, r0);
    if (x == 0)
        return;
    change(1, l0, r0, 1);
    //将这个区间的所有数字全部改为0
    int left = l1, right = r1 + 1;
    while (left + 1 < right) {
        int mid = (left + right) / 2;
        if (query1(1, l1, mid) <= x)
            left = mid;
        else
            right = mid;
    }
    //通过二分来判断哪个区间是可以满足的
    //那么直接将这个区间修改为1
    change(1, l1, left, 2);
}

// 查询区间最大连续0的长度
int query2(int num, int x, int y) {
    if (t[num].left >= x && t[num].right <= y)
        //命中区间  直接返回答案
        return t[num].answer;
    pushDown(num);
    //懒更新  将信息向下传递
    if (t[num * 2].right < x)
        //左儿子的右边界没有命中  直接去右儿子就好
        return query2(num * 2 + 1, x, y);
    if (t[num * 2 + 1].left > y)
        //右儿子的左边界没有命中  直接去左儿子就好
        return query2(num * 2, x, y);
    return max(max(query2(num * 2, x, y), query2(num * 2 + 1, x, y)),
               min(t[num * 2].rightMax, t[num * 2 + 1].left - x) + min(t[num * 2 + 1].leftMax, y - t[num * 2].right));
               //这里的min表示  要么是最大leftmax或者rightmax  要么是左右的限制xy  这两个取最小值才行  表示左右儿子交界处寻找答案
               //这个总体式子表示的是
               //要么直接就是左儿子的不包括右边界区域是答案
               //要么是右儿子不包括左边界是答案
               //要么就是两个儿子的交界处是答案 也就是min这个式子
}

int main() {
    read(n);
    read(m);
    build(1, 1, n);
    while (m--) {
        read(f),read(l0),read(r0);
        switch (f) {
            case 0:
                change(1, l0, r0, 1);
                break;
            case 1:
                performOperation1();
                break;
            case 2:
                writen(query2(1, l0, r0));
                break;
        }
    }
    return 0;
}
