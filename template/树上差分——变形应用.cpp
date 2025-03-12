//P9648
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 30;

int n;

//这个sum的含义是如果你想成为头结点    你必须要解决的问题数目
//就是一个节点有两条相同边权的边   有多少个这样的问题要解决
int sum;
int arr[MAXN];//表示这个节点可以解决的问题个数  在没有统计最终答案的时候是差分数组
bool flag;//判断是否有答案
int ans;

//用于统计来到当前节点  他的孩子信息
int tot[MAXM];
int lst[MAXM];

int cnt=1;
int head[MAXN];
int to[MAXN<<1];
int weight[MAXN<<1];
int Next[MAXN<<1];

void build(){
    cnt=1,ans=0,flag=false;
    sum=0;
    for(int i=1;i<=n;i++){
        head[i]=0;
        arr[i]=0;
    }
}

void addedge(int u,int v,int w){
    Next[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void dfs(int u,int fa,int val){
    //u是从fa经过val的边权来的
    for(int i=1;i<=27;i++){
        tot[i]=lst[i]=0;//全部清空原始信息
    }
    for(int i=head[u];i;i=Next[i]){
        int v=to[i],w=weight[i];
        if(v==fa){
            //不走重复边
            continue;
        }
        if(w==val){
            //边权和父亲相同  那么当前节点的上方其实不受影响
            //而且这条边也不影响
			arr[u]--;
			arr[v]++;
        }
        if(tot[w]==1){
            //相同的边权以前有过一条
			if(val == w){
			    //现在又来一条 还跟父亲是一样的  也就是这个节点有三个相同的边权  直接结束
				flag = true;
			}
			else{
				arr[lst[w]]++, arr[v]++, sum++;
			}
        }
        else if(tot[w]>1){
            flag=true;
        }
        tot[w]++,lst[w]=v;
    }
    for(int i=head[u];i;i=Next[i]){
        int v=to[i],w=weight[i];
        if(v==fa){
            //不走重复边
            continue;
        }
        dfs(v,u,w);
    }
}

void compute(int u,int fa){
    arr[u]+=arr[fa];
    if(arr[u]==sum){
        ans++;
    }
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        if(v!=fa){
            compute(v,u);
        }
    }
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        build();
        for(int i=1;i<n;i++){
            int u,v,w;
            char c;
            cin>>u>>v>>c;
            w=c-'a'+1;
            addedge(u,v,w),addedge(v,u,w);
        }
        dfs(1,0,0);
        if(flag){
            cout<<0<<endl;
        }
        else{
            compute(1,0);
            cout<<ans<<endl;
        }
    }
    return 0;
}
