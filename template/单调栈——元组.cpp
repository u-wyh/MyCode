#include<bits/stdc++.h>
using namespace std;

int n;
int st[10000],nums[10000];
int r=1;

int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>nums[i];
    for(int i=1;i<n;i++){
        if(nums[st[r-1]]>nums[i]){
            st[r++]=i;
        }
    }
    int ans=0;
    for(int i=n-1;i>=0;i--){
        while(r>0&&nums[st[r-1]]<=nums[i]){
            ans=max(ans,i-st[--r]);
        }
    }
    cout<<ans;
    return 0;
}
