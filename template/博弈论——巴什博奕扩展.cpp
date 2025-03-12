// 质数次方版取石子(巴什博弈扩展)
// 一共有n颗石子，两个人轮流拿
// 每一轮当前选手可以拿 p的k次方 颗石子
// 当前选手可以随意决定p和k，但要保证p是质数、k是自然数
// 拿到最后一颗石子的人获胜
// 根据石子数返回谁赢
// 如果先手赢，返回"October wins!"
// 如果后手赢，输出"Roy wins!"
// 测试链接 : https://www.luogu.com.cn/problem/P4018
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        if(n%6==0){
            cout<<"Roy wins!\n";
        }
        else{
            cout<<"October wins!\n";
        }
    }
    return 0;
}
