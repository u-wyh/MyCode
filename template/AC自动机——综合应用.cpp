// 数数(利用AC自动机检查命中)
//关键词报警功能
#include<bits/stdc++.h>
using namespace std;
// 所有目标字符串的数量
const int MAXN = 10001;
// 所有目标字符串的总字符数量
const int MAXS = 10001;

// 记录每个节点是否报警
bool alert[MAXS];

// AC自动机
int tree[MAXS][26];
int fail[MAXS];
int cnt = 0;

// 每个节点记录词频
int times[MAXS];
// 可以用作队列或者栈，一个容器而已
int box[MAXS];

string s;
int path;
int n;

void insert(int i,string word){
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
    alert[cur]=true;
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
        // 命中标记前移
        alert[u] |= alert[fail[u]];
    }
}
//报警标志的迁移

int main()
{
    cout<<"请输入关键词数量: ";
    cin>>n;
    for(int i=1;i<=n;i++){
        cout<<"请输入第 "<<i<<" 个关键词: ";
        string str;
        cin>>str;
        insert(i,str);
    }
    setFail();
    cout<<"请输入待测字符串: ";
    cin>>s;
    int u=0,k=0,flag=0;
    for (char ch:s) {
        if(alert[u]){
            flag=1;
            cout<<"在第 "<<k<<" 个位置触发关键词！"<<endl;
            break;
        }
        k++;
        u = tree[u][ch - 'a'];//表示到达下一个节点
    }
    if(flag!=1)
        cout<<"输入正常，未引发任何问题。"<<endl;
    return 0;
}

/*
6
beta
alpha
haha
delta
dede
tata
dedeltalphahahahototatalpha

6
beta
alpha
haha
delta
dede
tata
dedaltblphahbhahototatolqha
*/
