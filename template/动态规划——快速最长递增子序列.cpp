//P2215
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e4+5;

int n,m,k;
int arr[MAXN];
int dp[MAXN];//表示的是以当前元素作为起始  最长递增子序列长度
int en[MAXN];//ends[i]表示的是  长度为i  的递增子序列  开头  最大是多少
int len=0;//表示ends数组长度

void compute(){
    int u=1;
    while(dp[u]<k){
        u++;
    }
    int maxlen=k;
    int last=INT_MIN;
    for(int i=1;i<=k;i++){
        while(dp[u]<k-i+1||arr[u]<=last){
            u++;
        }
        cout<<arr[u]<<' ';
        last=arr[u];
        u++;
    }
    cout<<endl;
}

//找到第一个小于等于val的元素的下标
int bs(int val){
    int l=1,r=len,ans=-1;
    while(l<=r){
        int mid=(l+r)/2;
        if(en[mid]<=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    for(int i=n;i>=1;i--){
        int sub=bs(arr[i]);
        if(sub==-1){
            //说明暂时没有比他小的元素
            en[++len]=arr[i];//在数组末尾加入一个元素
            dp[i]=len;
        }
        else{
            en[sub]=arr[i];//将原来的元素替换
            dp[i]=sub;
        }
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>k;
        if(k>len){
            cout<<"Impossible"<<endl;
        }
        else{
            compute();
        }
    }
    return 0;
}

