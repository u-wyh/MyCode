#include<bits/stdc++.h>
using namespace std;

int n,m;
int a,b,c;
int nums[1000];

int main()
{
    cin>>n>>m;
    while(m--){
        cin>>a>>b>>c;
        nums[a]+=c;
        nums[b+1]-=c;
    }
    for(int i=1;i<=n;i++){
        nums[i]+=nums[i-1];
        printf("%3d",nums[i]);
    }
    return 0;
}
