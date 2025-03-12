#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool canConvert(const char *str1, const char *str2) {
    if (strcmp(str1, str2) == 0) {
        return true;
    }

    int map[26] = {0}; // 初始化map数组为0
    int kinds = 0;
    for (int i = 0; str2[i] != '\0'; i++) {
        int index = str2[i] - 'a';
        if (map[index] == 0) {
            kinds++;
        }
        map[index]++;
    }
    if (kinds == 26) {
        return false;
    }

    // 重新初始化map数组为-1，这里使用memset更方便
    memset(map, -1, sizeof(map));

    // map[x] = y 表示str1中的字符x上次出现在str1中的y位置
    for (int i = 0, cur; str1[i] != '\0'; i++) {
        cur = str1[i] - 'a';
        if (map[cur] != -1 && str2[map[cur]] != str2[i]) {
            return false;
        }
        map[cur] = i;
    }

    return true;
}

int main() {
    // 示例用法
    const char *str1 ;
    const char *str2 ;
    scanf("%s",str1);
    scanf("%s",str2);
    if (canConvert(str1, str2)) {
        printf("可以转换\n");
    } else {
        printf("不可以转换\n");
    }

    return 0;
}
