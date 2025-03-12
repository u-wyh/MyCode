// 贴瓷砖的方法数(轮廓线dp)
// 给定两个参数n和m，表示n行m列的空白区域
// 有无限多的1*2规格的瓷砖，目标是严丝合缝的铺满所有的空白区域
// 返回有多少种铺满的方法
// 1 <= n, m <= 11
// 测试链接 : http://poj.org/problem?id=2411
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有用例
#include<iostream>
using namespace std;

long dp[11][11][1<<11];
int n, m;

// 辅助函数：获取状态s中第j位的状态
int get(int s, int j) {
    return (s >> j) & 1;
}

// 辅助函数：设置状态s中第j位的状态为v，并返回新的状态
int set(int s, int j, int v) {
    return v == 0 ? (s & (~(1 << j))) : (s | (1 << j));
}

long f(int i,int j,int s){
    if(i==n){
        return 1;
    }
    if(j==m){
        return f(i+1,0,s);
    }
    if(dp[i][j][s]!=-1){
        return dp[i][j][s];
    }
    long ans=0;
    if(get(s,j)==1){
        ans+=f(i,j+1,set(s,j,0));
    }
    else{
        if (i + 1 < n) { // 当前竖着摆砖
            ans = f(i, j + 1, set(s, j, 1));
        }
        if (j + 1 < m && get(s, j + 1) == 0) { // 当前横着摆砖
            ans += f(i, j + 2, s);
        }
    }
    dp[i][j][s]=ans;
    return ans;
}

int main()
{
    while(true){
        cin>>n>>m;
        if(n+m==0)
            break;
        for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				for (int s = 0; s < (1<<m); s++) {
					dp[i][j][s] = -1;
				}
			}
		}
		cout<<f(0, 0, 0)<<endl;
    }
    return 0;
}
