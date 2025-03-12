//P1169
//left[i][j]:代表从(i,j)(i,j)能到达的最左位置
//right[i][j]:代表从(i,j)(i,j)能到达的最右位置
//up[i][j]:代表从(i,j)(i,j)向上扩展最长长度.
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2005;

int n,m;
int nums[MAXN][MAXN];
int lef[MAXN][MAXN];
int righ[MAXN][MAXN];
int up[MAXN][MAXN];
int ans1=0,ans2=0;

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>nums[i][j];
            lef[i][j]=righ[i][j]=j;
            up[i][j]=1;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=2;j<=m;j++){
            if(nums[i][j]!=nums[i][j-1]){
                lef[i][j]=lef[i][j-1];
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=m;j>=2;j--){
            if(nums[i][j]!=nums[i][j-1]){
                righ[i][j-1]=righ[i][j];
            }
        }
    }
    for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
            if(i>1&&nums[i][j]!=nums[i-1][j]){
                lef[i][j]=max(lef[i][j],lef[i-1][j]);
                righ[i][j]=min(righ[i][j],righ[i-1][j]);//这样可以得到最长但是最窄的面积
                up[i][j]=up[i-1][j]+1;//竖向长度
            }
            int a=righ[i][j]-lef[i][j]+1;	//横向长度
            int b=min(a,up[i][j]);
            ans1=max(ans1,b*b);//正方形
            ans2=max(ans2,a*up[i][j]);//长方形
            //这里求的两个面积实际上都是以i、j作为右下点的最大面积
        }
    }
    cout<<ans1<<endl<<ans2<<endl;
    return 0;
}
