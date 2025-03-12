//P3501
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;

char ss[MAXN << 1];//这个数组中间添加了#
char a[MAXN];//原始数组
int p[MAXN << 1];//半径数组
char change[300];
int n;

void manacherss() {
    n = strlen(a) * 2 + 1;
    for (int i = 0, j = 0; i < n; i++) {
        ss[i] = (i & 1) == 0 ? '#' : a[j++];
    }
}

void manacher(){
    for (int i = 0, c = 0, r = 0, len; i < n; i+=2) {//i是此时来到的中心位置
        //这里是比较特殊的一点 因为求的一定是偶数长度  不可能是奇数  所以每次加2
        len = r > i ? min(p[2 * c - i], r - i) : 1;//这个值是基本值  如果包住了  那么基本值就是最终值  否则后续再加
        while (i + len < n && i - len >= 0 && ss[i + len] == change[ss[i - len]]) {
            len++;
            //如果被包住了  那么直接跳出来了
        }
        //此时已经求出了以i为中心的回文半径大小
        if (i + len > r) {
            r = i + len;
            c = i;//c表示的是如今的r是以那个点为中心的右边界
            //如果更新了右边界  那么c就是i  r就是i+len
        }
        p[i] = len;
        //得到回文半径
    }
}

signed main()
{
    change['0']='1';
    change['1']='0';
    change['#']='#';
    cin>>n;
    scanf("%s",a);
    manacherss();
    manacher();
    int ans=0;
    for(int i=0;i<n;i++){
        ans+=(p[i]/2);
    }
    cout<<ans<<endl;
    return 0;
}
