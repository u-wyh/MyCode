#include <stdio.h>
#include <string.h>

#define MAXN 100000

int f[1000];
int size;
int sg[MAXN];
int appear[MAXN];

void build1(){
    f[0]=1;
    f[1]=2;
    size=1;
    while (f[size] <= MAXN) {
        f[size + 1] = f[size] + f[size - 1];
        size++;
    }
}

void build() {
    for (int i = 1; i < MAXN; i++) {
        memset(appear, 0, sizeof(appear));
        for (int j = 0; j < size && i - f[j] >= 0; j++) {
            appear[sg[i - f[j]]] = 1;
        }
        for (int s = 0; s < MAXN; s++) {
            if (!appear[s]) {
                sg[i] = s;
                break;
            }
        }
    }
}

int  win2(int a, int b, int c) {
    return sg[a] ^ sg[b] ^ sg[c];
}

int main() {
    build1();
    build();
    int a,b,c;
    scanf("%d %d %d",&a,&b,&c);
    printf("%d\n",win2(a,b,c));
    return 0;
}
