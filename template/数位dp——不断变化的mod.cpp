//P2147
#include<bits/stdc++.h>
using namespace std;

long long l,r;
long long f[20][200][200];
int len;
int arr[20];
int mod;

long long dfs(int len,int sum,int st,bool limit){
    //表示还有len位没有填  目前总和是sum  目前已经填好的数字模mod的和是st
    //其实这个st基本没有什么作用 他只在最后判断是否可以模mod的时候用到
    //st是乘法同余的体现  比如34567%8中3可以看成是3*10*10*10*10%8
    //即 3%8 * 10%8 * 10%8 * 10%8 * 10%8
    if(sum+9*len<mod){
        //如果剩下的位置全部填9都无法满足 说明一定不行
        return 0;
    }
    if(!limit&&f[len][sum][st]!=-1){
        //在可以自由选择的情况下加上f
        //否则  会出现错误的答案被统计  即在填f的时候可以自由  而现在不能自由
        return f[len][sum][st];
    }
    if(len==0){
        //如果所有的位数都用完了  只有数位和是sum并且st%mod==0  才可以加一
        return sum==mod&&st==0;
    }
    int num=limit?arr[len]:9;
    long long ans=0;
    for(int i=0;i<=num&&i+sum<=mod;i++){
        ans+=dfs(len-1,sum+i,(st*10+i)%mod,limit&&(i==num));
    }
    if(!limit){
        //必须要在可以自由选择的情况下统计f
        //否则  如果接下来选的数字过大但是总的数位和是mod  也会被错误的加进答案中
        f[len][sum][st]=ans;
    }
    return ans;
}

long long compute(long long x){
    for(len=0;x;x/=10){
        arr[++len]=x%10;
        //首先将数字分解成数组
    }
    long long ans=0;
    for(mod=1;mod<=9*len;mod++){
        //既然是要求各个数位上的和  那么我们直接枚举各个数位上的和数值
        //即只求数位和是mod的数字个数
        memset(f,0xff,sizeof(f));
        ans+=dfs(len,0,0,1);
    }
    return ans;
}

int main()
{
    cin>>l>>r;
    cout<<(compute(r)-compute(l-1))<<endl;
    return 0;
}
