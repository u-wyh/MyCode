//P1300
#include<bits/stdc++.h>
using namespace std;

int n,m;
char s[35][35];
int nums[35][35];
int dis[35][35][4];
bool vis[35][35][4];
int walk[4][2]={{0,1},{1,0},{0,-1},{-1,0}};//东 南 西 北
// 定义节点结构体
struct Node {
    int first,second,third,fourth; // 我们将基于这个元素进行排序
};
struct Compare {
    bool operator()(const Node& lhs, const Node& rhs) const {
        return lhs.fourth > rhs.fourth;
    }
};
priority_queue<Node, std::vector<Node>, Compare> heap;
int enx,eny,stx,sty,stdir;//东0 南1 西2 北3

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int k=0;k<4;k++){
                dis[i][j][k]=1e9;//初始化距离
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char c;
            cin>>c;
            if(c!='.'){
                nums[i][j]=1;
                if(c!='#'&&c!='F'){
                    stx=i,sty=j;
                    if(c=='E'){
                        stdir=0;
                    }else if(c=='S'){
                        stdir=1;
                    }else if(c=='W'){
                        stdir=2;
                    }else if(c=='N'){
                        stdir=3;
                    }
                }else if(c=='F'){
                    enx=i;
                    eny=j;
                }
            }
        }
    }
    dis[stx][sty][stdir]=1;
    heap.push({stx,sty,stdir});
    while(!heap.empty()){
        Node u=heap.top();
        heap.pop();
        int ux=u.first,uy=u.second,udir=u.third;

        if(ux==enx&&uy==eny){
            cout<<dis[enx][eny][udir]-1<<endl;
            return 0;
        }
        if(vis[ux][uy][udir]){
            continue;//表示之前有更小的值弹出过
        }
        vis[ux][uy][udir]=true;//表示这绝对是这个状态最小值了  不会在变小了

        int flag=1;//用于判断是否后退

        //左转
        int nx=ux+walk[(udir+3)%4][0];
        int ny=uy+walk[(udir+3)%4][1];
        int ndir=(udir+3)%4;
        if(!vis[nx][ny][ndir]&&nx<=n&&nx>0&&ny>0&&ny<=m&&nums[nx][ny]){
            flag=0;
            if(dis[nx][ny][ndir]>dis[ux][uy][udir]+1){
                dis[nx][ny][ndir]=dis[ux][uy][udir]+1;
                heap.push({nx,ny,ndir,dis[nx][ny][ndir]});
            }
        }

        //右转
        nx=ux+walk[(udir+1)%4][0];
        ny=uy+walk[(udir+1)%4][1];
        ndir=(udir+1)%4;
        if(!vis[nx][ny][ndir]&&nx<=n&&nx>0&&ny>0&&ny<=m&&nums[nx][ny]){
            flag=0;
            if(dis[nx][ny][ndir]>dis[ux][uy][udir]+5){
                dis[nx][ny][ndir]=dis[ux][uy][udir]+5;
                heap.push({nx,ny,ndir,dis[nx][ny][ndir]});
            }
        }

        //直行
        nx=ux+walk[udir][0];
        ny=uy+walk[udir][1];
        ndir=udir;
        if(!vis[nx][ny][ndir]&&nx<=n&&nx>0&&ny>0&&ny<=m&&nums[nx][ny]){
            flag=0;
            if(dis[nx][ny][ndir]>dis[ux][uy][udir]){
                dis[nx][ny][ndir]=dis[ux][uy][udir];
                heap.push({nx,ny,ndir,dis[nx][ny][ndir]});
            }
        }

        if(flag){
            //表示可以后退
            int nx=ux+walk[(udir+2)%4][0];
            int ny=uy+walk[(udir+2)%4][1];
            int ndir=(udir+2)%4;
            if(vis[nx][ny][ndir]||nx<=0||nx>n||ny<=0||ny>m||nums[nx][ny]==0){
                continue;
            }
            if(dis[nx][ny][ndir]>dis[ux][uy][udir]+10){
                dis[nx][ny][ndir]=dis[ux][uy][udir]+10;
                heap.push({nx,ny,ndir,dis[nx][ny][ndir]});
            }
        }
    }
    //cout<<666<<endl;
    return 0;
}
