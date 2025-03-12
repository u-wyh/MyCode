#include <stdio.h>
#include <string.h>

#define MAXN 301

int father[MAXN];
int sets;

void build(int n) {
    for (int i = 0; i < n; i++) {
        father[i] = i;
    }
    sets = n;
}

int find(int i) {
    if (i != father[i]) {
        father[i] = find(father[i]);
    }
    return father[i];
}

void union_sets(int x, int y) {
    int fx = find(x);
    int fy = find(y);
    if (fx != fy) {
        father[fx] = fy;
        sets--;
    }
}

int numSimilarGroups(char* strs[], int n) {
    int m = strlen(strs[0]); // 假设所有字符串长度相同
    build(n);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (find(i) != find(j)) {
                int diff = 0;
                for (int k = 0; k < m && diff < 3; k++) {
                    if (strs[i][k] != strs[j][k]) {
                        diff++;
                    }
                }
                if (diff == 0 || diff == 2) {
                    union_sets(i, j);
                }
            }
        }
    }

    return sets;
}

int main() {
    char* strs[] = {"star", "sart", "atsr", "asbt", "aart"};
    int n = sizeof(strs) / sizeof(strs[0]);
    int result = numSimilarGroups(strs, n);
    printf("Number of similar groups: %d\n", result);
    return 0;
}
