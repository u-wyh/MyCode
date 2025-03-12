// 长度前k名的奇数长度回文子串长度乘积
// 给定一个字符串s和数值k，只关心所有奇数长度的回文子串
// 返回其中长度前k名的回文子串的长度乘积是多少
// 如果奇数长度的回文子串个数不够k个，返回-1
// 测试链接 : https://www.luogu.com.cn/problem/P1659
// 答案对19930726取模
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过
#include<bits/stdc++.h>
using namespace std;
const int MOD = 19930726;
const int MAXN = 10000005;

int n,m;
long k;
char ss[MAXN << 1];//这个数组中间添加了#
char a[MAXN];//原始数组
int p[MAXN << 1];//半径数组
int cnt[MAXN];

void manacherss() {
    n = m * 2 + 1;
    for (int i = 0, j = 0; i < n; i++) {
        ss[i] = (i & 1) == 0 ? '#' : a[j++];
    }
}

int manacher() {
    manacherss();
    int maxans = 0;
    for (int i = 0, c = 0, r = 0, len; i < n; i++) {//i是此时来到的中心位置
        len = r > i ? min(p[2 * c - i], r - i) : 1;//这个值是基本值  如果包住了  那么基本值就是最终值  否则后续再加
        while (i + len < n && i - len >= 0 && ss[i + len] == ss[i - len]) {
            len++;
            //如果被包住了  那么直接跳出来了
        }
        //此时已经求出了以i为中心的回文半径大小
        if (i + len > r) {
            r = i + len;
            c = i;
            //如果更新了右边界  那么c就是i  r就是i+len
        }
        maxans = max(maxans, len);
        p[i] = len;
        //得到回文半径
    }
    return maxans - 1;
}

long power(long x, long n) {
    long ans = 1;
    while (n > 0) {
        if ((n & 1) == 1) {
            ans = (ans * x) % MOD;
        }
        x = (x * x) % MOD;
        n >>= 1;
    }
    return ans;
}//快速幂

int main()
{
    cin>>m>>k;
    scanf("%s",a);
    manacher();
    for(int i=1;i<n;i+=2){
        cnt[p[i]-1]++;
        //统计出字符串长度
    }
    long ans=1;
    long sum=0;
    for(int len=(m&1)==1?m:(m-1);len>=0&&k>=0;len-=2){
        sum+=cnt[len];
        ans=(ans*(long)power(len,min((long)k,sum)))%MOD;
        k-=sum;
    }
    if(k>=0){
        ans=-1;
    }
    cout<<ans;
    return 0;
}
