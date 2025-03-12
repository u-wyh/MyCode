#include<stdio.h>
#include<stdbool.h>
#define Max 1000

int n,m;
int nums[Max][Max];

int max(int a,int b)
{
    return a>b?a:b;
}

void dfs(int i, int j,int id) {
    if (i < 0 || i == n || j < 0 || j == m || nums[i][j] != 1) {
        return;
    }
    nums[i][j]=id;
    dfs(i-1,j,id);
    dfs(i,j-1,id);
    dfs(i+1,j,id);
    dfs(i,j+1,id);
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            scanf("%d",&nums[i][j]);
        }
    }
    int id = 2;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (nums[i][j] == 1) {
                dfs(i, j, id++);
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            printf("%2d",nums[i][j]);
        }
        printf("\n");
    }
    int sizes[id];
    for(int i=0;i<id;i++)
    {
        sizes[i]=0;
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (nums[i][j] > 1) {
                ans = max(ans, ++sizes[nums[i][j]]);
            }
        }
    }
    bool visited[id];
    for(int i = 0; i < id; i++) {
        visited[i] = 0;
    }
    int up, down, left, right, merge;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (nums[i][j] == 0) {
                up = i > 0 ? nums[i - 1][j] : 0;
                down = i + 1 < n ? nums[i + 1][j] : 0;
                left = j > 0 ? nums[i][j - 1] : 0;
                right = j + 1 < m ? nums[i][j + 1] : 0;
                visited[up] = true;
                merge = 1 + sizes[up];
                if (!visited[down]) {
                    merge += sizes[down];
                    visited[down] = true;
                }
                if (!visited[left]) {
                    merge += sizes[left];
                    visited[left] = true;
                }
                if (!visited[right]) {
                    merge += sizes[right];
                    visited[right] = true;
                }
                ans = max(ans, merge);
                visited[up] = false;
                visited[down] = false;
                visited[left] = false;
                visited[right] = false;
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
