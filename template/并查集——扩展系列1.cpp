// 关押罪犯
// 一共有n个犯人，编号1 ~ n，一共有两个监狱，你可以决定每个犯人去哪个监狱
// 给定m条记录，每条记录 l r v，表示l号犯人和r号犯人的仇恨值
// 每个监狱的暴力值 = 该监狱中仇恨最深的犯人之间的仇恨值
// 冲突值 = max(第一座监狱的暴力值，第二座监狱的暴力值)
// 犯人的分配方案需要让这个冲突值最小，返回最小能是多少
// 1 <= n <= 20000    1 <= m <= 100000    1 <= 仇恨值 <= 10^9
// 测试链接 : https://www.luogu.com.cn/problem/P1525
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility> // for std::pair

using namespace std;

const int MAXN = 20002;
const int MAXM = 100001;

int n, m;
int father[MAXN];
int enemy[MAXN];
vector<pair<int, pair<int, int>>> arr(MAXM + 1); // vector of pairs to store the input

void prepare() {
    for (int i = 1; i <= n; i++) {
        father[i] = i;
        enemy[i] = 0;
    }
}

int find(int i) {
    if (father[i] != i) {
        father[i] = find(father[i]); // Path compression
    }
    return father[i];
}

void unionSets(int l, int r) {
    father[find(l)] = find(r);
}

bool sameSet(int l, int r) {
    return find(l) == find(r);
}

int compute() {
    // Sort based on the third element of the pair in descending order
    sort(arr.begin() + 1, arr.end(), [](const pair<int, pair<int, int>>& a, const pair<int, pair<int, int>>& b) {
        return a.second.second > b.second.second;
    });

    int ans = 0;
    for (int i = 1; i <= m; i++) {
        int l = arr[i].second.first;
        int r = arr[i].first;
        int v = arr[i].second.second;
        if (sameSet(l, r)) {
            ans = v;
            break;
        } else {
            if (enemy[l] == 0) {
                enemy[l] = r;
            } else {
                unionSets(enemy[l], r);
            }
            if (enemy[r] == 0) {
                enemy[r] = l;
            } else {
                unionSets(l, enemy[r]);
            }
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    prepare();
    for (int i = 1; i <= m; i++) {
        int l, r, v;
        cin >> l >> r >> v;
        arr[i] = make_pair(r, make_pair(l, v)); // Store in the format {r, {l, v}}
    }

    cout << compute() << endl;

    return 0;
}
