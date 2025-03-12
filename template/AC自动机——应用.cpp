//P3082
#include<bits/stdc++.h>
using namespace std;
// 所有目标字符串的总字符数量
const int MAXS = 1005;
const int MAXN = 1e4+5;

// AC自动机
int tree[MAXS][26];
int fail[MAXS];
int cnt = 0;

bool en[MAXS];
// 可以用作队列或者栈，一个容器而已
int box[MAXS];

string s,str;
int path;
int n;

int dp[MAXN][MAXS];

void insert(string word){
    //i是目标串的编号
    int cur=0;//头结点设置为0
    for (char ch : word){
        path=ch-'a';
        if(tree[cur][path]==0){
            tree[cur][path]=++cnt;
            //没有路就要新建一条路  并赋予编号
        }
        cur=tree[cur][path];
    }
    en[cur]=true;
}

void setFail() {
    // box当做队列来使用
    int l = 0;
    int r = 0;
    for (int i = 0; i <= 25; i++) {
        if (tree[0][i] > 0) {
            box[r++] = tree[0][i];
            //0节点中只有有孩子的节点加入队列中
            //这个队列里面存储过的所有节点都要有fail
        }
    }
    while (l < r) {
        int u = box[l++];
        for (int i = 0; i <= 25; i++) {
            if (tree[u][i] == 0) {
                tree[u][i] = tree[fail[u]][i];
            } else {
                fail[tree[u][i]] = tree[fail[u]][i];//设置这个孩子节点的fail指针   直通表辅助不用绕环
                box[r++] = tree[u][i];//表示有这条支路  加入到队列中
            }
        }
    }
}
//报警标志的迁移

int main()
{
    cin>>str>>s;
    insert(s);
    setFail();
    int n=str.size();
    //cout<<n<<' '<<cnt<<endl;
    //dp的含义是str的前i个字符  和  节点j匹配  最多剩余多少个字母
    for(int i=1;i<=n;i++){
        for(int j=0;j<=cnt;j++){
            dp[i][j]=max(dp[i-1][j],dp[i][j]);
            if(!en[tree[j][str[i-1]-'a']]){
                dp[i][tree[j][str[i-1]-'a']]=max(dp[i][tree[j][str[i-1]-'a']],dp[i-1][j]+1);
            }
        }
    }
    int ans=0;
    for(int i=0;i<=cnt;i++){
        ans=max(ans,dp[n][i]);
    }
    cout<<(n-ans)<<endl;
    return 0;
}
