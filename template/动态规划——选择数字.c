#include<stdio.h>
#include<stdbool.h>

// 如果1~7范围的数字都能选，那么status的状态为：
// 1 1 1 1 1 1 1 1
// 7 6 5 4 3 2 1 0
// 0位弃而不用
// 如果1~7范围的数字，4、2已经选了不能再选，那么status的状态为：
// 1 1 1 0 1 0 1 1
// 7 6 5 4 3 2 1 0
// 0位弃而不用
// f的含义 :
// 数字范围1~n，当前的先手，面对status给定的数字状态
// 在累加和还剩rest的情况下
// 返回当前的先手能不能赢，能赢返回true，不能赢返回false
bool f(int n, int status, int rest, int* dp) {
    if (rest <= 0) {
        return false;
    }
    // rest > 0
    if (dp[status] != 0) {
        return dp[status] == 1;
    }
    //用于判断此时的status是否是可以获胜的
    bool ans = false;
    for (int i = 1; i <= n; i++) {
        // 考察所有数字，但是不能选择之前选了的数字
        if ((status & (1 << i)) != 0 && !f(n, (status ^ (1 << i)), rest - i, dp)) {
            ans = true;
            break;
        }
    }
    dp[status] = ans ? 1 : -1;
    return ans;
}

bool canIWin(int n, int m) {
    if (m == 0) {
        // 来自题目规定
        return true;
    }
    if (n * (n + 1) / 2 < m) {
        // 如果1~n数字全加起来
        // 累加和和是n * (n+1) / 2，都小于m
        // 那么不会有赢家，也就意味着先手不会获胜
        return false;
    }
    // dp[status] == 0 代表没算过
    // dp[status] == 1 算过，答案是true
    // dp[status] == -1 算过，答案是false
    int dp [1 << (n + 1)];
    for(int i=0;i<(1<<(n+1));i++)
        dp[i]=0;
    return f(n, (1 << (n + 1)) - 1, m, dp);
}
/*
我们要注意这个status是状态，我们不能把它当成一个数字，要把它看成一个二进位制的数字组成的数组
dp[status]的含义是在status的状态下，面对这个局面的选手能否获胜
其实我们最终的答案也可以是dp[status] status最初的值  是否是1
*/
int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    if(canIWin(n,m))
        printf("yes\n");
    else
        printf("no\n");
    return 0;
}
