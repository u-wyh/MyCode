/*
// 组团买票
// 景区里一共有m个项目，景区的第i个项目有如下两个参数：
// game[i] = { Ki, Bi }，Ki、Bi一定是正数
// Ki代表折扣系数，Bi代表票价
// 举个例子 : Ki = 2, Bi = 10
// 如果只有1个人买票，单张门票的价格为 : Bi - Ki * 1 = 8
// 所以这1个人游玩该项目要花8元
// 如果有2个人买票，单张门票的价格为 : Bi - Ki * 2 = 6
// 所以这2个人游玩该项目要花6 * 2 = 12元
// 如果有5个人买票，单张门票的价格为 : Bi - Ki * 5 = 0
// 所以这5个人游玩该项目要花5 * 0 = 0元
// 如果有更多人买票，都认为花0元(因为让项目倒贴钱实在是太操蛋了)
// 于是可以认为，如果有x个人买票，单张门票的价格为 : Bi - Ki * x
// x个人游玩这个项目的总花费是 : max { x * (Bi - Ki * x), 0 }
// 单位一共有n个人，每个人最多可以选1个项目来游玩，也可以不选任何项目
// 所有员工将在明晚提交选择，然后由你去按照上面的规则，统一花钱购票
// 你想知道自己需要准备多少钱，就可以应付所有可能的情况，返回这个最保险的钱数
// 数据量描述 :
// 1 <= M、N、Ki、Bi <= 10^5
// 来自真实大厂笔试，没有在线测试，对数器验证
*/







//不对
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int ki;
    int bi;
    int people;
    // 计算再来一人能赚多少钱的函数
    int (*earn)(struct Game*);
} Game;

// 计算Game结构体中再来一人能赚多少钱
int game_earn(Game *g) {
    return g->bi - (g->people + 1) * g->ki - g->people * g->ki;
}

// 初始化Game结构体
Game* create_game(int k, int b) {
    Game *g = malloc(sizeof(Game));
    g->ki = k;
    g->bi = b;
    g->people = 0;
    g->earn = game_earn;
    return g;
}

// 比较两个Game结构体（用于堆）
int compare_games(const void *a, const void *b) {
    Game *ga = *(Game**)a;
    Game *gb = *(Game**)b;
    return (ga->earn(ga) - gb->earn(gb));
}

// 暴力方法（未实现，因为时间复杂度过高）

// 正式方法
int enough2(int n, int games[][2], int m) {
    Game **heap = malloc(m * sizeof(Game*));
    for (int i = 0; i < m; i++) {
        heap[i] = create_game(games[i][0], games[i][1]);
    }

    // 使用qsort初始化堆（因为C标准库没有直接的大根堆实现）
    qsort(heap, m, sizeof(Game*), compare_games);

    int ans = 0;
    for (int i = 0; i < n; i++) {
        Game *cur = heap[0];
        if (cur->earn(cur) <= 0) break;

        ans += cur->earn(cur);
        cur->people++;

        // 重新排序堆
        qsort(heap, m, sizeof(Game*), compare_games);
    }

    // 释放内存
    for (int i = 0; i < m; i++) {
        free(heap[i]);
    }
    free(heap);

    return ans;
}

// 辅助函数，生成随机游戏数组
int** randomGames(int *m, int v) {
    *m = rand() % 20 + 1; // 假设最多20个游戏
    int **games = malloc(*m * sizeof(int*));
    for (int i = 0; i < *m; i++) {
        games[i] = malloc(2 * sizeof(int));
        games[i][0] = rand() % v + 1;
        games[i][1] = rand() % v + 1;
    }
    return games;
}

// 主函数，用于测试
int main() {
    srand(time(NULL)); // 初始化随机数生成器

    int N = 8, M = 8, V = 20, testTimes = 2000;
    printf("测试开始\n");

    for (int i = 0; i < testTimes; i++) {
        int n = rand() % N + 1;
        int m;
        int **games = randomGames(&m, V);

        int ans1 = 0; // 暴力方法的结果（未实现）
        int ans2 = enough2(n, games, m);


    }

    printf("测试结束\n");
    return 0;
}
