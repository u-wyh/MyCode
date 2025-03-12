#include <stdio.h>
#include <stdlib.h>

// 矩阵相乘
void multiply(int** a, int** b, int** result, int n, int m, int p) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            result[i][j] = 0;
            for (int c = 0; c < m; c++) {
                result[i][j] += a[i][c] * b[c][j];
            }
        }
    }
}
//这段代码没有返回值，我们更推荐使用下面的代码
//矩阵a是n*m型   b是m*p型

/*
int ** multiply(int** a, int** b, int n, int m, int p) {
    int** result=createMatrix(n,p);
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
*/

// 打印二维矩阵
void print(int** m, int n, int p) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            printf("%4d", m[i][j]);
        }
        printf("\n");
    }
}

// 动态分配二维数组
int** createMatrix(int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }
    return matrix;
}

// 释放二维数组
void freeMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int n, m, p;
    scanf("%d %d %d", &n, &m, &p); // 读取矩阵A的n行m列和矩阵B的m行p列

    int** a = createMatrix(n, m);
    int** b = createMatrix(m, p);
    int** result = createMatrix(n, p);

    // 输入矩阵A
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    // 输入矩阵B
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            scanf("%d", &b[i][j]);
        }
    }

    // 矩阵相乘
    multiply(a, b, result, n, m, p);

    // 打印结果
    print(result, n, p);

    // 释放内存
    freeMatrix(a, n);
    freeMatrix(b, m);
    freeMatrix(result, n);

    return 0;
}
