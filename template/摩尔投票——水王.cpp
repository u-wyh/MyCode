// 出现次数大于n/2的数
// 给定一个大小为n的数组nums
// 水王数是指在数组中出现次数大于n/2的数
// 返回其中的水王数，如果数组不存在水王数返回-1
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
    if(hp==0){
        cout<<"no water-king"<<endl;
        return 0;
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(nums[i]==cand){
            ans++;
        }
    }
    if(ans>n/2){
        cout<<"the water-king is: "<<cand<<endl;
    }else{
        cout<<"no water-king"<<endl;
    }
    return 0;
}
