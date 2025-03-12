//最短相同前后缀
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
char a[1000010];
int n,fail[1000010];
int main(){
    scanf("%d",&n);
    scanf("%s",a);
    int i,j;
    ll cnt=0;
    fail[0]=fail[1]=0;
    j=0;
    for(i=1;i<n;i++){//求解next
        while(j&&(a[i]!=a[j]))
            j=fail[j];//不匹配就继续跳
        j+=(a[i]==a[j]);//判断是否可以加1  还是已经到了最原始的头
        fail[i+1]=j;
    }
    for(i=1;i<=n;i++){
        j=i;
        while(fail[j])
            j=fail[j];
        if(fail[i]!=0)
            fail[i]=j;//记忆化
        cnt+=i-j;
    }
    printf("%lld",cnt);
    return 0;
}
