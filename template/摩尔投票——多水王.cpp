#include<bits/stdc++.h>
using namespace std;
const int MAXN = 10000;

int n,k;
int arr[MAXN];
struct node{
    int val,cnt;
}cand[100];
//因为k的值不是很大  并且最多水王数不会大于等于k
//那么我们统计血量和候选数字的数组最大只用开到k-1即可

void update(int num) {
    //输入一个数字用于更新
    for (int i = 1; i < k; i++) {
        if (cand[i].val == num && cand[i].cnt > 0) {
            cand[i].cnt++;
            return;
        }
    }
    //如果这个候选数组中存在这个值并且次数不为0  那么可以让这个数字次数加1
    for (int i = 1; i < k; i++) {
        if (cand[i].cnt == 0) {
            cand[i].val = num;
            cand[i].cnt = 1;
            return;
        }
    }
    //如果这个数字还没有填满  那么就加入这个数字
    for (int i = 1; i < k; i++) {
        if (cand[i].cnt > 0) {
            cand[i].cnt--;
        }
    }
    //否则所有的数字全部减一
}

void collect() {
    for (int i = 1, cur, real; i < k; i++) {
        if (cand[i].cnt > 0) {
            cur = cand[i].val;
            real = 0;
            for (int j=1;j<=n;j++) {
                if (cur == arr[j]) {
                    real++;
                }
            }
            if (real <= n / k) {
                cand[i].cnt=0;
            }
        }
    }
}
//检测这个数字是不是符合我们的要求

int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    for(int i=1;i<=n;i++){
        update(arr[i]);
    }
    for(int i=1;i<k;i++){
        printf("%3d %3d\n",cand[i].val,cand[i].cnt);
    }
    collect();
    for(int i=1;i<k;i++){
        if(cand[i].cnt)
            printf("%3d",cand[i].val);
    }
    return 0;
}
