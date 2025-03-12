#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin>>n;
    int nums[n+1];
    for(int i=0;i<=n;i++)
        cin>>nums[i];
    int slow=nums[0];
    int fast=nums[nums[0]];
    while(slow!=fast){
        slow=nums[slow];
        fast=nums[nums[fast]];
    }
    fast=0;
    while(slow!=fast){
        slow=nums[slow];
        fast=nums[fast];
    }
    cout<<slow;
    return 0;
}
