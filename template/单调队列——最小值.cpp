#include<bits/stdc++.h>
using namespace std;

int n,k;
int a[100000],q[100000];

int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    int h=0,t=0;
    for(int i=1;i<=k-1;i++){
        while(h<t&&q[h]+k<=i){
            h++;
        }
        while(h<t&&a[q[t-1]]>a[i]){
            t--;
        }//h<t  保证了如果队列已经是空的  那么不在t--
        q[t]=i;
        t++;
    }//建立了一个容量为k的窗口
    for(int i=k;i<=n;i++){
        while(h<t&&q[h]+k<=i){
            h++;
        }
        while(h<t&&a[q[t-1]]>a[i]){
            t--;
        }//h<t  保证了如果队列已经是空的  那么不在t--
        q[t]=i;
        t++;
        cout<<a[q[h]]<<endl;
    }
    return 0;
}
//这里也可以先建立一个k-1的滑动窗口  然后在加入第k个数字  判断并输出最大值
