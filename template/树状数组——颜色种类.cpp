#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000010;

int arr[MAXN];
//原本的数组
struct Query{
    int l,r,subsrcipt;
}query[MAXN];
//查询区间数组  以及对应查询下标
int ans[MAXN];
//表示对应的查询下标对应的答案是什么
int Map[MAXN];
//标记一种颜色出现的最右位置是什么  如果是0表示还未出现
int tree[MAXN];
int n, m;

int lowbit(int i) {
    return i & -i;
}

void add(int i, int v) {
    while (i <= n) {
        tree[i] += v;
        i += lowbit(i);
    }
}
//在这道题目中  v的取值只有1和-1 表示消除这个位置上的值或者赋予一个位置值
//在这道题中 tree[i]如果是1  表示这个位置是目前某一个颜色的最右出现的地方  0表示还未出现或者不是最右位置

int sum(int i) {
    int ans = 0;
    while (i > 0) {
        ans += tree[i];
        i -= lowbit(i);
    }
    return ans;
}

int range(int l, int r) {
	return sum(r) - sum(l - 1);
}

bool cmp(Query a,Query b){
    return a.r<b.r;
}

void compute() {
    sort(query+1,query+ m + 1,cmp);
    //将查询数组根据查询右边界进行排序
    for (int s = 1, q = 1, l, r, i; q <= m; q++) {
        //这里似乎有双指针的风格
        r = query[q].r;
        for (; s <= r; s++) {
            int color = arr[s];
            if (Map[color] != 0) {
                add(Map[color], -1);
            }
            //如果当前颜色已经出现过  那么就要将其复原为0  因为他不再是最右的了
            add(s, 1);
            //将当前位置标记为1  表示是一种颜色出现的最右位置
            Map[color] = s;
            //记录这种颜色出现的最优位置
        }
        //完成了到临界点r之前的全部更新工作
        l = query[q].l;
        i = query[q].subsrcipt;
        ans[i] = range(l, r);
    }
    //每进行一轮  代表完成一个查询任务
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>query[i].l>>query[i].r;
        query[i].subsrcipt=i;
    }
    compute();
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}
