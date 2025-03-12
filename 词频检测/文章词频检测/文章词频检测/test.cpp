#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
using namespace std;

// ����Ŀ���ַ���������
const int MAXN = 1001;
// ����Ŀ���ַ��������ַ�����
const int MAXS = 10001;

// ��¼ÿ��Ŀ�괮�Ľ�β�ڵ���
int en[MAXN];
// �ؼ��ʱ�������
bool alert[MAXS];

// AC�Զ�������
int tree[MAXS][270];//����׼��270����·  ����׼�����е�ASCII�ַ�
int fail[MAXS];//����failָ��
int cnt = 0;

// ����ÿ���ڵ��¼��Ƶ
int times[MAXS];
// �����������л���ջ��һ����������   ��ʹ��stlģ��
int box[MAXS];

// ��ʽǰ���ǣ�Ϊ�˽���failָ��ķ�ͼ
int head[MAXS];
int Next[MAXS];
int to[MAXS];
int edge = 0;

string s;
int path;
int n;
string str[MAXN];

void insert(int i, string word) {
    //i��Ŀ�괮�ı��
    int cur = 0;//ͷ�������Ϊ0
    for (char ch : word) {
        if (ch >= 'A' && ch <= 'Z') {
            ch += 32;
        }
        path = ch - ' ';
        if (tree[cur][path] == 0) {
            tree[cur][path] = ++cnt;
            //û��·��Ҫ�½�һ��·  ��������
        }
        cur = tree[cur][path];
    }
    en[i] = cur;
    alert[cur] = true;
}

// ��������Ŀ���ַ���֮��
// ����failָ�� �Լ� ����ֱ��ֱͨ��
// ����AC�Զ����̶����Ż�
void setFail() {
    // box����������ʹ��
    int l = 0;
    int r = 0;
    for (int i = 0; i <= 127; i++) {
        if (tree[0][i] > 0) {
            box[r++] = tree[0][i];
            //0�ڵ���ֻ���к��ӵĽڵ���������
            //�����������洢�������нڵ㶼Ҫ��fail
        }
    }
    while (l < r) {
        int u = box[l++];
        for (int i = 0; i <= 127; i++) {
            if (tree[u][i] == 0) {
                tree[u][i] = tree[fail[u]][i];
            }
            else {
                fail[tree[u][i]] = tree[fail[u]][i];//����������ӽڵ��failָ��   ֱͨ���������ƻ�
                box[r++] = tree[u][i];//��ʾ������֧·  ���뵽������
            }
        }
        alert[u] |= alert[fail[u]];
    }
}
//���ֱͨ��  ��  fail��

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

//ȫ�����  ���´�ʹ��
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
    //�����ı�
    ifstream inputFile("C:\\Users\\wuyuh\\Desktop\\��Ƶ���\\��Ƶ���.txt");
    if (!inputFile.is_open()) {
        cerr << "�޷����ļ���" << endl;
        return 1;
    }
    cout << "���¶���ɹ���" << endl;
    string line;
    while (getline(inputFile, line)) {
        s += line + "\n"; // ����Ҫ�������з�����������Ƴ� "\n"
        //s += line;
    }
    inputFile.close();

    //��һ�����ǽ����еĴ�д��ĸ�ĳ�Сд  Ҳ���Բ�Ҫ��һ����
    int len = s.length();
    for (int i = 0; i < len; i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] += 32;
        }
    }

    cout <<endl<< "��Ƶ��⹦��չʾ��" << endl;
    cout << "������ؼ�������������0�˳�����";
    cin >> n;
    while (n != 0) {
        getchar();//�������з�
        for (int i = 1; i <= n; i++) {
            cout << "������� " << i << " ���ؼ��ʣ�";
            getline(cin, str[i]);
            insert(i, str[i]);
        }
        setFail();

        int u = 0;
        for (char ch : s) {
            u = tree[u][ch - ' '];//��ʾ������һ���ڵ�
            // ����ƥ�����
            times[u]++;
        }
        for (int i = 1; i <= cnt; i++) {
            // ����failָ�뽨��ͼ
            // ��ʵ��һ����
            addEdge(fail[i], i);
        }
        // ����failָ�뽨����
        // ����ÿ���ڵ�Ĵ�Ƶ
        f1(0);
        for (int i = 1; i <= n; i++) {
            cout << "�� " << setw(3) << i << " ���ؼ��� " << setw(7) << str[i] << " ������ " << times[en[i]] << " ��" << endl;
        }
        clean();
        cout << "������ؼ�������������0�˳�����";
        cin >> n;
    }

    cout << endl << "�ؼ��ʾ�������չʾ��" << endl;
    cout << "������ؼ�������������0�˳�����";
    cin >> n;
    while (n != 0) {
        getchar();//�������з�
        for (int i = 1; i <= n; i++) {
            cout << "������� " << i << " ���ؼ��ʣ�";
            getline(cin, str[i]);
            insert(i, str[i]);
        }
        setFail();
        int u=0,k=0,flag=0;
        for (char ch : s) {
            if (alert[u]) {
                flag = 1;
                cout << "�ڵ� " << k << " ��λ�ô����ؼ��ʣ�" << endl;
                break;
            }
            k++;
            u = tree[u][ch - ' '];//��ʾ������һ���ڵ�
        }
        if(flag!=1)
            cout << "����������δ�����κ����⡣" << endl;
        clean();
        cout << "������ؼ�������������0�˳�����";
        cin >> n;
    }
    return 0;
}
