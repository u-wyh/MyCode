// 异或关系
// 一共n个数，编号0 ~ n-1，实现如下三种类型的操作，一共调用m次
// I x v        : 声明 第x个数 = v
// I x y v      : 声明 第x个数 ^ 第y个数 = v
// Q k a1 .. ak : 查询 一共k个数，编号为a1 .. ak，这些数字异或起来的值是多少
// 对每个Q的操作打印答案，如果根据之前的声明无法推出答案，打印"I don't know."
// 如果处理到第s条声明，发现了矛盾，打印"The first s facts are conflicting."
// 注意只有声明操作出现，s才会增加，查询操作不占用声明操作的计数
// 发现矛盾之后，所有的操作都不再处理，更多的细节可以打开测试链接查看题目
// 1 <= n <= 20000    1 <= m <= 40000    1 <= k <= 15
// 测试链接 : https://acm.hdu.edu.cn/showproblem.php?pid=3234
// 测试链接 : https://www.luogu.com.cn/problem/UVA12232
// 测试链接 : https://vjudge.net/problem/UVA-12232
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<iostream>
using namespace std;
#define gc getchar
inline int read()
{
	int ret=0,f=0;char c=gc();
	while(!isdigit(c)){if(c=='-')f=1;c=gc();}
	while(isdigit(c)){ret=ret*10+c-48;c=gc();}
	if(f)return -ret;return ret;
}
const int N=20005;
int n,m,fa[N],val[N],vis[N];
struct query{
    char c;
    int a,b,v,k,x[20];
} q[N*2];
int find(int x)
{
    if(fa[x]==x)return x;
    int tmp=fa[x];
    fa[x]=find(fa[x]);
    val[x]^=val[tmp];
    return fa[x];
}
void init()//建一颗无用的点n，把值确定的点连向n
{
    for(int i=0;i<=n;i++)
	{
		fa[i]=i;
		val[i]=0;
    }
    char Q[105];
    for(int i=0;i<m;i++)
	{
		scanf("%s",Q);
		q[i].c=Q[0];
		int a,b,v;
		if(Q[0]=='I')
		{
		    gets(Q);
		    if(sscanf(Q,"%d%d%d",&a,&b,&v)==2)
			{
				v=b;
				b=n;
		    }
		    q[i].a=a;q[i].b=b;q[i].v=v;
		}
		else{
		    scanf("%d",&q[i].k);
		    for(int j=0;j<q[i].k;j++)scanf("%d",&q[i].x[j]);
		}
    }
}
void solve()
{
    int fir=0;
    for(int i=0;i<m;i++)
	{
		if(q[i].c=='I')
		{
		    fir++;
		    int x=find(q[i].a);
		    int y=find(q[i].b);
		    if(x==n)swap(x,y);
		    if(x==y)
			{
				if((val[q[i].a]^val[q[i].b])!=q[i].v)
				{
				    printf("The first %d facts are conflicting.\n",fir);
				    return;
				}
		    }
		    else{
				fa[x]=y;
				val[x]=val[q[i].a]^val[q[i].b]^q[i].v;//不知道x和y确切的值，所以要用其他方式求出x^y
		    }
		}
		else{
		    int ans=0;
		    for(int j=0;j<q[i].k;j++)
			{
				int x=find(q[i].x[j]);
				ans^=val[q[i].x[j]];
				if(x!=n)vis[x]^=1;//为1就表示多计算了一次fa的值
			}
			int flag=1;
			for(int j=0;j<q[i].k;j++)
			{
				if(vis[fa[q[i].x[j]]])flag=0;
				vis[fa[q[i].x[j]]]=0;
		    }
		    if(flag)printf("%d\n",ans);
		    else printf("I don't know.\n");
		}
    }
}
int main()
{
    int cas=0;
    while(scanf("%d%d",&n,&m)!=EOF)
	{
		if(n==0&&m==0)return 0;
		init();
		printf("Case %d:\n",++cas);
		solve();
		puts("");
    }
    return 0;
}
