#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2001;
int Sort[MAXN];
// 维护信息 : 以数值i结尾的最长递增子序列，长度是多少
// 维护的信息以树状数组组织
int treeMaxLen[MAXN];
// 维护信息 : 以数值i结尾的最长递增子序列，个数是多少
// 维护的信息以树状数组组织
int treeMaxLenCnt[MAXN];
int nums[MAXN];
int m,n;
int maxLen, maxLenCnt;

int lowbit(int i) {
    return i & -i;
}

// 查询结尾数值<=i的最长递增子序列的长度，赋值给maxLen
// 查询结尾数值<=i的最长递增子序列的个数，赋值给maxLenCnt
void query(int i) {
    maxLen = maxLenCnt = 0;
    while (i > 0) {
        if (maxLen == treeMaxLen[i]) {
            maxLenCnt += treeMaxLenCnt[i];
            //如果最大值一样   那么累加
        } else if (maxLen < treeMaxLen[i]) {
            maxLen = treeMaxLen[i];
            maxLenCnt = treeMaxLenCnt[i];
        }
        i -= lowbit(i);
    }
}

// 以数值i结尾的最长递增子序列，长度达到了len，个数增加了cnt
// 更新树状数组
void add(int i, int len, int cnt) {
    while (i <= m) {
        if (treeMaxLen[i] == len) {
            treeMaxLenCnt[i] += cnt;
        } else if (treeMaxLen[i] < len) {
            treeMaxLen[i] = len;
            treeMaxLenCnt[i] = cnt;
        }
        //剩下的那种情况  不做出任何改变
        i += lowbit(i);
        //将所有包含这个的全部更新
    }
}

int Rank(int v) {
	int ans = 0;
    int l = 1, r = m, mid;
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

int findNumberOfLIS(int* nums) {
    for (int i = 1; i <= n; i++) {
        Sort[i] = nums[i];
    }
    sort(Sort+ 1,Sort+ n + 1);
    m = 1;
    for (int i = 2; i <= n; i++) {
        if (Sort[m] !=Sort[i]) {
            Sort[++m] = Sort[i];
        }
    }
    //以上部分实现排序 离散化  以及去重

    memset(treeMaxLen,0,sizeof(treeMaxLen));
    memset(treeMaxLenCnt,0,sizeof(treeMaxLenCnt));
    int i;
    for (int k=1;k<=n;k++) {
        int num=nums[k];
        int i = Rank(num);
        query(i - 1);
        if (maxLen == 0) {
            // 如果查出数值<=i-1结尾的最长递增子序列长度为0
            // 那么说明，以值i结尾的最长递增子序列长度就是1，计数增加1
            //这里是为了特判i是1的情况  避免错误
            add(i, 1, 1);
        } else {
            // 如果查出数值<=i-1结尾的最长递增子序列长度为maxLen != 0
            // 那么说明，以值i结尾的最长递增子序列长度就是maxLen + 1，计数增加maxLenCnt
            add(i, maxLen + 1, maxLenCnt);
        }
        //举个例子 如果i是16  并且query(i-1)返回的值是长为5 共5个  那么add:长为6 5个
        //如果i是1   那么返回的必然是0 0 当是增加的是1 1
    }
    query(m);
    //m是数组中的最大值  那么这个操作相当于查询整个树状数组中最长的长度以及相应的个数
    return maxLenCnt;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>nums[i];
    cout<<findNumberOfLIS(nums);
    return 0;
}
