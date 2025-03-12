//P7771
//这个是有向图
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;
int del[MAXN];//记录节点i的边已经删除了几条  下一次从第几条开始选
int in[MAXN];
int out[MAXN];
stack<int>st;
vector<int>vec[MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

void dfs(int u){
    for(int i=del[u];i<vec[u].size();i=del[u]){
        del[u]++;
        dfs(vec[u][i]);
    }
    st.push(u);
}

int main()
{
    n=read(),m=read();
    int u,v;
    for(int i=1;i<=m;i++){
        u=read(),v=read();
        vec[u].push_back(v);
        out[u]++,in[v]++;
    }
    for(int i=1;i<=n;i++){
        sort(vec[i].begin(),vec[i].end());//这道题要求按照字典序输出   所以要排序
    }
    //保证将有向边视为无向边后图连通  所以最低是弱连通
    //接下来统计各个点的入度和出度是否符合
    bool flag=true;//表示所有的节点  入度和出度相同
    int s=1;//初始点  可能会变化
    int cnt1=0,cnt2=0;//分别是  入-出=1  和  出-入=1
    for(int i=1;i<=n;i++){
        if(in[i]!=out[i]){
            flag=false;
            if(in[i]-out[i]==1){
                cnt1++;
            }
            else if(out[i]-in[i]==1){
                cnt2++;
                s=i;
            }
            else{
                cout<<"No"<<endl;
                return 0;
            }
        }
    }
    if(!flag&&!(cnt1==cnt2&&cnt1==1)){
        //既不符合欧拉回路 也不符合欧拉通路
        cout<<"No"<<endl;
        return 0;
    }
    dfs(s);
    while(!st.empty()){
        cout<<st.top()<<' ';
        st.pop();
    }
    return 0;
}
