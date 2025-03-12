// 分割的方法数
// 给定一个长度为n的数组A, 将其分割成数组B和数组C，满足A[i] = B[i] + C[i]
// 也就是一个数字分成两份，然后各自进入B和C，要求B[i], C[i] >= 1
// 同时要求，B数组从左到右不能降序，C数组从左到右不能升序
// 比如，A = { 5, 4, 5 }，一种有效的划分，B = { 2, 2, 3 }，C = { 3, 2, 2 }
// 返回有多少种有效的划分方式
// 1 <= n <= 10^7
// 1 <= A[i] <= 10^7
// 最终结果可能很大，答案对 1000000007 取模
// 来自真实大厂笔试题，该实现为对数器版本
// 有同学找到了测试链接，就是Code04_SplitWays2文件
#include<bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

// 乘法快速幂
long long power(long long x, long long p) {
    long long ans = 1;
    while (p > 0) {
        if ((p & 1) == 1) {
            ans = (ans * x) % MOD;
        }
        x = (x * x) % MOD;
        p >>= 1;
    }
    return ans;
}

int f(const std::vector<int>& arr, int i, int preb, int prec) {
    if (i == arr.size()) {
        return 1;
    }
    int ans = 0;
    for (int b = 1, c = arr[i] - 1; b < arr[i]; ++b, --c) {
        if (preb <= b && prec >= c) {
            ans += f(arr, i + 1, b, c);
        }
    }
    return ans;
}

// 组合公式
int c(int n, int k) {
    long long fac = 1;
    long long inv1 = 1;
    long long inv2 = 1;
    for (int i = 1; i <= n; ++i) {
        fac = (fac * i) % MOD;
        if (i == k) {
            inv1 = power(fac, MOD - 2); // 费马小定理求逆元
        }
        if (i == n - k) {
            inv2 = power(fac, MOD - 2); // 费马小定理求逆元
        }
    }
    return (int) ((((fac * inv1) % MOD) * inv2) % MOD);
}

// 暴力方法
int ways1(const std::vector<int>& arr) {
    int ans = 0;
    for (int b = 1, c = arr[0] - 1; b < arr[0]; ++b, --c) {
        ans += f(arr, 1, b, c);
    }
    return ans;
}

// 正式方法
// 转化成杨辉三角
int ways2(const std::vector<int>& arr) {
    int n = arr.size();
    int k = arr[0] - 1;
    for (int i = 1; i < n && k > 0; ++i) {
        if (arr[i - 1] > arr[i]) {
            k -= arr[i - 1] - arr[i];
        }
    }
    if (k <= 0) {
        return 0;
    }
    return c(k + n - 1, n);
}

// 为了测试
std::vector<int> randomArray(int n, int v) {
    std::vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
        ans[i] = rand() % v + 1;
    }
    return ans;
}

// 测试函数
int main() {
    srand(static_cast<unsigned int>(time(0)));
    std::cout << "功能测试开始" << std::endl;
    int N = 10;
    int V = 20;
    int test = 2000;
    for (int i = 0; i < test; ++i) {
        int n = rand() % N + 1;
        std::vector<int> arr = randomArray(n, V);
        int ans1 = ways1(arr);
        int ans2 = ways2(arr);
        if (ans1 != ans2) {
            std::cout << "出错了!" << std::endl;
        }
        else{
            cout<<"第"<<setw(5)<<i<<"组测试正确！"<<endl;
        }
    }
    std::cout << "功能测试结束" << std::endl;

//    std::cout << "==========" << std::endl;
//
//    std::cout << "性能测试开始" << std::endl;
//    int n = 10000000;
//    int v = 10000000;
//    auto start, end;
//    std::vector<int> arr(n);
//
//    std::cout << "随机生成的数据测试" << std::endl;
//    std::cout << "数组长度 : " << n << std::endl;
//    std::cout << "数值范围 : [" << 1 << "," << v << "]" << std::endl;
//    for (int i = 0; i < n; ++i) {
//        arr[i] = rand() % v + 1;
//    }
//    start = std::chrono::high_resolution_clock::now();
//    ways2(arr);
//    end = std::chrono::high_resolution_clock::now();
//    std::chrono::duration<double> elapsed_seconds = end - start;
//    std::cout << "运行时间 : " << elapsed_seconds.count() * 1000 << " 毫秒" << std::endl;
//
//    std::cout << std::endl;
//
//    std::cout << "运行最慢的数据测试" << std::endl;
//    std::cout << "数组长度 : " << n << std::endl;
//    std::cout << "数值都是 : " << v << std::endl;
//    std::cout << "这种情况其实是复杂度最高的情况" << std::endl;
//    for (int i = 0; i < n; ++i) {
//        arr[i] = v;
//    }
//    start = std::chrono::high_resolution_clock::now();
//    ways2(arr);
//    end = std::chrono::high_resolution_clock::now();
//    elapsed_seconds = end - start;
//    std::cout << "运行时间 : " << elapsed_seconds.count() * 1000 << " 毫秒" << std::endl;
//    std::cout << "性能测试结束" << std::endl;

    return 0;
}
