#include<bits/stdc++.h>
using namespace std;
const int LIMIT = 80001;

int n,m;
int cnt=1;
int Left[LIMIT];
int Right[LIMIT];
long sum[LIMIT];
long add[LIMIT];

void up(int h, int l, int r) {
    sum[h] = sum[l] + sum[r];
}

void lazy(int i, long v, int n) {
    sum[i] += v * n;
    add[i] += v;
}

void down(int i, int ln, int rn) {
    if (add[i] != 0) {
        // 懒更新任务下发
        // 那左右两侧的空间需要准备好
        if (Left[i] == 0) {
            Left[i] = ++cnt;
        }
        if (Right[i] == 0) {
            Right[i] = ++cnt;
        }
        lazy(Left[i], add[i], ln);
        lazy(Right[i], add[i], rn);
        add[i] = 0;
    }
}

void Add(int jobl, int jobr, long jobv, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        lazy(i, jobv, r - l + 1);
    } else {
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        if (jobl <= mid) {
            // 不得不去左侧才会申请
            if (Left[i] == 0) {
                Left[i] = ++cnt;
            }
            Add(jobl, jobr, jobv, l, mid, Left[i]);
        }
        if (jobr > mid) {
            // 不得不去右侧才会申请
            if (Right[i] == 0) {
                Right[i] = ++cnt;
            }
            Add(jobl, jobr, jobv, mid + 1, r, Right[i]);
			}
        up(i, Left[i], Right[i]);
    }
}

long query(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return sum[i];
    }
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);
    long ans = 0;
    if (jobl <= mid) {
        // 发现左侧申请过空间才有必要去查询
        // 如果左侧从来没有申请过空间那查询结果就是0
        if (Left[i] != 0) {
            ans += query(jobl, jobr, l, mid, Left[i]);
        }
    }
    if (jobr > mid) {
        // 发现右侧申请过空间才有必要去查询
        // 如果右侧从来没有申请过空间那查询结果就是0
        if (Right[i] != 0) {
            ans += query(jobl, jobr, mid + 1, r, Right[i]);
        }
    }
    return ans;
}

int main()
{
    cin>>n>>m;
    long k;
    for(int i=1,op,l,r;i<=m;i++){
        cin>>op>>l>>r;
        if(op==1){
            cin>>k;
            Add(l,r,k,1,n,1);
        }else{
            cout<<query(l,r,1,n,1)<<endl;
        }
    }
    return 0;
}
