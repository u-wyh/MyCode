//P3375
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

char s1[MAXN];
char s2[MAXN];
int Next[MAXN];

// 计算next数组
void nextArray(const char *s, int m) {
    if (m == 1) {
        Next[0] = -1;
        return ;
    }

    Next[0] = -1;
    Next[1] = 0;

    int i = 2, cn = 0;
    // i表示当前要求next值的位置
    // cn表示当前要和前一个字符比对的下标
    while (i < m) {
        if (s[i - 1] == s[cn]) {
            Next[i] = ++cn;
            if(s[Next[i]]==s[i]){
                Next[i]=Next[Next[i]];
            }
            i++;
        } else if (cn > 0) {
            cn = Next[cn];
        } else {
            Next[i] = ++cn;
            if(s[Next[i]]==s[i]){
                Next[i]=Next[Next[i]];
            }
            i++;
        }
        //下面这个优化代码的意思是  如果匹配成功了  那么看看能不能更省事 更进一步
        //如果失败了  那么没有资格继续
        //这个是优化代码  意思是这个位置上对不上  跳转的位置和现在一样
        //所以一定也是不对的  那么就再调一下
//        if(s[Next[i]]==s[i]){
//            Next[i]=Next[Next[i]];
//        }
    }
}

// KMP算法的核心函数
int kmp(const char *s1, const char *s2) {
    int n = strlen(s1), m = strlen(s2), x = 0, y = 0;
    nextArray(s2, m);
    for(int i=0;i<m;i++){
        cout<<Next[i]<<' ';
    }
    cout<<endl;
    // s1中当前比对的位置是x
    // s2中当前比对的位置是y
    while (x < n && y < m) {
        if (s1[x] == s2[y]) {
            x++;
            y++;
        } else if (y == 0) {
            x++;
            //表示s2已经在第一个位置了
        } else {
            y = Next[y];
            //表示s2往前跳
        }
    }

    return y == m ? x - y : -1;
}

int main()
{
    cin>>s1>>s2;
    int result = kmp(s1, s2);
    if (result != -1) {
        printf("Found at index: %d\n", result);
    } else {
        printf("Not found\n");
    }
    return 0;
}
