// 重复叠加字符串匹配
// 给定两个字符串a和b，寻找重复叠加字符串a的最小次数，使得字符串b成为叠加后的字符串a的子串
// 如果不存在则返回-1
// 字符串"abc"重复叠加0次是""
// 重复叠加1次是"abc"
// 重复叠加2次是"abcabc"
// 测试链接 : https://leetcode.cn/problems/repeated-string-match/
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 10005;
const int base = 499;
int n,m;
char s1[MAXN];
char s2[MAXN];
char s[30009];
vector<long>d(MAXN);
vector<long>Pow(MAXN);
int k=0;

long zi(int l,int r){
    long  ans=d[r];
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
    k=(m+n-1)/n;
    //printf("%d %d\n",n,m);
    int len=0;
    for(int i=0;i<=k;i++){
        for(int j=0;j<n;j++){
            s[len++]=s1[j];
        }
    }

    Pow[0]=1;
    for(int i=1;i<len;i++){
        Pow[i]=Pow[i-1]*base;
    }
    d[0]=s[0]-'a'+1;
    for(int i=1;i<len;i++){
        d[i]=d[i-1]*base+s[i]-'a'+1;
    }

    long h2 = s2[0] - 'a' + 1;
    for (int i = 1; i < m; i++) {
        h2 = h2 * base + s2[i] - 'a' + 1;
    }
    int l,r;
    for (l = 0, r = m - 1; r < n; l++, r++) {
        if (zi(l, r) == h2) {
            break;
        }
    }

    printf("%d\n",r<k*n?k:k+1);
    return 0;
}

