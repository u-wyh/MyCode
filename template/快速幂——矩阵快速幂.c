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
//参数是需要的矩阵大小：行和列

// 矩阵相乘
int** multiply(int** a, int** b, int n) {
    int** result = createMatrix(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = 0;
            for (int k = 0; k < n; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return result;
}
//这个矩阵乘法不具备普遍性  这个只能用来计算两个正方形矩阵
//如果是矩形矩阵，那么可以参考  快速幂——矩阵乘法

// 矩阵幂
int** power(int** m, int p, int n) {
    int** ans = createMatrix(n, n);
    for (int i = 0; i < n; i++) {
        for(int j=0;j<n;j++)
        {
            ans[i][j]=0;
            if(i==j)
                ans[i][j]=1;
        }
    }
    for (; p != 0; p >>= 1) {
        if ((p & 1) != 0) {
            ans = multiply(ans, m,n);
        }
        m = multiply(m, m,n);
    }
    return ans;
}
//m是数组指针，p是它的幂，n是它的宽度（正方形矩阵）

// 打印二维矩阵
void print(int** m, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d", m[i][j]);
        }
        printf("\n");
    }
}

// 释放二维数组
void freeMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int n, p;
    scanf("%d %d", &n, &p); // 读取矩阵大小和幂

    int** m = createMatrix(n, n);

    // 输入矩阵m
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &m[i][j]);
        }
    }

    int** result = power(m, p, n);

    // 打印结果矩阵
    print(result, n);

    // 释放内存
    freeMatrix(m, n);
    freeMatrix(result, n);

    return 0;
}
