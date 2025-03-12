// 贴瓷砖的方法数(轮廓线dp+空间压缩)
// 给定两个参数n和m，表示n行m列的空白区域
// 有无限多的1*2规格的瓷砖，目标是严丝合缝的铺满所有的空白区域
// 返回有多少种铺满的方法
// 1 <= n, m <= 11
// 测试链接 : http://poj.org/problem?id=2411
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有用例
#include<iostream>
using namespace std;

long dp[12][1<<11];
long prepare[1<<11];
int n, m;

// 辅助函数：获取状态s中第j位的状态
int get(int s, int j) {
    return (s >> j) & 1;
}

// 辅助函数：设置状态s中第j位的状态为v，并返回新的状态
int set(int s, int j, int v) {
    return v == 0 ? (s & (~(1 << j))) : (s | (1 << j));
}

int main()
{
    while(true){
        cin>>n>>m;
        if(n+m==0)
            break;
        for(int i=0;i<(1<<n);i++){
            prepare[i]=1;
        }
        for(int i=n-1;i>=0;i--){
            for(int j=0;j<(1<<m);j++){
                //此时填的是第m列  也就是加出来的那一列
                dp[m][j]=prepare[j];
            }

            for(int j=m-1;j>=0;j--){
                for(int s=0;s<(1<<m);s++){
                    long ans=0;
                    if(get(s,j)==1){
                        ans+=dp[j+1][set(s,j,0)];
                    }
                    else{
                        if (i + 1 < n) { // 当前竖着摆砖
                            ans = dp[j + 1][set(s, j, 1)];
                        }
                        if (j + 1 < m && get(s, j + 1) == 0) { // 当前横着摆砖
                            ans += dp[j + 2][ s];
                        }
                    }
                    dp[j][s]=ans;
                }
            }

            for(int j=0;j<(1<<m);j++){
                prepare[j]=dp[0][j];
                //这张表的第一列也是下一张表的最后一列
            }
        }
        cout<<dp[0][0]<<endl;
    }
    return 0;
}
