//P8112
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e7+5;

// b与b每一个后缀串的最长公共前缀长度，z数组
// b与a每一个后缀串的最长公共前缀长度，e数组
int z[MAXN];
int e[MAXN];
char a[MAXN];
char b[MAXN];
int n,m;

int q[MAXN];
int f[MAXN];
//从后往前  至少要跳几次才能到达最后  而且越往后一定越小  这是因为我们被对答案没有贡献的部分全部去除了

void zArray(char* s, int n) {
    z[0] = n;
    for (int i = 1, c = 1, r = 1, len; i < n; i++) {
        len = r > i ? min(r - i, z[i - c]) : 0;
        while (i + len < n && s[i + len] == s[len]) {
            len++;
        }
        if (i + len > r) {
            r = i + len;
            c = i;
        }
        z[i] = len;
    }
}

void eArray(char* a, char* b, int n, int m) {
    for (int i = 0, c = 0, r = 0, len; i < n; i++) {
        len = r > i ? min(r - i, z[i - c]) : 0;
        while (i + len < n && len < m && a[i + len] == b[len]) {
            len++;
        }
        if (i + len > r) {
            r = i + len;
            c = i;
        }
        e[i] = len;
    }
}
//如果说有参数的话直接就是模版

int main()
{
    cin>>m>>n;
    scanf("%s",b);
    scanf("%s",a);
    zArray(b,m);
    eArray(a,b,n,m);
    for(int i=0;i<=n;i++){
        f[i]=1e9;
    }
    for(int i=0,r=-1;i<n;i++){
        r>i+e[i]?e[i]=0:r=i+e[i];
        //这里的意思是 如果前面就已经可以转移到的后面并且当前点却无法转移到那之后
        //说明这个点对答案没有任何帮助  那么设置为0
        //如果这些点没有去除的话  那么优先队列进入时要有操作  判断
    }
    //那么此时所有的点 只要e[i]为0  对答案一定没有影响
    f[n]=0;
    int l=1,r=1;
    q[r++]=n;
    for(int i=(n-1);i>=0;i--){
        if(!e[i]){
            continue;
        }
        while(l<r&&q[l]>i+e[i]){
            //超出了界限范围
            l++;
        }
        f[i]=f[q[l]]+1;
        q[r++]=i;
    }
    if(f[0]<=1e9){
        cout<<f[0]<<endl;
    }
    else{
        cout<<"Fake"<<endl;
    }
    return 0;
}
