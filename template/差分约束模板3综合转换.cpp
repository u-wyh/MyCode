#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e3+5;
const int MAXM = 2e4+5;

// ��ʽǰ���ǽ�ͼ��Ҫ
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;
int n,m;
//n��ʾһ���ж��ٸ���  m��ʾһ���ж�����·��
// Դ�������ÿ���ڵ�ľ����
int dis[MAXN];
// �ڵ㱻�ɳڵĴ���
int updateCnt[MAXN];
bool enter[MAXN];
//��ǰ�ڶ����еĻ�  ����true  �������false
queue<int >q;
//ÿһ�ֶ�����������һ��  ���һ������Ա��Ż�  ��ô�������


void build() {
    cnt = 1;
    fill(head+1, head+n + 1, 0);
    fill(enter+1,enter+ n + 1, false);
    fill(dis+ 1,dis+ n + 1, INT_MAX);
    fill(updateCnt+1,updateCnt+ n + 1, 0);
    while(!q.empty()){
        q.pop();
    }
}

void addEdge(int u, int v, int w) {
    Next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}
//������ʽǰ����

bool spfa() {
    dis[0] = 0;
    updateCnt[0]++;
    q.push(0) ;
    enter[0] = true;
    //�����Ŀ�е�Դ�㶼��0 ���ֲ���   �������ϵĲ��������1
    //ʵ����Ӧ�����Ϊ�����Դ���
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        enter[u] = false;
        for (int ei = head[u], v, w; ei > 0; ei = Next[ei]) {
            v = to[ei];
            w = weight[ei];
            if (dis[u] + w < dis[v]) {
                //���ֵ��С��  ��ô��Ҫ�ı�
                dis[v] = dis[u] + w;
                if (!enter[v]) {
                    //������ڶ����вŻ����
                    // �ɳڴ�������n-1���и���
                    if (++updateCnt[v] > n) {
                        return true;
                    }
                    q.push(v);
                    enter[v] = true;
                }
            }
        }
    }
    return false;
}

int main()
{
    cin>>n>>m;
    build();
    for(int i=1;i<=n;i++){
        addEdge(0,i,0);
    }
    for(int i=1;i<=m;i++){
        int op;
        cin>>op;
        if(op==1){
            int u,v,w;
            cin>>u>>v>>w;
            addEdge(u,v,-w);
        }
        else if(op==2){
            int u,v,w;
            cin>>u>>v>>w;
            addEdge(v,u,w);
        }
        else{
            int u,v;
            cin>>u>>v;
            addEdge(u,v,0);
            addEdge(v,u,0);
        }
    }
    if(spfa()){
        cout<<"No"<<endl;
    }else{
        cout<<"Yes"<<endl;
    }
    return 0;
}
