// 杨辉三角
// 给定数字n，打印杨辉三角的前n行
// 1 <= n <= 20
// 测试链接 : https://www.luogu.com.cn/problem/P5732
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;

long long tri[20][20];

int main()
{
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        tri[i][0]=1;
        tri[i][i]=1;
    }
    for(int i=1;i<n;i++){
        for(int j=1;j<i;j++){
            tri[i][j]=tri[i-1][j]+tri[i-1][j-1];
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<=i;j++){
            cout<<tri[i][j]<<' ';
        }
        cout<<endl;
    }
    return 0;
}
