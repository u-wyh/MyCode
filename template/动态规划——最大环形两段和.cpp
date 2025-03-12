//p1121
#include<bits/stdc++.h>
using namespace std;
const int INF=0x3f3f3f3f;
const int N=2e5+5;

int n,f[N],g[N],a[N],sum=0,tot=0;

int query(){
    int res=-INF;
    for (int i=1;i<=n;i++)f[i]=max(f[i-1],0)+a[i];
    for (int i=n;i>0;i--)g[i]=max(g[i+1],0)+a[i];
    for (int i=1;i<=n;i++)f[i]=max(f[i-1],f[i]);
    for (int i=n;i>0;i--)g[i]=max(g[i+1],g[i]);
    for (int i=1;i<n;i++)res=max(res,f[i]+g[i+1]);
    return res;
}

int main()
{
    scanf("%d",&n);
    f[0]=g[n+1]=INT_MIN;//之所以要处理一下  是因为可能第一个数和最后一个数是负数  导致不对
//    memset(f,~0x3f,sizeof(f));
//    memset(g,~0x3f,sizeof(g));
    for (int i=1;i<=n;i++)
        scanf("%d",&a[i]),sum+=a[i],tot+=a[i]>0;
    int t1=query();//这是第一种情况 没有跨过环
    if (tot==1){
        //如果只有一个正数  那么直接结束
        //因为这种情况一定是没有跨过环
        printf("%d",t1);
    }else{
        //计算跨过环的情况 我们可以求最小的两段之和
        //我们整体取反  计算最大的即可
        for (int i=1;i<=n;i++)a[i]=-a[i];
        int t2=sum+query();
        if (!t2)t2=-INF;
        printf("%d",max(t1,t2));
    }
    return 0;
}
