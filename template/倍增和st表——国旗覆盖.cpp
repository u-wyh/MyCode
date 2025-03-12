#include<bits/stdc++.h>
using namespace std;
const int MAXN = 200001;
const int LIMIT = 18;

int power;
int line[MAXN << 1][3];
// stjump[i][p] : 从i号线段出发，跳的次数是2的p次方，能到达的最右线段的编号
int stjump[MAXN << 1][LIMIT];
int ans[MAXN];
int n, m;

int read(){
	int a=0,k=1;char c=getchar();
	while (!isdigit(c)){if (c=='-')k=-1;c=getchar();}
	while (isdigit(c)){a=a*10+c-'0';c=getchar();}
	return a*k;
}

int log2(int n) {
    int ans = 0;
    while ((1 << ans) <= (n >> 1)) {
        ans++;
    }
    return ans;
}

void sortBySecondColumn(int line[][3], int n) {
    for (int i = 1; i <= n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j <= n; ++j) {
            if (line[j][1] < line[minIndex][1]) {
                minIndex = j;
            }
        }
        // 交换行
        for (int k = 0; k < 3; ++k) {
            int temp = line[i][k];
            line[i][k] = line[minIndex][k];
            line[minIndex][k] = temp;
        }
    }
}

void build() {
    for (int i = 1; i <= n; i++) {
        if (line[i][1] > line[i][2]) {
            line[i][2] += m;
        }
    }
    sortBySecondColumn(line ,n);
    //for(int i=1;i<=n;i++)
      //  printf("%d %d %d\n",line[i][0],line[i][1],line[i][2]);
    for (int i = 1; i <= n; i++) {
        line[i + n][0] = line[i][0];
        line[i + n][1] = line[i][1] + m;
        line[i + n][2] = line[i][2] + m;
    }
    int e = n << 1;
    for (int i = 1, arrive = 1; i <= e; i++) {
        while (arrive + 1 <= e && line[arrive + 1][1] <= line[i][2]) {
            arrive++;
        }
        stjump[i][0] = arrive;
    }
    for (int p = 1; p <= power; p++) {
        for (int i = 1; i <= e; i++) {
            stjump[i][p] = stjump[stjump[i][p - 1]][p - 1];
        }
    }
}

int jump(int i) {
    int aim = line[i][1] + m, cur = i, next, ans = 0;
    for (int p = power; p >= 0; p--) {
        next = stjump[cur][p];
        if (next != 0 && line[next][2] < aim) {
            ans += 1 << p;
            cur = next;
        }
    }
    return ans + 1 + 1;
}

void compute() {
    power = log2(n);
    build();
    for (int i = 1; i <= n; i++) {
        //填答案
        //如果一开始的顺序是  1 2 3 4 5
        //但是经过排序可能变为5 3 1 4 2
        //那么我们一开始就记录了编号   将相应的答案填到对应编号中
        ans[line[i][0]] = jump(i);
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        line[i][0]=i;
        line[i][1]=read();
        line[i][2]=read();
    }
    compute();
    for(int i=1;i<=n;i++)
        cout<<ans[i]<<' ';
    return 0;
}
