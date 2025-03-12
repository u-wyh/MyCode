//p4667
#include<bits/stdc++.h>
using namespace std;
const int dx[4]={1,-1,-1,1}; //方向数组，别搞错了
const int dy[4]={1,1,-1,-1};
const char a[5]="\\/\\/";
const int ix[4]={0,-1,-1,0};
const int iy[4]={0,0,-1,-1};
deque <int> x;  //双端队列！
deque <int> y;
char map[505][505]; //存储地图
int vis [505][505]; //vis数组，记录最短步数
int l,c;  //l——line（行数），c——column（列数）

void bfs(){  //广搜函数
	memset(vis,0x3f,sizeof(vis)); //因为要求最小值，把vis数组初始化成0x3f（就是一个很大的数啦）
	x.push_back(0);  //起点（0，0）入队，步数是0
	y.push_back(0);
	vis[0][0]=0;
	while(!x.empty()){  //这一部分就是把广搜的板子啦
		int xx=x.front();  //先get到队首
		int yy=y.front();
		x.pop_front();  //一定要get完了之后先pop出去
		y.pop_front();
		for(int i=0;i<4;i++){  //4个方向一个一个试
			int dnx=xx+dx[i]; //dnx，dxy——点的横纵坐标
			int dny=yy+dy[i];
			int inx=xx+ix[i];//inx，iny——格子的横纵坐标
			int iny=yy+iy[i];
			if(dnx>=0&&dnx<=l&&dny>=0&&dny<=c){  //如果没出界的话就考虑入不入队
				if(a[i]!=map[inx][iny]){ //看看地图的电线状态和往这个方向走的电线状态是否一致
					int t=vis[xx][yy]+1;  //不一致就要转向，步数+1
					if(t<vis[dnx][dny]){ //如果比原来的步数小，就入队，标记
						x.push_back(dnx); //转向肯定不如不转向好，所以要后搜，从队尾入队
						y.push_back(dny);
						vis[dnx][dny]=t;
					}
				}
				else{//要不就不用转向
					int t=vis[xx][yy]; //不用转向，步数不用变;
					if(t<vis[dnx][dny]){ //步数比原来的小才能入队
						x.push_front(dnx); //不用转向肯定更好，要先搜，从队首入队
						y.push_front(dny);
						vis[dnx][dny]=t;
					}
				}
			}
		}
	}
	cout<<vis[l][c]<<endl; //输出最后的步数
}

int main(){
		cin>>l>>c; //输入
		for(int i=0;i<l;i++)
			cin>>map[i];
		if((l+c)%2) //如果终点横纵坐标和是奇数
		cout<<"NO SOLUTION\n";//那就铁定无解
		else bfs(); //不无解那就广搜
	return 0;
}
