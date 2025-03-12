#include<bits/stdc++.h>
using namespace std;
const int MAXN =105;

int n,m;
int graph[MAXN][MAXN];
//�ڽӱ�
int Time=1;
//����ʱ���
int dfn[MAXN];
int low[MAXN];
int fa[MAXN];
//�ֱ���ÿ���ڵ�Ĳ���
int point[MAXN];//���
int bridge[1000][2];
int cnt=1;

void dfs(int x){
    dfn[x]=Time;
    low[x]=Time++;
    int child=0;
    //dfn����һ����ֵ  �㲻�ٸı�
    //low����ֵ��ʲô��ʵ����Ҫ  ��ֻ�з����ı����û�иı���һ�����õ���Ϣ
    for(int k=1;k<=n;k++){
        if(graph[x][k]){
            //��ֻ���Է����Լ��ܵ���ĵ�
            if(!dfn[k]){
                child++;
                fa[k]=x;
                //���Կ��������ȷ�����һ���ڵ�  ������ֵ�Լ�  �ڶ���dfs
                dfs(k);
                if(fa[x]==0&&child>=2){
                    point[x]=1;
                }
                if(fa[x]!=0&&low[k]>=dfn[x]){
                    point[x]=1;
                }
                if(low[k]>dfn[x]){
                    bridge[cnt][0]=x;
                    bridge[cnt++][1]=k;
                }
                low[x]=min(low[x],low[k]);
                //��Ϊyû�б����ʹ�  ������dfs(y)  ��ʱy��low�Ѿ�����ֵ   �����������������  ��ôҲ�Ѿ����
            }else if(k=fa[x]){
                //��ô˵��yһ����x֮ǰ����  ��Ȼ�γ�һ����
                low[x]=min(low[x],dfn[k]);
            }
            //ʣ�µ���������Ǽ��Ѿ������ʹ�  Ҳ����ջ��
        }
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
    //����ڽӱ�ĳ�ʼ��
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            //���û�б����ʵ��Ż����dfs
            dfs(i);
        }
    }
    for(int i=1;i<=n;i++){
        if(point[i]!=0){
            printf("%3d",i);
        }
    }
    cout<<endl;
    for(int i=1;i<=cnt;i++){
        printf("%d %d\n",bridge[i][0],bridge[i][1]);
    }
    return 0;
}

