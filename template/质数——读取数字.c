#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

// f1 函数的C语言版本，直接读取long long类型
void f1() {
    printf("f1函数测试读入\n");
    long long num;
    // 使用scanf直接读取long long类型，%lld是long long的占位符
    scanf("%lld", &num);
    printf("%lld\n", num);
}

// f2 函数在C语言中不需要特别的字符串到long long的转换，因为我们可以直接读取
void f2() {
    char str[100]; // 假设输入的数字字符串不超过99个字符加上一个'\0'
    long num;
    char *endptr;

    printf("f2函数测试读入: ");
    // 使用fgets而不是gets以避免溢出（gets已被弃用）
    // 注意：fgets会保留换行符，如果字符串长度小于缓冲区大小
    if (fgets(str, sizeof(str), stdin) == NULL) {
        perror("fgets failed");
        return;
    }

    // 移除可能的换行符
    str[strcspn(str, "\n")] = 0;

    // 使用strtol将字符串转换为long
    errno = 0; // 清除errno，因为strtol会在出错时设置它
    num = strtol(str, &endptr, 10);

    // 检查strtol的返回值是否因为溢出而失败
    if ((errno == ERANGE && (num == LONG_MAX || num == LONG_MIN))
            || (endptr == str)) {
        printf("转换失败: 溢出或输入非数字\n");
        return;
    }
}

int main() {
    f1();

    f2();
    return 0;
}
