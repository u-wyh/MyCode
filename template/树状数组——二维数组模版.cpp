// 二维数组上范围增加、范围查询，使用树状数组的模版(java)
// 测试链接 : https://www.luogu.com.cn/problem/P4514
// 如下实现是正确的，但是洛谷平台对空间卡的很严，只有使用C++能全部通过
// java的版本就是无法完全通过的，空间会超过限制，主要是IO空间占用大
// 这是洛谷平台没有照顾各种语言的实现所导致的
// 在真正笔试、比赛时，一定是兼顾各种语言的，该实现是一定正确的
// C++版本就是Code05_TwoDimensionIntervalAddIntervalQuery2文件
// C++版本和java版本逻辑完全一样，但只有C++版本可以通过所有测试用例
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2050;
const int MAXM = 2050;
int info1[MAXN][MAXM], info2[MAXN][MAXM], info3[MAXN][MAXM], info4[MAXN][MAXM];
// 维护信息 :  d[i][j]   d[i][j]*i    d[i][j]*j    d[i][j]*i*j
int n, m;

int lowbit(int x){
    return x&-x;
}

void add(int x,int y,int v){
    int v1=v;
    int v2=v*x;
    int v3=v*y;
    int v4=v*x*y;
    //对于每一个树状数组  每一次的增加值都是一样的

    for(int i=x;i<=n;i+=lowbit(i)){
        //行数增加 只要不超过限制
        for(int j=y;j<=m;j+=lowbit(j)){
            //列数增加 只要不超过限制
            info1[i][j]+=v1;
            info2[i][j]+=v2;
            info3[i][j]+=v3;
            info4[i][j]+=v4;
        }
    }
}
//这个函数的作用是将所有树状数组的值加上一个值

int sum(int x,int y){
    int ans=0;
    for(int i=x;i>0;i-=lowbit(i)){
        for(int j=y;j>0;j-=lowbit(j)){
            ans+=(x + 1) * (y + 1) * info1[i][j] - (y + 1) * info2[i][j] - (x + 1) * info3[i][j] + info4[i][j];
        }
    }
    return ans;
}
//这个函数的作用是计算从(1,1)到(x,y)的累加和
//上面的计算方式是推导出来的结果

void add(int a, int b, int c, int d, int v) {
    add(a, b, v);
    add(a, d + 1, -v);
    add(c + 1, b, -v);
    add(c + 1, d + 1, v);
}
//这个函数的作用是将一个矩形全部加上一个值
//但是我们维护的是差分数组  二维差分   从而只需要将四个位置改一下就行了

int range(int a, int b, int c, int d) {
	return sum(c, d) - sum(a - 1, d) - sum(c, b - 1) + sum(a - 1, b - 1);
}

int main()
{
    char op;
    cin>>op>>n>>m;
    int a,b,c,d,v;
    while(scanf("%c",&op)==1){
        if(op=='L'){
            cin>>a>>b>>c>>d>>v;
            add(a,b,c,d,v);
        }else if(op=='k'){
            cin>>a>>b>>c>>d;
            cout<<range(a,b,c,d)<<endl;
        }
    }
    return 0;
}
