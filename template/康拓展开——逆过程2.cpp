// 逆康托展开   二分加树状数组
// 数字从1到n，可以有很多排列，给定一个长度为n的数组s，表示具体的一个排列
// 求出这个排列的排名假设为x，打印第x+m名的排列是什么
// 1 <= n <= 10^5
// 1 <= m <= 10^15
// 题目保证s是一个由1~n数字组成的正确排列，题目保证x+m不会超过排列的总数
// 测试链接 : https://www.luogu.com.cn/problem/U72177
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

long long arr[MAXN],tmp[MAXN];
int tree[MAXN];
int n;
long long m;

//以下部分是树状数组用于求和
int lowbit(int x){
    return x & -x;
}

void add(int i,int v){
    while(i<=n){
        tree[i]+=v;
        i+=lowbit(i);
        //每一次都加上自己最右侧的1
        //相当于把所有包含该状态的数字都增加
    }
}

int sum(int i){
    int ans=0;
    while(i>0){
        ans+=tree[i];
        i-=lowbit(i);
        //每一次都减去自己最右侧的1
        //相当于将整个区间拆分开为几个小区间加速  和乘法快速幂相似
    }
    return ans;
}
//这个函数求的是从1到i所有数字的和

//通过二分法得到答案
int solve(int x){
    int l=1,r=n,ans;
    while(l<=r){
        int mid=(l+r)>>1;
        if(sum(mid)>=x){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    add(ans,-1);
    return ans;
}

void compute(){
    //初始化树状数组
    for(int i=1;i<=n;i++){
        add(i,1);
    }
    // 当前排列转化为阶乘进制的排名
    for (int i = 1, x; i <= n; i++) {
        x = (int) arr[i];
        if (x == 1) {
            arr[i] = 0;
        } else {
            arr[i] = sum(x - 1);
        }
        //arr数组表示一开始的排列在阶乘进制下的排名
        add(x, -1);
        //消除这个数字的影响
    }
    // 当前排名加上m之后，得到新的排名，用阶乘进制表示
    arr[n] += m; // 最低位获得增加的幅度
    for (int i = n; i >= 1; i--) {
        // 往上进位多少
        arr[i - 1] += arr[i] / (n - i + 1);
        // 当前位是多少
        arr[i] %= n - i + 1;
    }
    //到这里时  arr数组里面是加上m后的排名在阶乘进制下的表示
    // 根据阶乘进制转化为具体的排列
    for(int i=1;i<=n;i++){
        add(tmp[i],1);
    }
    //将树状数组重新复原
    for (int i = 1; i <= n; i++) {
        arr[i] = solve((int) arr[i] + 1);
        //此时这个arr数组用来存放排列
    }
}

int main()
{
    cin>>n>>m;
    for (int i = 1; i <= n; i++) {
        cin>>arr[i];
        tmp[i]=arr[i];
    }
    compute();
    for (int i = 1; i <= n; i++) {
        cout<<arr[i] <<" ";
    }
    return 0;
}
