// �ۻ�Ա������ - TSP����
// ĳ����n����ׯ(1<=n<=20)����һ���ۻ�Ա����Ҫ��������ׯȥ�ۻ�
// ����ׯ֮���·��s(1<=s<=1000)����֪��
// ��A�嵽B���·�̣���B��A��·��಻ͬ(�����Ȩͼ)
// Ϊ�����Ч�ʣ������̵������ÿ����ׯһ�Σ�Ȼ�󷵻��̵����ڵĴ壬
// �����̵����ڵĴ�ׯΪ1
// ����֪��ѡ��ʲô����·�߲���ʹ���ߵ�·�����
// �������ѡ��һ����̵�·
// �������� : https://www.luogu.com.cn/problem/P1171
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ֱ��ͨ��

#include<bits/stdc++.h>
using namespace std;

int n;
int graph[20][20];
int dp[1<<20][20];
int ans=INT_MAX;

void f(int status,int now,int cost){
    //��ʾ״̬Ϊstatus   ����λ��now
    if(ans<=cost)
        return ;
    if(status==(1<<n)-1){
        cost+=graph[now][0];
        ans=min(ans,cost);
    }
    if(dp[status][now]!=INT_MAX){
        if(cost>=dp[status][now]){
            return ;
        }
        else{
            dp[status][now]=cost;
        }
    }
    for(int i=0;i<n;i++){
        if(!(status&(1<<i))&&dp[status^(1<<i)][i]>cost+graph[now][i]){
            //dp[status^(1<<i)][i]=cost+graph[now][i];
            f(status^(1<<i),i,cost+graph[now][i]);
        }
    }
    dp[status][now]=cost;
}

int main()
{
    cin>>n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>graph[i][j];
        }
    }
    for(int i=0;i<(1<<n);i++){
        for(int j=0;j<n;j++){
            dp[i][j]=INT_MAX;
        }
    }
    f(1,0,0);
    cout<<ans;
    return 0;
}
