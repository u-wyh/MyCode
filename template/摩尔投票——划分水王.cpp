// 划分左右使其水王数相同
// 给定一个大小为n的数组nums
// 水王数是指在数组中出现次数大于n/2的数
// 返回其中的一个划分点下标，使得左侧水王数等于右侧水王数
// 如果数组不存在这样的划分返回-1
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 20005;

int n;
int nums[MAXN];
int cand,hp;//其中cand  hp分别是候选数字 血量

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    for(int i=1;i<=n;i++){
        if(hp==0){
            //如果当前血量hp==0  说明没有候选数字
            //那么接下来的数字自动为候选数字  并且hp==1
            cand=nums[i];
            hp=1;
        }else if(nums[i]==cand){
            //如果当前数字和候选数字一样  血量hp++
            hp++;
        }else{
            //如果不一样  那么hp--
            //不用担心候选数字  如果hp为1 那么变为0  如果大于1  说明候选数字没有变化
            hp--;
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(nums[i]==cand){
            ans++;
        }
    }
    // lc : 水王数左侧出现的词频
    // rc : 水王数右侧出现的词频
    for (int i = 1, lc = 0, rc = ans; i < n; i++) {
        if (nums[i] == cand) {
            lc++;
            rc--;
        }
        if (lc > i / 2 && rc > (n - i) / 2) {
            // 找到了划分点直接返回
            cout<<i<<endl;
            return 0;
        }
    }
    cout<<"not find"<<endl;
    return 0;
}

