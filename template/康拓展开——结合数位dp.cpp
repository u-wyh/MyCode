//P2518
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 55;//最长不会超过50位

int n;
int arr[10];//各个数字的统计
int C[MAXN][MAXN];
int val[MAXN];//初始时该位置上的数字

int c(int a,int b){
    if(C[a][b]){
        return C[a][b];
    }
    int ans=1;
    for(int i=1;i<=min(b,a-b);i++){
        ans*=(a-i+1);
        ans/=i;
    }
    C[a][b]=ans;
    return ans;
}

int compute(){
    int m=n;//表示这m个位置可以随意填
    int ans=1;
    for(int i=0;i<=9;i++){
        if(arr[i]){
            ans*=c(m,arr[i]);
            m-=arr[i];//可以填的位置减少
        }
    }
    return ans;
}

signed main()
{
    char c;
    // 读取输入并统计每个数字的出现次数
    while (cin >> c) {
        if (isdigit(c)) {
            val[++n] = c - '0'; // 将字符转换为数字
            arr[val[n]]++; // 统计数字出现次数
        }
    }
    int ans=0;
    int len=n;//备份长度
    for(int i=1;i<=len;i++){
        n--;//表示剩余位置减少
        for(int j=0;j<val[i];j++){
            if(arr[j]){
                arr[j]--;//表示这位置填j  那么剩下的位置就可以自由选择了
                ans+=compute();
                arr[j]++;
            }
        }
        arr[val[i]]--;//表示和原来一样  即剩下的数据不能随便选
    }
    cout<<ans<<endl;
    return 0;
}
