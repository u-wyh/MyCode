#include<bits/stdc++.h>
using namespace std;
//可以实时查询

const int MAXN = 500001;
int arr[MAXN];
int Sort[MAXN];
int tree[MAXN];
int n, m;

int lowbit(int i) {
	return i & -i;
}

void add(int i, int v) {
    while (i <= m) {
        tree[i] += v;
        i += lowbit(i);
    }
}

// 1~i范围的累加和
long sum(int i) {
    long ans = 0;
    while (i > 0) {
        ans += tree[i];
        i -= lowbit(i);
    }
    return ans;
}

// 给定原始值v
// 返回排名值(排序部分1~m中的下标)
int Rank(int v) {
	int l = 1, r = m, mid;
    int ans = 0;
    while (l <= r) {
        mid = (l + r) / 2;
        if (Sort[mid] >= v) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

long compute() {
    sort(Sort+ 1,Sort+ n + 1);
    m = 1;
    for (int i = 2; i <= n; i++) {
        if (Sort[m] != Sort[i]) {
            Sort[++m] = Sort[i];
        }
    }
    //将数组去重
    for (int i = 1; i <= n; i++) {
        arr[i] = Rank(arr[i]);
        //将原有数组的值改为他们在数组中的大小排名  原有的数据本来就没有什么用
        //这样还更方便计算  以及节约空间
    }
    long ans = 0;
    for (int i = n; i >= 1; i--) {
        // 右边有多少数字是 <= 当前数值 - 1
        ans += sum(arr[i] - 1);
        // 增加当前数字的词频
        add(arr[i], 1);
    }
    return ans;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        Sort[i]=arr[i];//复制数组  用于排序和去重
    }
    cout<<compute();
    return 0;
}
