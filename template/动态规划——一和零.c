#include <stdio.h>
#include <string.h>
#define max 100
// 全局变量
static int zeros, ones;

int main()
{
    char str[max][max][max];
    for(int )
    return 0;
}
/*// 统计一个字符串中0和1的数量
void zerosAndOnes(const char* str) {
    zeros = 0;
    ones = 0;
    while (*str) {
        if (*str == '0') {
            zeros++;
        } else if (*str == '1') {
            ones++;
        }
        printf("%5d %5d\n",zeros,ones);
        str++;
    }
}

// strs[i...]自由选择，希望零的数量不超过z、一的数量不超过o
// 最多能选多少个字符串
int f1(const char* strs[], int i, int z, int o) {
    if (i == 0 && strs == NULL) {
        // 没有字符串了
        return 0;
    }
    // 不使用当前的strs[i]字符串
    int p1 = f1(strs, i + 1, z, o);

    // 使用当前的strs[i]字符串
    int p2 = 0;
    zerosAndOnes(strs[i]);
    if (zeros <= z && ones <= o) {
        p2 = 1 + f1(strs, i + 1, z - zeros, o - ones);
    }
    return (p1 > p2) ? p1 : p2;
}

// 对外提供的接口，统计最多能选多少个字符串
int findMaxForm(const char* strs[], int m, int n) {
    return f1(strs, 0, m, n);
}

int main() {
    // 示例
    const char* strs[] = {"10", "0001", "111001", "1", "0"};
    int m = 5, n = 3;
    printf("最多能选 %d 个字符串\n", findMaxForm(strs, m, n));
    return 0;
}*/
