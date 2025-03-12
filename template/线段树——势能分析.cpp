//对数组进行更新操作，并求最大值
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

long arr[MAXN];
long sum[MAXN << 2];
long Max[MAXN<<2];
int n,m;

//比较左右两边最大值
void up(int i) {
    sum[i] = sum[i << 1]+sum[i << 1 | 1];
    Max[i] = max(Max[i << 1] ,Max[i << 1 | 1]);
}

void build(int l, int r, int i) {
    if (l == r) {
        sum[i] = arr[l];
        Max[i] = arr[l];
    } else {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
}

// sqrt方法是最核心的
// 注意和常规线段树不一样，这里没有懒更新，也就不需要有down方法
// 只有根据范围最大值信息的剪枝
// 时间复杂度的分析就是课上讲的势能分析
// 不用纠结单次调用的复杂度
// 哪怕调用再多次sqrt方法，总的时间复杂度也就是O(n * 6 * logn)
void Sqrt(int jobl, int jobr, int l, int r, int i) {
    if (l == r) {
        long sqrt1 = (long) sqrt(Max[i]);
        sum[i] = sqrt1;
        Max[i] = sqrt1;
    } else {
        int mid = (l + r) >> 1;
        if (jobl <= mid && Max[i << 1] > 1) {
            Sqrt(jobl, jobr, l, mid, i << 1);
        }
        if (jobr > mid && Max[i << 1 | 1] > 1) {
            Sqrt(jobl, jobr, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
}

long query(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return sum[i];
    }
    int mid = (l + r) >> 1;
    long ans = 0;
    if (jobl <= mid) {
        ans +=query(jobl, jobr, l, mid, i << 1);
    }
    if (jobr > mid) {
        ans +=query(jobl, jobr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>arr[i];
    build(1,n,1);
    cin>>m;
    long jobv;
    for (int i = 1, op, jobl, jobr; i <= m; i++) {
        cin>>op;
        cin>>jobl;
        cin>>jobr;
        if(jobl>jobr){
            int tmp=jobl;
            jobl=jobr;
            jobr=tmp;
        }
        if (op == 0) {
            Sqrt(jobl, jobr, 1, n, 1);
        } else {
            cout<<query(jobl, jobr, 1, n, 1)<<endl;
        }
    }
    return 0;
}

