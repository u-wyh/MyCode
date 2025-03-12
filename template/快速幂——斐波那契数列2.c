#include <stdio.h>
#include <stdlib.h>

// 动态分配二维数组
int** createMatrix(int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    if (matrix == NULL) {
        fprintf(stderr, "Memory allocation failed for matrix rows\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for matrix cols\n");
            // Free previously allocated rows and exit
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            exit(EXIT_FAILURE);
        }
    }
    return matrix;
}

// 矩阵相乘
int** multiply(int** a, int** b, int n, int m, int p) {
    int** result = createMatrix(n, p);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            result[i][j] = 0;
            for (int c = 0; c < m; c++) {
                result[i][j] += a[i][c] * b[c][j];
            }
        }
    }
    return result;
}

// 矩阵快速幂
int** power(int** m, int p, int n) {
    int** ans = createMatrix(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans[i][j] = (i == j) ? 1 : 0;
        }
    }
    for (; p != 0; p >>= 1) {
        if (p & 1) {
            ans = multiply(ans, m, n, n, n);
        }
        m = multiply(m, m, n, n, n);
    }
    return ans;
}

// 释放二维数组
void freeMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// 计算斐波那契数列
int fib2(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    int** start = createMatrix(1, 2);
    start[0][0] = 1;
    start[0][1] = 0;

    int** base = createMatrix(2, 2);
    base[0][0] = 1; base[0][1] = 1;
    base[1][0] = 1; base[1][1] = 0;

    int** result = multiply(start, power(base, n - 1,2), 1, 2, 2);
    int fib = result[0][0];

    // 释放内存
    freeMatrix(start, 1);
    freeMatrix(base, 2);
    freeMatrix(result, 1);

    return fib;
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d\n", fib2(n));
    return 0;
}
