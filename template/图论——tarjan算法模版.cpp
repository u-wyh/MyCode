#include<bits/stdc++.h>
using namespace std;
const int MAXN =105;

int n,m;
int graph[MAXN][MAXN];
//邻接表
stack<int >st;
//栈结构  用于储存节点
int Time=1;
//建立时间戳
int dfn[MAXN];
int low[MAXN];
//分别是每个节点的参数
bool instack[MAXN];
//判断是否在栈中

void dfs(int x){
    dfn[x]=Time;
    low[x]=Time++;
    //dfn数组一经赋值  便不再改变
    //low数组值是什么其实不重要  他只有发生改变或者没有改变这一个有用的信息
    st.push(x);
    //压入栈中
    instack[x]=true;
    for(int k=1;k<=n;k++){
        //printf("%d ",graph[x][k]);
        if(graph[x][k]){
            //他只可以访问自己能到达的点
            if(!dfn[k]){
                //可以看出它是先访问下一个节点  后来赋值自己  第二种dfs
                dfs(k);
                low[x]=min(low[x],low[k]);
                //因为y没有被访问过  所以先dfs(y)  此时y的low已经被赋值   并且如果发生了修正  那么也已经完成
            }else if(instack[k]){
                //那么说明y一定在x之前访问  必然形成一个环
                low[x]=min(low[x],dfn[k]);
            }
            //剩下的那种情况是既已经被访问过  也不在栈中
        }
    }
    cout<<endl;
    if(dfn[x] == low[x]){
        //如果两者相同  开始输出
        int tmp;
        do{
            tmp = st.top();
            st.pop();
            instack[tmp] = false;
            cout<<tmp<<' ';
        }while(tmp != x);
        //直到输出x为止
        cout<<endl;
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        graph[u][v]=1;
    }
    //完成邻接表的初始化
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            //如果没有被访问到才会进入dfs
            dfs(i);
        }
    }
    return 0;
}
