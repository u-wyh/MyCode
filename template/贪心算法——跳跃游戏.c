#include <stdio.h>
#include <stdlib.h>

// 声明jump函数
int jump(int* arr, int n) {

    // 当前步以内，最右到哪
    int cur = 0;

    // 如果再一步，(当前步+1)以内，最右到哪
    int next = 0;

    // 一共需要跳几步
    int ans = 0;

    for (int i = 0; i < n; i++) {
        // 来到i下标
        // cur包括了i所在的位置，不用付出额外步数
        // cur没有包括i所在的位置，需要付出额外步数
        if (cur < i) {
            ans++;
            cur = next;
        }
        // 更新next，即当前步（包含下一步）内能到达的最远距离
        next = (next > i + arr[i]) ? next : i + arr[i];
    }

    return ans;
}

int main() {
    int n;
    scanf("%d",&n);
    int arr[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }

    // 调用jump函数并打印结果
    int result = jump(arr, n);
    printf("Minimum jumps to reach the end: %d\n", result);

    return 0;
}
