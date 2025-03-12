#include<bits/stdc++.h>
using namespace std;

const int MAXN = 10001;
// 所有目标字符串的总字符数量
const int MAXS = 2000001;

// 记录每个目标串的结尾节点编号
int en[MAXN];

// AC自动机
int tree[MAXS][127];
int fail[MAXS];
int cnt = 0;

// 具体题目相关，本题为收集词频
// 所以每个节点记录词频
int times[MAXS];
// 可以用作队列或者栈，一个容器而已
int box[MAXS];

// 链式前向星，为了建立fail指针的反图
int head[MAXS];
int Next[MAXS];
int to[MAXS];
int edge = 0;

string s;
int path;
int n;
string str[100];

void insert(int i,string word){
    //i是目标串的编号
    int cur=0;//头结点设置为0
    for (char ch : word){
        path=ch-'0';
        if(tree[cur][path]==0){
            tree[cur][path]=++cnt;
            //没有路就要新建一条路  并赋予编号
        }
        cur=tree[cur][path];
    }
    en[i]=cur;
}

// 加入所有目标字符串之后
// 设置fail指针 以及 设置直接直通表
// 做了AC自动机固定的优化
void setFail() {
    // box当做队列来使用
    int l = 0;
    int r = 0;
    for (int i = 0; i <= 127; i++) {
        if (tree[0][i] > 0) {
            box[r++] = tree[0][i];
            //0节点中只有有孩子的节点加入队列中
            //这个队列里面存储过的所有节点都要有fail
        }
    }
    while (l < r) {
        int u = box[l++];
        for (int i = 0; i <= 127; i++) {
            if (tree[u][i] == 0) {
                tree[u][i] = tree[fail[u]][i];
            } else {
                fail[tree[u][i]] = tree[fail[u]][i];//设置这个孩子节点的fail指针   直通表辅助不用绕环
                box[r++] = tree[u][i];//表示有这条支路  加入到队列中
            }
        }
    }
}
//完成直通表  和  fail表

void addEdge(int u, int v) {
    Next[++edge] = head[u];
    head[u] = edge;
    to[edge] = v;
}

void f1(int u) {
    for (int i = head[u]; i > 0; i = Next[i]) {
        f1(to[i]);
        times[u] += times[to[i]];
    }
}

int main()
{
//    cout<<('a'-'A')<<endl;
//    cout<<('A'-'A')<<endl;
    cout<<"请输入关键词数量：";
    cin>>n;
    for(int i=1;i<=n;i++){
        cout<<"请输入第 "<<i<<" 个关键词：";
        cin>>str[i];
        insert(i,str[i]);
    }
    setFail();
    char ch;

    std::cout << "Enter text: ";

    // 使用getchar()逐个字符读入，直到遇到ESC字符
    while (std::cin.get(ch)) {
//        if (ch == '0') { // 检查是否是ESC字符（ASCII码27）
//            break;
//        }
        s += ch; // 将字符添加到输入字符串中
    }

    int u=0;
    for (char ch:s) {
        u = tree[u][ch - '0'];//表示到达下一个节点
        // 增加匹配次数
        times[u]++;
    }
    for (int i = 1; i <= cnt; i++) {
        // 根据fail指针建反图
        // 其实是一颗树
        addEdge(fail[i], i);
    }
    // 遍历fail指针建的树
    // 汇总每个节点的词频
    f1(0);
    for(int i=1;i<=n;i++){
        cout<<"第 "<<i<<" 个关键词 "<<setw(5)<<str[i] <<" 出现了 "<<times[en[i]]<<" 次"<<endl;
    }
    return 0;
}
