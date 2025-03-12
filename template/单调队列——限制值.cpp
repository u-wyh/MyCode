#include<bits/stdc++.h>
using namespace std;

int n,limit;
int nums[10000];
int maxq[10000],minq[10000],maxh,maxt,minh,mint;

void push(int r) {
    while (maxh < maxt && nums[maxq[maxt - 1]] <= nums[r]) {
        maxt--;
    }
    maxq[maxt++] = r;
    while (minh < mint && nums[minq[mint - 1]] >= nums[r]) {
        mint--;
    }
    minq[mint++] = r;
}
//将一个新的数字压入minq  maxq中

void pop(int l) {
    if (maxh < maxt && maxq[maxh] == l) {
        maxh++;
    }
    if (minh < mint && minq[minh] == l) {
        minh++;
    }
}
//弹出已经过期的数据

bool ok(int number) {
    // max : 如果number进来，新窗口的最大值
    int max1 = maxh < maxt ? max(nums[maxq[maxh]], number) : number;
    // min : 如果number进来，新窗口的最小值
    int min1 = minh < mint ? min(nums[minq[minh]], number) : number;
    return max1 - min1 <= limit;
}

int longest(){
    maxh=0,maxt=0,minh=0,mint=0;
    //首先将两个单调队列的开头结尾初始化
    int ans = 0;
    for (int l = 0, r = 0; l < n; l++) {
        // [l,r)，r永远是没有进入窗口的、下一个数所在的位置
        while (r < n && ok(nums[r])) {
            push(r++);
            //如果可以  说明这个数字可以加入
        }
        // 判断条件说明还有下一个数字  并且这个数字加入后还是达标的
        // 从while出来的时候，[l,r)是l开头的子数组能向右延伸的最大范围
        ans = max(ans, r - l);
        pop(l);
        //以这个为头的数字数组结束  换下一个数字  把这个数字弹出
    }
    //for循环每一次可以返回一个由i开头的最大达标长度
    return ans;
}

int main()
{
    cin>>n>>limit;
    for(int i=0;i<n;i++)
        cin>>nums[i];
    cout<<longest()<<endl;
    return 0;
}
