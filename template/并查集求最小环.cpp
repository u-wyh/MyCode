//P2661
#include<cstdio>
#include<algorithm>//用到min
using namespace std;
const int MAXN=200010;
int a[MAXN],fa[MAXN],dis[MAXN];//含义见上
int ans=0x3f3f3f3f;//浅坑1
int read(){//快读，这里就不给注释了
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
int getfa(int u){//找祖先
	if(fa[u]==u) return u;//不用找，直接返回
	int tmp=fa[u];//深坑，解释见上
	fa[u]=getfa(fa[u]);//浅坑2
	dis[u]+=dis[tmp];
	return fa[u];//返回
}
void unio(int u,int v){//合并
	int fu=getfa(u),fv=getfa(v);//先找祖先
	if(fu==fv) ans=min(ans,dis[v]+1);//更新答案，解释见上
	else fa[fu]=fv,dis[u]=dis[v]+1;//更新fa和dis，浅坑3
}
int main(){//主函数
	int n=read();
	for(int i=1;i<=n;i++) fa[i]=i;//浅坑4
	for(int i=1;i<=n;i++){
		a[i]=read();
		unio(i,a[i]);//合并，浅坑5
	}
	printf("%d",ans);//输出
	return 0;//华丽结束
}
/*
在找祖先（getfagetfa）这个函数里，不仅要更新祖先节点，还要更新距离。这里有一个比较巧妙的方法：
由于真正的祖先节点是目前的祖先节点的祖先节点，
所以这个点到真正祖先节点的距离就是它到目前的祖先节点的距离加上目前的祖先节点到真正祖先节点的距离。（比较绕）

还有一个合并的函数（unionunion这个名字被用过了，所以我这里叫uniounio）。
对于输入第二行的每个数，都需要与当时的ii做一次合并操作。先找到需要合并的两个节点的祖先。

如果祖先相同，那么出现环，此环的长度就是dis[v]+1dis[v]+1。如果不好理解，那么看下面的图：

其中正在处理u=4,v=1u=4,v=1的合并，可以得到fa[1]=4,dis[1]=3,fa[4]=4,dis[4]=0fa[1]=4,dis[1]=3,fa[4]=4,dis[4]=0。
不难发现，dis[u]永远是0，所以答案就是dis[v]dis[v]加上<4,1><4,1>这条边的11。

如果祖先不相同，那么就按照并查集的正常做法，再加上一句dis[u]=dis[v]+1dis[u]=dis[v]+1就好了。
*/
