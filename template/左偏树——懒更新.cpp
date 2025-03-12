// 城池攻占，C++版
// 一共有n个城市，1号城市是城市树的头，每个城市都有防御值、上级城市编号、奖励类型、奖励值
// 如果奖励类型为0，任何骑士攻克这个城市后，攻击力会加上奖励值
// 如果奖励类型为1，任何骑士攻克这个城市后，攻击力会乘以奖励值
// 任何城市的上级编号 < 这座城市的编号，1号城市没有上级城市编号、奖励类型、奖励值
// 一共有m个骑士，每个骑士都有攻击力、第一次攻击的城市
// 如果骑士攻击力 >= 城市防御值，当前城市会被攻占，骑士获得奖励，继续攻击上级城市
// 如果骑士攻击力  < 城市防御值，那么骑士会在该城市牺牲，没有后续动作了
// 所有骑士都是独立的，不会影响其他骑士攻击这座城池的结果
// 打印每个城市牺牲的骑士数量，打印每个骑士攻占的城市数量
// 1 <= n、m <= 3 * 10^5，攻击值的增加也不会超过long类型范围
// 测试链接 : https://www.luogu.com.cn/problem/P3261
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300001;
int n, m;
// 城市防御值
long long defend[MAXN];
// 上级城市编号
int belong[MAXN];
// 奖励类型
int type[MAXN];
// 奖励值
long long gain[MAXN];
long long attack[MAXN];
// 骑士第一次攻击的城市
int first[MAXN];
// 城市在城市树中的深度
int deep[MAXN];
// 城市拥有的骑士列表，用小根堆左偏树组织，最弱的骑士是头
int top[MAXN];
// 每个城市牺牲人数统计
int sacrifice[MAXN];
// 每个骑士死在了什么城市
int die[MAXN];
// 左偏树需要   左偏树维持小根堆
//将攻击力弱的放在上面  如果连最弱的都可以成功  说明所有的都能成功
int ls[MAXN];
int rs[MAXN];
int dist[MAXN];
// 懒更新信息，攻击力应该乘多少
long long mul[MAXN];
// 懒更新信息，攻击力应该加多少
long long add[MAXN];

//信息全部初始化
void prepare() {
    dist[0] = -1;
    for (int i = 1; i <= m; i++) {
        ls[i] = rs[i] = dist[i] = 0;
        mul[i] = 1;
        add[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        sacrifice[i] = top[i] = 0;
    }
}

//更新信息  将i号骑士加上类型为t数值为v的奖励
//这个只会是传给当前某个城市的小根堆的头节点
void upgrade(int i, int t, long long v) {
    if (t == 0) {
        //如果是相加类型
        attack[i] += v;
        add[i] += v;
    } else {
        //如果是相乘类型
        attack[i] *= v;
        mul[i] *= v;
        add[i] *= v;
    }
}

//将信息向下传递
void down(int i) {
    if (mul[i] != 1 || add[i] != 0) {
        //表示确实有要传递的更新信息
        int l = ls[i];
        int r = rs[i];
        if (l != 0) {
            //有左儿子
            attack[l] = attack[l] * mul[i] + add[i];
            //将左儿子的值更新对  然后将更新信息修正  不在往下传递
            mul[l] = mul[l] * mul[i];
            add[l] = add[l] * mul[i] + add[i];
        }
        if (r != 0) {
            attack[r] = attack[r] * mul[i] + add[i];
            mul[r] = mul[r] * mul[i];
            add[r] = add[r] * mul[i] + add[i];
        }
        mul[i] = 1;
        add[i] = 0;
        //将自己的更新信息修改
    }
}

//合并过程  唯一不同的就是有个down
int merge(int i, int j) {
    if (i == 0 || j == 0) {
        return i + j;
    }
    if (attack[i] > attack[j]) {
        swap(i, j);
    }
    down(i);
    rs[i] = merge(rs[i], j);
    if (dist[ls[i]] < dist[rs[i]]) {
        swap(ls[i], rs[i]);
    }
    dist[i] = dist[rs[i]] + 1;
    return i;
}

//弹出头结点  唯一不同的就是有个down
int pop(int i) {
    down(i);
    int ans = merge(ls[i], rs[i]);
    ls[i] = rs[i] = dist[i] = 0;
    return ans;
}

void compute() {
    deep[1] = 1;
    for (int i = 2; i <= n; i++) {
        deep[i] = deep[belong[i]] + 1;
    }
    //首先将各个节点的深度计算出来  因为所有节点的祖先都在前面  所以不要dfs也可以
    for (int i = 1; i <= m; i++) {
        if (top[first[i]] == 0) {
            //表示这个骑士第一个要攻击的城市还没有其他骑士攻击
            //那么这个城市的骑士团第一位就是他
            top[first[i]] = i;
        } else {
            //表示这个骑士第一个要攻击的城市有其他骑士攻击
            //那么就要和已经存在的骑士团合并为小根堆
            top[first[i]] = merge(top[first[i]], i);
        }
    }
    //将最初的各个城市的骑士团信息建立为小根堆
    for (int i = n; i >= 1; i--) {
        //从后往前遍历  因为后面的城市的骑士要是成功了 就会到前面的城市
        while (top[i] != 0 && attack[top[i]] < defend[i]) {
            //表示有骑士  但是最弱的骑士失败了
            die[top[i]] = i;//记录最弱的骑士死亡地点是在这个城市
            sacrifice[i]++;//那么这个城市死亡的骑士加一
            top[i] = pop(top[i]);//将最弱的骑士弹出
        }
        if (top[i] != 0) {
            //表示还有骑士  那么获得奖励
            upgrade(top[i], type[i], gain[i]);
            if (top[belong[i]] == 0) {
                //如果这个城市的上级城市没有骑士攻打
                //那么直接将这个骑士团全部给到上一个城市
                top[belong[i]] = top[i];
            } else {
                //否则和哪个城市的骑士团合并
                top[belong[i]] = merge(top[belong[i]], top[i]);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    //初始化信息
    prepare();
    //将城市的信息读入
    for (int i = 1; i <= n; i++) {
        cin >> defend[i];
    }
    for (int i = 2; i <= n; i++) {
        cin >> belong[i] >> type[i] >> gain[i];
    }
    //读入骑士信息
    for (int i = 1; i <= m; i++) {
        cin >> attack[i] >> first[i];
    }
    compute();
    for (int i = 1; i <= n; i++) {
        cout << sacrifice[i] << "\n";
    }
    for (int i = 1; i <= m; i++) {
        //记录攻克的城市
        cout << deep[first[i]] - deep[die[i]] << endl;
    }
    return 0;
}
