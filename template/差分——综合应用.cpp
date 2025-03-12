#include<bits/stdc++.h>
using namespace std;

long fields[205][3];
int n;
int diff[202][202];

int rank1(long* nums, long v, int sz) {
    int l = 0;
    int r = sz - 1;
    int m, ans = 0;
    while (l <= r) {
        m = (l + r) / 2;
        if (nums[m] >= v) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return ans + 1;
}

void add(int a, int b, int c, int d) {
    diff[a][b] += 1;
    diff[c + 1][d + 1] += 1;
    diff[c + 1][b] -= 1;
    diff[a][d + 1] -= 1;
}

int sort1(long* nums) {
    sort(nums,nums+sizeof(nums)/sizeof(nums[0]));
    int sz = 1;
    for (int i = 1; i < n; i++) {
        if (nums[i] != nums[sz - 1]) {
            nums[sz++] = nums[i];
        }
    }
    return sz;
}

int main()
{
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>fields[i][0]>>fields[i][1]>>fields[i][2];
    }
    // n : 矩形的个数，x 2*n个坐标
    long* xs = new long[n << 1];
    long* ys = new long[n << 1];
    for (int i = 0, k = 0, p = 0; i < n; i++) {
        long x = fields[i][0];
        long y = fields[i][1];
        long r = fields[i][2];
        xs[k++] = (x << 1) - r;
        xs[k++] = (x << 1) + r;
        ys[p++] = (y << 1) - r;
        ys[p++] = (y << 1) + r;
    }
    // xs数组中，排序了且相同值只留一份，返回有效长度
    int sizex = sort1(xs);
    // ys数组中，排序了且相同值只留一份，返回有效长度
    int sizey = sort1(ys);
    // n个力场，sizex : 2 * n, sizey : 2 * n
    for (int i = 0, a, b, c, d; i < n; i++) {
        long x = fields[i][0];
        long y = fields[i][1];
        long r = fields[i][2];
        a = rank1(xs, (x << 1) - r, sizex);
        b = rank1(ys, (y << 1) - r, sizey);
        c = rank1(xs, (x << 1) + r, sizex);
        d = rank1(ys, (y << 1) + r, sizey);
        add(a, b, c, d);
    }
    int ans = 0;
    // O(n^2)
    for (int i = 1; i < sizex; i++) {
        for (int j = 1; j < sizey; j++) {
            diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
            ans = max(ans, diff[i][j]);
        }
    }
    cout<<ans;
    return 0;
}
