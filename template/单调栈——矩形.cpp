#include<bits/stdc++.h>
using namespace std;

int st[10000];
int n,r=0;
int nums[10000],L;
int ans=0;

int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>nums[i];
    int cur;
    for(int i=0;i<n;i++){
        while(r>0&&nums[st[r-1]]>=nums[i]){
            cur=st[--r];
            L=r>0?st[r-1]:-1;
            ans=max(ans,nums[cur]*(i-1-L));
        }
        st[r++]=i;
    }

    while (r > 0) {
        cur = st[--r];
        L = r > 0 ? st[r - 1] : -1;
        ans=max(ans,nums[cur]*(n-1-L));
    }

    cout<<ans<<endl;
    return 0;
}

