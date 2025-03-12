//3423
//使用单调队列优化多重背包问题
#include<bits/stdc++.h>
using namespace std;
const int MAXM = 20005;
const int MAXN = 205;

int n,m;
int val[MAXN];
int num[MAXN];
int q[MAXN];

int f[MAXM];
int g[MAXM];

int d[MAXM][MAXN];
int d1[MAXM][MAXN];

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

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<=n;i++){
        num[i]=read();
    }
    m=read();
    for(int i=1;i<=m;i++){
        f[i]=500;
    }
    f[0]=0;
    for(int i=1;i<=n;i++){
        //枚举货币种类
        for(int j=0;j<=m;j++){
            g[j]=f[j];//每次f会变化  先拷贝一下
        }
        for(int j=1;j<=m;j++){
            for(int k=1;k<=n;k++){
                d1[j][k]=d[j][k];
            }
        }
        for(int j=0;j<val[i];j++){
            //拆分成val[i]个类  根据%val[i]余数分类
            int head=0,tail=0;
            for(int k=j;k<=m;k+=val[i]){//这个是下标  实际上是空间（背包问题中常见的模型）
                //对每个类进行单调队列
                while(head<tail&&q[head]<(k-num[i]*val[i])){
                    //由于每次最多移动一个位置  实际上最多每次只会移出一个 用if语句也可以
                    //(k-num[i]*val[i])  表示左边界 因为最多选num[i]个  每两个之间相差val[i]
                    //目前的要求的花费为k的时候  最多的价值
                    head++;
                }
                while(head<tail&&g[k]<=(g[q[tail-1]]+(k-q[tail-1])/val[i])){
                    //实际上是g[k]+(x-k)/v*w  <= g[q[tail-1]]+(x-q[tail-1])/v*w
                    //这里是简化了 并且x和k、q[tail-1]的差值一定可以约分v  因为这是一个类
                    //这里的代价是w=1
                    tail--;
                }
                q[tail++]=k;
                f[k]=min(g[k],g[q[head]]+(k-q[head])/val[i]);
                if(f[k]==g[q[head]]+(k-q[head])/val[i]){
                    for(int u=1;u<=i;u++){
                        d[k][u]=d1[q[head]][u];
                    }
                    d[k][i]+=(k-q[head])/val[i];
                }
            }
        }
//        cout<<i<<": ";
//        for(int j=0;j<=m;j++){
//            cout<<f[j]<<' ';
//        }
//        cout<<endl;
//        cout<<f[m]<<endl;
//        for(int j=1;j<=m;j++){
//            cout<<j<<": ";
//            for(int k=1;k<=n;k++){
//                cout<<d[j][k]<<' ';
//            }
//            cout<<endl;
//        }
    }
    cout<<f[m]<<endl;
    for(int i=1;i<=n;i++){
        cout<<d[m][i]<<' ';
    }
    return 0;
}
