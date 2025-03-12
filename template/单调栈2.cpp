#include<bits/stdc++.h>
using namespace std;

int st[10000];
int n,r=0;
int nums[10000],R[10000];

int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>nums[i];
    int cur;
    for(int i=0;i<n;i++){
        while(r>0&&nums[st[r-1]]<nums[i]){
            cur=st[--r];
            R[cur]=i-cur;
        }
        st[r++]=i;
    }
    //±éÀú½×¶Î

    while (r > 0) {
        cur = st[--r];
        R[cur] = 0;
    }
    //ÇåËã½×¶Î

    for(int i=0;i<n;i++)
        cout<<R[i]<<endl;//记录从这个数字开始到下一个比自己大的数中间有几个数（包括自己）
    return 0;
}

