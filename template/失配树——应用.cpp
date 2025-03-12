//P2375
#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;
const int MAXN = 1e6+5;
const int LIMIT = 20;

char s1[MAXN];
char s2[MAXN];
int Next[MAXN];
int n;
int num[MAXN];//表示前i-1个字符中 前后缀匹配的方案有多少  包含全选

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cnt=1;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}


// 计算next数组
void nextArray(const char *s, int m) {
    if (m == 1) {
        Next[0] = -1;
        return ;
    }

    Next[0] = -1;
    Next[1] = 0;
    int i = 2, cn = 0;
    // i表示当前要求next值的位置
    // cn表示当前要和前一个字符比对的下标
    while (i < m) {
        if (s[i - 1] == s[cn]) {
            Next[i] = ++cn;
            num[i++] = 1+num[cn];
        } else if (cn > 0) {
            cn = Next[cn];
        } else {
            Next[i++] = 0;
        }
    }
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        memset(num,0,sizeof(num));
        scanf("%s",s1+1);//从1开始读入更方便
        n=strlen(s1+1);
        nextArray(s1+1,n+1);
        for(int i=1;i<=n;i++){
            num[i]++;//这个加的是它本身整体
            //cout<<num[i]<<' '<<Next[i]<<endl;
        }
        int j=0;
        long long ans=1;
        for(int i=2;i<=n;i++){//求解num
            while(j&&(s1[i]!=s1[j+1]))//如果没有匹配上 那么就跳转
                j=Next[j];
            j+=(s1[i]==s1[j+1]);//匹配上 就往后移动一位
            while((j<<1)>i)
                j=Next[j];
            ans=(ans*(num[j]+1))%MOD;//记得+1
        }
        cout<<ans<<endl;
    }
    return 0;
}
