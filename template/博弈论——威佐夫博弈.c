#include <stdio.h>
#include <math.h>

// 定义黄金分割比的近似值
#define PHI 1.6180339887498948482045868

int compute(int a, int b) {
    // 确保a <= b
    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }

    // 计算(b-a)*PHI，然后取整与a比较
    double result = (b - a) * PHI;
    if ((int)result == a) {
        // 如果相等，则后手赢
        return 0;
    } else {
        // 如果不相等，则先手赢
        return 1;
    }
}

int main() {
    int a, b;
    while (scanf("%d %d", &a, &b) != EOF) {
        printf("%d\n", compute(a, b));
    }
    return 0;
}
