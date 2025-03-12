#include<bits/stdc++.h>
using namespace std;

int t,m=31;

void show(int t,int m){
    //展示一个数的二进制各个数位上的数字
    //如果目前的数字大于(1<<p)  说明当前位上是1  那么减去这个数字
    //否则是0
    //m的含义是这个数字最多不超过2的m次方
    int n=t;
    for(int p=m-1;p>=0;p--){
        if(t>=(1<<p)){
            printf("%d 的第%02d位是 1\n",n,p);
            t-=(1<<p);
        }else
            printf("%d 的第%02d位是 0\n",n,p);
    }
}

int show1(int t){
    int p=0;
    while((1<<p)<=t){
        p++;
    }
    return p-1;
}

int show2(int t){
    int p=0;
    while((1<<p)<=(t>>1)){
        p++;
    }
    return p;
}
//show1  show2  这两个函数都是实现输出不超过数字t的最大2的次方
//区别就是show2更加的安全   不用担心溢出问题
//比如：20000000000  此时show1无法输出  死循环了

int main()
{
    cin>>t;
    show(t,m);
    cout<<show2(t)<<endl;
    cout<<show1(t)<<endl;
    return 0;
}
