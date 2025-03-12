// 甄别食物链
// 一共有n只动物，编号1 ~ n，每只动物都是A、B、C中的一种，A吃B、B吃C、C吃A
// 一共有k句话，希望你判断哪些话是假话，每句话是如下两类句子中的一类
// 1 X Y : 第X只动物和第Y只动物是同类
// 2 X Y : 第X只动物吃第Y只动物
// 当前的话与前面的某些真话冲突，视为假话
// 当前的话提到的X和Y，有任何一个大于n，视为假话
// 当前的话如果关于吃，又有X==Y，视为假话
// 返回k句话中，假话的数量
// 1 <= n <= 5 * 10^4    1 <= k <= 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P2024
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 50001;

int n,k,ans;
int fa[MAXN];
// dist[i] = 0，代表i和头是同类
// dist[i] = 1，代表i吃头
// dist[i] = 2，代表i被头吃
int dist[MAXN];

void prepare() {
    ans = 0;
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
        dist[i] = 0;
        //一开始自己和自己肯定是同类
    }
}

int find(int i) {
    if (i != fa[i]) {
        int tmp = fa[i];
        fa[i] = find(tmp);
        dist[i] = (dist[i] + dist[tmp]) % 3;
        //更新关系比较特殊
    }
    return fa[i];
}

// op == 1, 1 l r，l和r是同类
// op == 2, 2 l r，l吃r
void un(int op, int l, int r) {
    int lf = find(l), rf = find(r), v = op == 1 ? 0 : 1;//判断二者的关系
    if (lf != rf) {
        fa[lf] = rf;
        dist[lf] = (dist[r] - dist[l] + v + 3) % 3;
    }
}

bool check(int op, int l, int r) {
    if (l > n || r > n || (op == 2 && l == r)) {
        //不合理的情况  直接输出false
        return false;
    }
    if (find(l) == find(r)) {
        //处于一个集合中
        if (op == 1) {
            if (dist[l] != dist[r]) {
                return false;
            }
        } else {
            if ((dist[l] - dist[r] + 3) % 3 != 1) {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    cin>>n>>k;
    prepare();
    for(int i=1,op,l,r;i<=k;i++){
        cin>>op>>l>>r;
        if(!check(op,l,r)){
            ans++;
        }
        else{
            un(op,l,r);
        }
    }
    cout<<ans<<endl;
    return 0;
}
