// 获取所有钥匙的最短路径
// 给定一个二维网格 grid ，其中：
// '.' 代表一个空房间、'#' 代表一堵、'@' 是起点
// 小写字母代表钥匙、大写字母代表锁
// 从起点开始出发，一次移动是指向四个基本方向之一行走一个单位空间
// 不能在网格外面行走，也无法穿过一堵墙
// 如果途经一个钥匙，我们就把它捡起来。除非我们手里有对应的钥匙，否则无法通过锁。
// 假设 k 为 钥匙/锁 的个数，且满足 1 <= k <= 6，
// 字母表中的前 k 个字母在网格中都有自己对应的一个小写和一个大写字母
// 换言之，每个锁有唯一对应的钥匙，每个钥匙也有唯一对应的锁
// 另外，代表钥匙和锁的字母互为大小写并按字母顺序排列
// 返回获取所有钥匙所需要的移动的最少次数。如果无法获取所有钥匙，返回 -1 。
// 测试链接：https://leetcode.cn/problems/shortest-path-to-get-all-keys
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 31;
const int MAXM = 31;
const int MAXK = 6;

int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
char grid[MAXN][MAXM];
bool visited[MAXN][MAXM][1 << MAXK];
// 0 : 行
// 1 : 列
// 2 : 收集钥匙的状态
int q[MAXN * MAXM * (1 << MAXK)][3];
int l, r, n, m, key;

void build() {
    l = r = key = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '@') {
                q[r][0] = i;
                q[r][1] = j;
                // 0 : 000000
                q[r++][2] = 0;
            }
            if (grid[i][j] >= 'a' && grid[i][j] <= 'f') {
                key |= 1 << (grid[i][j] - 'a');
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int s = 0; s <= key; s++) {
                visited[i][j][s] = false;
            }
        }
    }
}

int main()
{
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>grid[i][j];
        }
    }
    build();
    int level = 1;
    while (l < r) {
        //相当于手写一个队列
        for (int k = 0, sz = r - l, x, y, s; k < sz; k++) {
            x = q[l][0];
            y = q[l][1];
            s = q[l++][2];
            for (int i = 0, nx, ny, ns; i < 4; i++) {
                nx = x + walk[i][0];
                ny = y + walk[i][1];
                ns = s;
                if (nx < 0 || nx == n || ny < 0 || ny == m || grid[nx][ny] == '#') {
                    // 越界或者障碍
                    continue;
                }
                if (grid[nx][ny] >= 'A' && grid[nx][ny] <= 'F' && ((ns & (1 << (grid[nx][ny] - 'A'))) == 0)) {
                    // 是锁，又没有对应的钥匙
                    continue;
                }
                if (grid[nx][ny] >= 'a' && grid[nx][ny] <= 'f') {
                    // 是某一把钥匙
                    ns |= (1 << (grid[nx][ny] - 'a'));
                }
                if (ns == key) {
                    // 常见剪枝
                    // 发现终点直接返回
                    // 不用等都结束
                    cout<<level;
                    return 0;
                }
                if (!visited[nx][ny][ns]) {
                    visited[nx][ny][ns] = true;
                    q[r][0] = nx;
                    q[r][1] = ny;
                    q[r++][2] = ns;
                }
            }
        }
        level++;
    }
    cout<<-1;
    return 0;
}
