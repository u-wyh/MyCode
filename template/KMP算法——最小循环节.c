#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#define MAX 1000000+5

// ¼ÆËãnextÊý×é
int* nextArray(char *s, int m) {
    if (m == 1) {
        int *next = (int*)malloc(sizeof(int));
        next[0] = -1;
        return next;
    }
    int *next = (int*)malloc(m * sizeof(int));
    next[0] = -1;
    next[1] = 0;
    int i = 2, cn = 0;
    while (i <= m) {
        if (s[i - 1] == s[cn]) {
            next[i++] = ++cn;
        } else if (cn > 0) {
            cn = next[cn];
        } else {
            next[i++] = 0;
        }
    }

    return next;
}

int main() {
    int n;
    scanf("%d",&n);
    char s[MAX];
    scanf("%s",s);
    int *next=nextArray(s,n);
    printf("%d\n",n-next[n]);
    return 0;
}

