#include<bits/stdc++.h>
using namespace std;

int st[10000];
int n,r=0;
int nums[10000],L[10000],R[10000];

int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>nums[i];
    int cur;
    for(int i=0;i<n;i++){
        while(r>0&&nums[st[r-1]]>=nums[i]){
            cur=st[--r];
            L[cur]=r>0?st[r-1]:-1;
            R[cur]=i;
        }
        st[r++]=i;
    }
    //±éÀú½×¶Î

    while (r > 0) {
        cur = st[--r];
        L[cur] = r > 0 ? st[r - 1] : -1;
        R[cur] = -1;
    }
    //ÇåËã½×¶Î

    for(int i=n-2;i>=0;i--){
        if(R[i]!=-1&&nums[i]==nums[R[i]])
            R[i]=R[R[i]];
    }
    //ÐÞÕý½×¶Î

    for(int i=0;i<n;i++)
        cout<<L[i]<<' '<<R[i]<<endl;
    return 0;
}
