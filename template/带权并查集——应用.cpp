//P4079
#include<bits/stdc++.h>
using namespace std;
const double eps = 1e-10;
const int MAXN = 10005;

int n,m;
int fa[MAXN];
double dis[MAXN];

int find(int x){
    if(x!=fa[x]){
        int tmp=fa[x];
        fa[x]=find(tmp);
        dis[x]*=dis[tmp];
    }
    return fa[x];
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int T;
    cin>>T;
    for(int t=1;t<=T;t++){
        cin>>n>>m;
        bool ans=true;
        for(int i=1;i<=n;i++){
            fa[i]=i;
            dis[i]=1.0;
        }
        for(int i=1;i<=m;i++){
            int u,v;
            double x,y;
            cin>>u>>v>>x>>y;
            int fu=find(u),fv=find(v);
            if(fu!=fv){
                fa[fu]=fv;
                dis[fu]*=(x*dis[v]/(y*dis[u]));
            }
            else{
                //如果他们在一个集合中  那么dis一定要是1
                if(abs(dis[u]/dis[v]-x/y)>eps){
                    ans=false;
                }
            }
        }
        if(ans){
            cout<<"Case #"<<t<<": Yes"<<endl;
        }
        else{
            cout<<"Case #"<<t<<": No"<<endl;
        }
    }
    return 0;
}
