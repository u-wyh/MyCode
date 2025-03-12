#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

// 定义移动方向数组，0:上，1:右，2:下，3:左
const int mov[5] = { -1, 0, 1, 0, -1 };

// Dijkstra算法
// grid[i][j] == 0 代表障碍
// grid[i][j] == 1 代表道路
// 只能走上、下、左、右，不包括斜线方向
// 返回从(startX, startY)到(targetX, targetY)的最短距离
int minDistance1(vector<vector<int>>& grid, int startX, int startY, int targetX, int targetY) {
    if (grid[startX][startY] == 0 || grid[targetX][targetY] == 0) {
        return -1;
    }
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> distance(n, vector<int>(m, INT_MAX));
    distance[startX][startY] = 1;
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> heap;
    heap.emplace(1, make_pair(startX, startY));
    while (!heap.empty()) {
        auto cur = heap.top();
        heap.pop();
        int d = cur.first;
        int x = cur.second.first;
        int y = cur.second.second;
        if (visited[x][y]) {
            continue;
        }
        visited[x][y] = true;
        if (x == targetX && y == targetY) {
            return distance[x][y];
        }
        for (int i = 0; i < 4; ++i) {
            int nx = x + mov[i];
            int ny = y + mov[i + 1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == 1 && !visited[nx][ny] && d + 1 < distance[nx][ny]) {
                distance[nx][ny] = d + 1;
                heap.emplace(d + 1, make_pair(nx, ny));
            }
        }
    }
    return -1;
}


// 曼哈顿距离
int f1(int x, int y, int targetX, int targetY) {
    return abs(targetX - x) + abs(targetY - y);
}

// 对角线距离
int f2(int x, int y, int targetX, int targetY) {
    return max(abs(targetX - x), abs(targetY - y));
}

// 欧式距离
double f3(int x, int y, int targetX, int targetY) {
    return sqrt(pow(targetX - x, 2) + pow(targetY - y, 2));
}


// A*算法
// grid[i][j] == 0 代表障碍
// grid[i][j] == 1 代表道路
// 只能走上、下、左、右，不包括斜线方向
// 返回从(startX, startY)到(targetX, targetY)的最短距离
int minDistance2(vector<vector<int>>& grid, int startX, int startY, int targetX, int targetY) {
    if (grid[startX][startY] == 0 || grid[targetX][targetY] == 0) {
        return -1;
    }
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> distance(n, vector<int>(m, INT_MAX));
    distance[startX][startY] = 1;
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    auto compare = [](const pair<int, pair<int, int>>& a, const pair<int, pair<int, int>>& b) {
        return a.first > b.first;
    };
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, decltype(compare)> heap(compare);
    heap.emplace(1 + f1(startX, startY, targetX, targetY), make_pair(startX, startY));
    while (!heap.empty()) {
        auto cur = heap.top();
        heap.pop();
        int d = cur.first - f1(cur.second.first, cur.second.second, targetX, targetY); // 实际距离
        int x = cur.second.first;
        int y = cur.second.second;
        if (visited[x][y]) {
            continue;
        }
        visited[x][y] = true;
        if (x == targetX && y == targetY) {
            return distance[x][y];
        }
        for (int i = 0; i < 4; ++i) {
            int nx = x + mov[i];
            int ny = y + mov[i + 1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == 1 && !visited[nx][ny] && distance[x][y] + 1 < distance[nx][ny]) {
                distance[nx][ny] = distance[x][y] + 1;
                heap.emplace(distance[nx][ny] + 1 + f1(nx, ny, targetX, targetY), make_pair(nx, ny));
            }
        }
    }
    return -1;
}

// 为了测试
vector<vector<int>> randomGrid(int n) {
    vector<vector<int>> grid(n, vector<int>(n));
    srand(time(0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            grid[i][j] = rand() % 10 < 3 ? 0 : 1; // 每个格子有30%概率是0
        }
    }
    return grid;
}

// 为了测试
int main() {
    int len = 100;
    int testTime = 1000;
    cout << "功能测试开始" << endl;
    for (int i = 0; i < testTime; ++i) {
        int n = rand() % len + 2;
        vector<vector<int>> grid = randomGrid(n);
        int startX = rand() % n;
        int startY = rand() % n;
        int targetX = rand() % n;
        int targetY = rand() % n;
        int ans1 = minDistance1(grid, startX, startY, targetX, targetY);
        int ans2 = minDistance2(grid, startX, startY, targetX, targetY);
        if (ans1 != ans2) {
            cout << "出错了!" << endl;
        }else {
            cout << "第" << setw(5) << i << "组测试正确！" << endl;
        }
    }
    cout << "功能测试结束" << endl;

    cout << "性能测试开始" << endl;
    vector<vector<int>> grid_large = randomGrid(2000);
    int startX = 0;
    int startY = 0;
    int targetX = 1999;
    int targetY = 1999;
    clock_t start, end;
    start = clock();
    int ans1 = minDistance1(grid_large, startX, startY, targetX, targetY);
    end = clock();
    cout << "运行Dijkstra算法结果: " << ans1 << ", 运行时间(毫秒) : " << double(end - start) / CLOCKS_PER_SEC * 1000 << endl;
    start = clock();
    int ans2 = minDistance2(grid_large, startX, startY, targetX, targetY);
    end = clock();
    cout << "运行A*算法结果: " << ans2 << ", 运行时间(毫秒) : " << double(end - start) / CLOCKS_PER_SEC * 1000 << endl;
    cout << "性能测试结束" << endl;
    return 0;
}
