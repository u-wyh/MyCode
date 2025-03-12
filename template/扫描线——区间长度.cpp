// 包含每个查询的最小区间
// 给你一个二维整数数组intervals，其中intervals[i] = [l, r]
// 表示第i个区间开始于l，结束于r，区间的长度是r-l+1
// 给你一个整数数组queries，queries[i]表示要查询的位置
// 答案是所有包含queries[i]的区间中，最小长度的区间是多长
// 返回数组对应查询的所有答案，如果不存在这样的区间那么答案是-1
// 测试链接 : https://leetcode.cn/problems/minimum-interval-to-include-each-query/
#include<bits/stdc++.h>
using namespace std;

struct Range {
    int l, r ,len;
    /*
    friend std::ostream& operator<<(std::ostream& os, const Range& range) {
        os << "(" << range.len<<", "<<range.l << ", " << range.r << ")";
        return os;
    }
    */
    //这段代码是为了输出   当然这是没有必要的
};

struct Dot{
    int subscript,value;
};

bool compare(Range& a,Range& b) {
    return a.len > b.len;
}
//为了做出小根堆

bool cmp1(Range a,Range b){
    return a.l<b.l;
}

bool cmp2(Dot a,Dot b){
    return a.value<b.value;
}
//以上两个比较函数都是为了从小到大排序

int main()
{
    int n,m;
    cin>>n>>m;
    int ans[m];
    std::priority_queue<Range, std::vector<Range>, decltype(&compare)> pq(compare);
    //定义小根堆
    Range range[n+1];
    Dot dot[m+1];
    for(int i=1;i<=n;i++){
        cin>>range[i].l>>range[i].r;
        range[i].len=range[i].r-range[i].l+1;
    }
    sort(range+1,range+n+1,cmp1);
    /*
    for(int i=1;i<=n;i++){
        printf("%3d %3d %3d\n",range[i].l,range[i].r,range[i].len);
    }
    */
    for(int i=1;i<=m;i++){
        cin>>dot[i].value;
        dot[i].subscript=i;
    }
    sort(dot+1,dot+m+1,cmp2);
    /*
    for(int i=1;i<=m;i++){
        printf("%3d %3d\n",dot[i].value,dot[i].subscript);
    }
    */
    for(int i=1,j=1;i<=m;i++){
        //从小到大依次输出扫描线
        while(dot[i].value>=range[j].l&&j<=n){
            pq.push(range[j]);
            j++;
        }
        //将符合要求的区间加入到小根堆中
        //cout<<pq.top()<<endl;
        while(!pq.empty()&&pq.top().r<dot[i].value){
            pq.pop();
        }
        //只需要判断小根堆的顶端的区间是不是符合要求的  不是就弹出
        if(!pq.empty()){
            ans[dot[i].subscript]=pq.top().len;
        }else{
            ans[dot[i].subscript]=-1;
        }
    }
    for(int i=1;i<=m;i++){
        printf("%3d",ans[i]);
    }
    return 0;
}
