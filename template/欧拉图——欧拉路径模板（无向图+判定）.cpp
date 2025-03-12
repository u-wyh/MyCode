//P1341
//无向图+判定
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100;
const int MAXM = 2600;//最大的n不会超过这个数

int n;
vector<pair<int,int>>vec[MAXN];
stack<int>st;
int degree[MAXN];
int cnt=0;
bool exist[MAXM];

//用于判定是否联通
int vis[MAXN];
int fa[MAXN];

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
    }
}

void dfs(int u){
    for(int i=0;i<vec[u].size();i++){
        if(!exist[vec[u][i].second]){
            //这样做是为了不初始化数组
            exist[vec[u][i].second]=true;
            exist[vec[u][i].second^1]=true;
            //将这两条边全部否认
            dfs(vec[u][i].first);
        }
    }
    st.push(u);
}

int main()
{
    cin>>n;
    for(int i=0;i<60;i++){
        fa[i]=i;
    }
    int tmp=100;
    for(int i=1;i<=n;i++){
        char c1,c2;
        int u,v;
        cin>>c1>>c2;
        u=c1-'A',v=c2-'A';
        vec[u].push_back({v,cnt++});
        vec[v].push_back({u,cnt++});
        vis[u]=true,vis[v]=true;
        degree[u]++,degree[v]++;
        un(u,v);
        tmp=min(tmp,min(u,v));
    }
    int father=150;//记录公共父亲
    bool flag=true;//判断是否联通
    for(int i=0;i<=60;i++){
        if(vis[i]){
            if(father==150){
                father=find(i);
            }
            else{
                if(find(i)!=father){
                    flag=false;
                }
            }
        }
    }
    if(!flag){
        cout<<"No Solution"<<endl;
        return 0;
    }
    for(int i=0;i<60;i++){
        sort(vec[i].begin(),vec[i].end());
    }
    //判断起始点和是否符合要求
    int cnt=0;//记录度数为奇数的个数
    int s=-1;
    for(int i=0;i<60;i++){
        if(vis[i]){
            if(degree[i]%2){
                flag=false;
                cnt++;
                if(s==-1){
                    s=i;
                }
            }
        }
    }
    if(!flag&&cnt>=3){
        cout<<"No Solution"<<endl;
        return 0;
    }
    if(flag){
        s=tmp;
    }
    dfs(s);
    while(!st.empty()){
        char c=st.top()+'A';
        cout<<c;
        st.pop();
    }
    cout<<endl;
    return 0;
}
