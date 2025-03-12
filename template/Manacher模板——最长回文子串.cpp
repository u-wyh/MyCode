// ������Ӵ�
// �ҵ��ַ���s����Ļ����Ӵ�������
// �������� : https://leetcode.cn/problems/longest-palindromic-substring/
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 11000001;

char ss[MAXN << 1];//��������м������#
char a[MAXN];//ԭʼ����
int p[MAXN << 1];//�뾶����
int n,maxans,maxend;

void manacherss() {
    n = strlen(a) * 2 + 1;
    for (int i = 0, j = 0; i < n; i++) {
        ss[i] = (i & 1) == 0 ? '#' : a[j++];
    }
}

void manacher() {
    manacherss();
    maxans = 0;
    for (int i = 0, c = 0, r = 0, len; i < n; i++) {//i�Ǵ�ʱ����������λ��
        len = r > i ? min(p[2 * c - i], r - i) : 1;//���ֵ�ǻ���ֵ  �����ס��  ��ô����ֵ��������ֵ  ��������ټ�
        while (i + len < n && i - len >= 0 && ss[i + len] == ss[i - len]) {
            len++;
            //�������ס��  ��ôֱ����������
        }
        //��ʱ�Ѿ��������iΪ���ĵĻ��İ뾶��С
        if (i + len > r) {
            r = i + len;
            c = i;
            //����������ұ߽�  ��ôc����i  r����i+len
        }
        if(len>maxans){
            maxans=len-1;//������ȱ���Ҫ��1
            maxend=(i+len-1)/2;//������Ӵ�ʵ�ʵĽ���λ��(���ܵ���)
        }
        p[i] = len;
        //�õ����İ뾶
    }
}

int main()
{
    scanf("%s",a);
    manacher();
    for(int i=maxend-maxans;i<maxend;i++){
        cout<<a[i];
    }
    return 0;
}
