//P3107
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 20;

int n,m;
int ans;

int f[MAXN][MAXN][MAXN][2][2];
int nums[MAXN];
int len;

int dfs1(int len,int k,int cnt1,int cnt2,bool flag1,bool flag2){
    //表示的信息是还有len位没有填  我们要统计的是数字k出现的次数
    //cnt1表示k出现的次数  cnt2表示的是前导零除外其余数字出现的次数
    //flag1表示是否可以自由选择  1表示不可以  0表示可以
    //flag2表示前面是否都是0  1表示是  0表示不是
    if(len==0){
        return cnt1>=cnt2;//所有的位置都已经填完了  比较是否满足
    }
    if(f[len][cnt1][cnt2][flag1][flag2]!=-1){
        return f[len][cnt1][cnt2][flag1][flag2];
    }
    int ans=0;
    for(int i=0;i<=9;i++){
        //枚举这一位置上要填的数字
        if(i<=nums[len]||flag1==0){
            //要么是小于原来的数字 要么是可以自由填
            ans+=dfs1(len-1,k,cnt1+(i==k)*(flag2==0||i!=0),cnt2+(i!=k)*(flag2==0||i!=0),flag1&&i==nums[len],i==0&&flag2);
            //(flag2==0||i!=0)表示的是已经不再是前导的范围了
            //flag1&&i==nums[len]  表示如果以前也不自由并且现在等于nums[len]  那么不自由  否则就是0 自由
            //i==0&&flag2  如果以前都是前导并且现在是0  那么就是前导
        }
    }
    f[len][cnt1][cnt2][flag1][flag2]=ans;
    return ans;
}

int calc1(int x,int k){
    //表示计算小于x的数字中  数字k出现次数大于总体一半的数字个数
    memset(f,-1,sizeof(f));
    for(len=0;x;x/=10){
        nums[++len]=x%10;
    }
    return dfs1(len,k,0,0,1,1);
}

int dfs2(int len,int k1,int k2,int cnt1,int cnt2,bool flag1,bool flag2){
    if(len==0){
        return cnt1==cnt2;//所有的位置都已经填完了  比较是否满足
    }
    if(f[len][cnt1][cnt2][flag1][flag2]!=-1){
        return f[len][cnt1][cnt2][flag1][flag2];
    }
    int ans=0;
    if(k1<=nums[len]||flag1==0){
        //要么可以自由选择 要么k1满足要求
        ans+=dfs2(len-1,k1,k2,cnt1+(k1!=0||flag2==0),cnt2,k1==nums[len]&&flag1,k1==0&&flag2);
    }
    if(k2<=nums[len]||flag1==0){
        //要么可以自由选择 要么k2满足要求
        ans+=dfs2(len-1,k1,k2,cnt1,cnt2+(k2!=0||flag2==0),k2==nums[len]&&flag1,k2==0&&flag2);
    }
    if(k1!=0&&k2!=0&&flag2==1){
        //填的是前导0
        ans+=dfs2(len-1,k1,k2,cnt1,cnt2,nums[len]==0&&flag1,flag2);
    }
    f[len][cnt1][cnt2][flag1][flag2]=ans;
    return ans;
}

int calc2(int x,int k1,int k2){
    //表示计算小于x的数字中  数字k1 k2出现次数大于等于总体一半的数字个数
    memset(f,-1,sizeof(f));
    for(len=0;x;x/=10){
        nums[++len]=x%10;
    }
    return dfs2(len,k1,k2,0,0,1,1);
}

signed main()
{
    cin>>n>>m;
    for(int i=0;i<=9;i++){
        ans+=calc1(m,i)-calc1(n-1,i);
    }
    //可能会答案多算 比如1122  即长度为偶数 两个数字都是一半
    for(int i=0;i<=9;i++){
        for(int j=i+1;j<=9;j++){
            ans-=calc2(m,i,j)-calc2(n-1,i,j);
        }
    }
    cout<<ans<<endl;
    return 0;
}

