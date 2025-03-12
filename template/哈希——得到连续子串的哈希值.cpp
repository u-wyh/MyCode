// �ַ�����ϣ�õ��Ӵ���ϣ
// �����ַ�����ϣ�ı��������KMP�㷨
// �������� : https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int base = 499;
int n,m;
char s1[MAXN];
char s2[MAXN];
vector<long>d(MAXN);
vector<long>Pow(MAXN);

// ���´������ַ�����ϣ��ԭ���ģ��
// ���磬base = 499, Ҳ���ǿ���˵��ѡ�����������
// �ٱ����ַ���s����
// " c a b e f "
//   0 1 2 3 4
// hash[0] = 3 * base��0�η�
// hash[1] = 3 * base��1�η� + 1 * base��0�η�
// hash[2] = 3 * base��2�η� + 1 * base��1�η� + 2 * base��0�η�
// hash[3] = 3 * base��3�η� + 1 * base��2�η� + 2 * base��1�η� + 5 * base��0�η�
// hash[4] = 3 * base��4�η� + 1 * base��3�η� + 2 * base��2�η� + 5 * base��1�η� + 6 *
// base��0�η�
// hash[i] = hash[i-1] * base + s[i] - 'a' + 1����������˵����˼
// ������Ӵ�"be"�Ĺ�ϣֵ -> 2 * base��1�η� + 5 * base��0�η�
// �Ӵ�"be"�Ĺ�ϣֵ = hash[3] - hash[1] * base��2�η�(�Ӵ�"be"�ĳ��ȴη�)
// hash[1] = 3 * base��1�η� + 1 * base��0�η�
// hash[1] * base��2�η� = 3 * base��3�η� + 1 * base��2�η�
// hash[3] = 3 * base��3�η� + 1 * base��2�η� + 2 * base��1�η� + 5 * base��0�η�
// hash[3] - hash[1] * base��2�η� = 2 * base��1�η� + 5 * base��0�η�
// �����͵õ��Ӵ�"be"�Ĺ�ϣֵ��
// �Ӵ�s[l...r]�Ĺ�ϣֵ = hash[r] - hash[l-1] * base��(r-l+1)�η�����������˵����˼
void build(){
    Pow[0]=1;
    for(int i=1;i<n;i++){
        Pow[i]=Pow[i-1]*base;
    }
    d[0]=s1[0]-'a'+1;
    for(int i=1;i<n;i++){
        d[i]=d[i-1]*base+s1[i]-'a'+1;
    }
}

long long zi(int l,int r){
    long long ans=d[r];
    if(l>0)
        ans-=d[l-1]*Pow[r-l+1];
    return ans;
}

int main()
{
    cin>>s1;
    cin>>s2;
    n=strlen(s1);
    m=strlen(s2);
    printf("%d %d\n",n,m);
    build();
    long h2 = s2[0] - 'a' + 1;
    for (int i = 1; i < m; i++) {
        h2 = h2 * base + s2[i] - 'a' + 1;
    }
    for (int l = 0, r = m - 1; r < n; l++, r++) {
        if (zi(l, r) == h2) {
            cout<<l;
            return 0;
        }
    }
    cout<<-1;
    return 0;
}
