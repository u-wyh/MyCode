// 树的序
// 给定一个长度为n的数组arr，表示依次插入数字，会形成一棵搜索二叉树
// 也许同样的一个序列，依次插入数字后，也能形成同样形态的搜索二叉树
// 请返回字典序尽量小的结果
// 1 <= n <= 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P1377
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int arr[MAXN];
int ls[MAXN];
int rs[MAXN];
int sta[MAXN];

void build() {
    for (int i = 1, top = 0, pos = 0; i <= n; i++) {
        pos = top;
        while (pos > 0 && arr[sta[pos]] > arr[i]) {
            pos--;
        }
        if (pos > 0) {
            rs[sta[pos]] = i;
        }
        if (pos < top) {
            ls[i] = sta[pos + 1];
        }
        sta[++pos] = i;
        top = pos;
    }
}

void pre() {
    int size = 1, i = 0, cur;
    while (size > 0) {
        cur = sta[size--];
        arr[++i] = cur;
        if (rs[cur] != 0) {
            sta[++size] = rs[cur];
        }
        if (ls[cur] != 0) {
            sta[++size] = ls[cur];
        }
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        int k;
        cin>>k;
        arr[k]=i;
    }
    build();
    pre();
    for(int i=1;i<=n;i++){
        cout<<arr[i]<<' ';
    }
    return 0;
}
