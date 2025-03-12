#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
using namespace std;

// 所有目标字符串的数量
const int MAXN = 1001;
// 所有目标字符串的总字符数量
const int MAXS = 10001;

// 记录每个目标串的结尾节点编号
int en[MAXN];
// 关键词报警功能
bool alert[MAXS];

// AC自动机部分
int tree[MAXS][270];//这里准备270条道路  用于准备所有的ASCII字符
int fail[MAXS];//设立fail指针
int cnt = 0;

// 所以每个节点记录词频
int times[MAXS];
// 可以用作队列或者栈，一个容器而已   不使用stl模板
int box[MAXS];

// 链式前向星，为了建立fail指针的反图
int head[MAXS];
int Next[MAXS];
int to[MAXS];
int edge = 0;

string s;
int path;
int n;
string str[MAXN];

void insert(int i, string word) {
    //i是目标串的编号
    int cur = 0;//头结点设置为0
    for (char ch : word) {
        if (ch >= 'A' && ch <= 'Z') {
            ch += 32;
        }
        path = ch - ' ';
        if (tree[cur][path] == 0) {
            tree[cur][path] = ++cnt;
            //没有路就要新建一条路  并赋予编号
        }
        cur = tree[cur][path];
    }
    en[i] = cur;
    alert[cur] = true;
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
            }
            else {
                fail[tree[u][i]] = tree[fail[u]][i];//设置这个孩子节点的fail指针   直通表辅助不用绕环
                box[r++] = tree[u][i];//表示有这条支路  加入到队列中
            }
        }
        alert[u] |= alert[fail[u]];
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

//全部清空  供下次使用
void clean() {
    cnt = 0;
    for (int i = 0; i < MAXS; i++) {
        head[i] = Next[i] = to[i] = 0;
        fail[i] = 0;
        times[i] = 0;
        alert[i] = false;
        for (int j = 0; j < 270; j++) {
            tree[i][j] = 0;
        }
    }
}

int main()
{
    //读入文本
    ifstream inputFile("C:\\Users\\wuyuh\\Desktop\\词频检测\\词频检测.txt");
    if (!inputFile.is_open()) {
        cerr << "无法打开文件。" << endl;
        return 1;
    }
    cout << "文章读入成功！" << endl;
    string line;
    while (getline(inputFile, line)) {
        s += line + "\n"; // 假设要保留换行符，否则可以移除 "\n"
        //s += line;
    }
    inputFile.close();

    //这一部分是将所有的大写字母改成小写  也可以不要这一部分
    int len = s.length();
    for (int i = 0; i < len; i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] += 32;
        }
    }

    cout <<endl<< "词频检测功能展示：" << endl;
    cout << "请输入关键词数量（输入0退出）：";
    cin >> n;
    while (n != 0) {
        getchar();//消除换行符
        for (int i = 1; i <= n; i++) {
            cout << "请输入第 " << i << " 个关键词：";
            getline(cin, str[i]);
            insert(i, str[i]);
        }
        setFail();

        int u = 0;
        for (char ch : s) {
            u = tree[u][ch - ' '];//表示到达下一个节点
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
        for (int i = 1; i <= n; i++) {
            cout << "第 " << setw(3) << i << " 个关键词 " << setw(7) << str[i] << " 出现了 " << times[en[i]] << " 次" << endl;
        }
        clean();
        cout << "请输入关键词数量（输入0退出）：";
        cin >> n;
    }

    cout << endl << "关键词警报功能展示：" << endl;
    cout << "请输入关键词数量（输入0退出）：";
    cin >> n;
    while (n != 0) {
        getchar();//消除换行符
        for (int i = 1; i <= n; i++) {
            cout << "请输入第 " << i << " 个关键词：";
            getline(cin, str[i]);
            insert(i, str[i]);
        }
        setFail();
        int u=0,k=0,flag=0;
        for (char ch : s) {
            if (alert[u]) {
                flag = 1;
                cout << "在第 " << k << " 个位置触发关键词！" << endl;
                break;
            }
            k++;
            u = tree[u][ch - ' '];//表示到达下一个节点
        }
        if(flag!=1)
            cout << "输入正常，未引发任何问题。" << endl;
        clean();
        cout << "请输入关键词数量（输入0退出）：";
        cin >> n;
    }
    return 0;
}
