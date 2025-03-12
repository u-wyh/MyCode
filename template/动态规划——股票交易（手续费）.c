#include <stdio.h>
#include <stdlib.h>

int maxProfit(int* prices, int pricesSize, int fee) {
    // prepare: 在交易次数无限制的情况下，扣除了购买和手续费之后，能获得的最大收益（初始化为负的第一天的价格减去手续费）
    int prepare = -prices[0] - fee;
    // done: 在交易次数无限制的情况下，能获得的最大收益（初始化为0）
    int done = 0;

    for (int i = 1; i < pricesSize; i++) {
        // 更新done：今天卖出股票能获得的最大收益
        done = (done > prepare + prices[i]) ? done : prepare + prices[i];
        // 更新prepare：如果今天买入股票然后未来某天卖出能获得的最大收益（需要扣除手续费）
        prepare = (prepare > done - prices[i] - fee) ? prepare : done - prices[i] - fee;
    }

    return done;
}

int main() {
    // 示例用法
    int n,fee;
    scanf("%d %d",&n,&fee);
    int prices[n];
    for(int i=0;i<n;i++)
        scanf("%d",&prices[i]);
    int result = maxProfit(prices, n, fee);
    printf("Maximum Profit: %d\n", result);
    return 0;
}
