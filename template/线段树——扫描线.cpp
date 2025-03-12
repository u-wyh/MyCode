// 矩形面积并
// 测试链接 : https://www.luogu.com.cn/problem/P5490
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 300001;

int rec[MAXN][4];
struct Line{
    int a1,a2,a3,a4;
}line[MAXN];
//y的数据需要离散化
int ysort[MAXN];
// 线段树某范围总长度
int length[MAXN << 2];
// 线段树某范围覆盖长度
int cover[MAXN << 2];
// 线段树某范围覆盖次数
int times[MAXN << 2];

int prepare(int n) {
    sort(ysort+1,ysort+ n + 1);
    int m = 1;
    for (int i = 2; i <= n; i++) {
        if (ysort[m] != ysort[i]) {
            ysort[++m] = ysort[i];
        }
    }
    ysort[m + 1] = ysort[m];//加一个数据防止越界
    return m;
}
//实现元素的去重

int Rank(int n, int num) {
    int ans = 0;
    int l = 1, r = n, mid;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (ysort[mid] >= num) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}
//二分法求出对应下标

void build(int l, int r, int i) {
    if (l < r) {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
    }
    length[i] = ysort[r + 1] - ysort[l];
    times[i] = 0;
    cover[i] = 0;
}

void up(int i) {
    if (times[i] > 0) {
        cover[i] = length[i];
    } else {
        cover[i] = cover[i << 1] + cover[i << 1 | 1];
    }
}

// 这个题的特殊性在于
// 1) 查询操作永远查的是整个范围，不会有小范围的查询，每次都返回cover[1]
// 2) 增加操作之后，后续一定会有等规模的减少操作
// 根据以上两点分析出不需要懒更新机制
// 首先当一次修改完成从下往上返回时，up方法能保证最上方的cover[1]是修改正确的
// 同时任何一次增加操作所涉及的线段树范围，后续一定能被等规模的减少操作取消掉
// 课上重点图解这个特殊性
void add(int jobl, int jobr, int jobv, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        times[i] += jobv;
    } else {
        int mid = (l + r) >> 1;
        if (jobl <= mid) {
            add(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid) {
            add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
    }
    up(i);
}

bool cmp(Line a,Line b){
    return a.a1<b.a1;
}

long compute(int n) {
    for (int i = 1, j = 1 + n, x1, y1, x2, y2; i <= n; i++, j++) {
        x1 = rec[i][0]; y1 = rec[i][1]; x2 = rec[i][2]; y2 = rec[i][3];
        ysort[i] = y1; ysort[j] = y2;
        line[i].a1 = x1; line[i].a2 = y1; line[i].a3 = y2; line[i].a4 = 1;//开始位置 起止位置 效果
        line[j].a1 = x2; line[j].a2 = y1; line[j].a3 = y2; line[j].a4 = -1;
        //一个矩形两条线
    }
    n <<= 1;
    int m = prepare(n);
    build(1, m, 1);
    sort(line+1,line+ n + 1,cmp);
    long ans = 0;
    for (int i = 1, pre = 0; i <= n; i++) {
        ans += (long) cover[1] * (line[i].a1 - pre);
        //每一发生变化的时候都计算一下上一个区域（可能是多个矩形）所产生的面积  即长乘宽
        //即结算操作  表示这个范围有多少被覆盖
        //pre是上一次的左边
        //这个cover[1]是此时总的覆盖长度
        pre = line[i].a1;
        add(Rank(m, line[i].a2), Rank(m, line[i].a3) - 1, line[i].a4, 1, m, 1);
        // 区间的加操作
    }
    return ans;
}

int main()
{
    int n;
    cin>>n;
    for (int i = 1; i <= n; i++) {
        // 左下角下标
        cin>>rec[i][0];
        cin>>rec[i][1];
        // 右上角下标
        cin>>rec[i][2];
        cin>>rec[i][3];
    }
    cout<<compute(n);
    return 0;
}
