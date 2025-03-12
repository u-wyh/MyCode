#include<bits/stdc++.h>
using namespace std;

struct fish{
    int weight,turn;
}nums[1000];
int n;
int st[1000],r=0,ans=0;

int main()
{
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>nums[i].weight;
        nums[i].turn=0;
    }
    for(int i=n-1;i>=0;i--){
        while(r>0&&nums[st[r-1]].weight<nums[i].weight){
            nums[i].turn=max(nums[i].turn+1,nums[st[--r]].turn);
        }
        st[r++]=i;
        ans=max(ans,nums[i].turn);
    }
    cout<<ans;
    return 0;
}
