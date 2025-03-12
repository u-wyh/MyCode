#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

const int MAXN = 101;
const int BIT = 60;

int n;
vector<long long> arr(MAXN);
vector<long long> basis1(BIT + 1, 0);
bool zero1 = false;

//无论是普通消元法还是高斯消元法  只要后来的数组数目与原来的数目不一样的  一定是有0

//普通消元法  是将数字的二进制位是否有1  进行插入数字
//从第一个数字开始  从二进制最高位开始
//如果这一位置上有数字 那么就要与这个数字异或  然后去下一位比较
//如果没有数字  那么这个数字插到里面去
//然后对于原始数组能不能生成0特判

// 线性基里插入num，如果线性基增加了返回true，否则返回false
// 这个可以判断是否有0  当然 不返回也可以  最后比较两个数组的元素个数也是一样的
bool insert(long long num) {
    for (int i = BIT; i >= 0; i--) {
        if (num >> i & 1) {
            if (basis1[i] == 0) {
                basis1[i] = num;
                return true;
            }
            num ^= basis1[i];
        }
    }
    return false;
}

void compute1() {
    zero1 = false;
    for (int i = 1; i <= n; i++) {
        if (!insert(arr[i])) {
            zero1 = true;
            //插入一个数字  线性基数组没有增加一个  说明一定是被以前的异或为0了  那么一定有0
        }
    }
}

//高斯消元
// 因为不需要维护主元和自由元的依赖关系
// 所以高斯消元的写法可以得到简化
// 只有没有主元并且当前我们想要的列要有1的行  要交换到当前行
vector<long long> basis2(MAXN, 0);
int len = 1;
bool zero2 = false;

void swap(int a, int b) {
    long long tmp = basis2[a];
    basis2[a] = basis2[b];
    basis2[b] = tmp;
}

void compute2() {
    len = 1;
    for (int i = BIT; i >= 0; i--) {
        for (int j = len; j <= n; j++) {
            if (basis2[j] & (1LL << i)) {
                swap(j, len);
                break;
            }
        }
        if (basis2[len] & (1LL << i)) {
            for (int j = 1; j <= n; j++) {
                if (j != len && (basis2[j] & (1LL << i))) {
                    basis2[j] ^= basis2[len];
                }
            }
            len++;
        }
    }
    len--;
    zero2 = len != n;
}

void dfs(const vector<long long>& nums, int n, int i, bool pick, long long path, unordered_set<long long>& set) {
    if (i > n) {
        if (pick) {
            set.insert(path);
        }
    } else {
        dfs(nums, n, i + 1, pick, path, set);
        dfs(nums, n, i + 1, true, path ^ nums[i], set);
    }
}

void printXorResults(const vector<long long>& nums, int n) {
    unordered_set<long long> set;
    dfs(nums, n, 1, false, 0, set);

    // 将unordered_set转换为vector
    vector<long long> sortedResults(set.begin(), set.end());

    // 对结果进行排序
    sort(sortedResults.begin(), sortedResults.end());

    cout << "至少选择一个数字所有可能的异或和:" << endl;
    for (long long s : sortedResults) {
        cout << s << ", ";
    }
    cout << endl;
}

void showDetails() {
    // 例子1
    cout << "例子1" << endl;
    fill(basis1.begin(), basis1.end(), 0);
    arr[1] = 12;
    arr[2] = 9;
    arr[3] = 14;
    arr[4] = 11;
    n = 4;
    cout << "原始数组得到的异或结果如下" << endl;
    printXorResults(arr, n);

    cout << "===========================" << endl;
    cout << "普通消元得到的线性基 : " << endl;
    compute1();
    vector<long long> b1(MAXN, 0);
    int s1 = 0;
    for (int i = BIT; i >= 0; i--) {
        if (basis1[i] != 0) {
            cout << basis1[i] << " ";
            b1[++s1] = basis1[i];
        }
    }
    cout << endl;
    cout << "是否能异或出0 : " << (zero1 ? "true" : "false") << endl;
    cout << "普通消元得到的异或结果如下" << endl;
    printXorResults(b1, s1);
    cout << "===========================" << endl << endl;

    // 例子2
    cout << "例子2" << endl;
    fill(basis1.begin(), basis1.end(), 0);
    arr[1] = 2;
    arr[2] = 5;
    arr[3] = 11;
    arr[4] = 6;
    n = 4;
    cout << "原始数组得到的异或结果如下" << endl;
    printXorResults(arr, n);
    cout << "===========================" << endl;
    cout << "普通消元得到的线性基 : " << endl;
    compute1();
    vector<long long> b2(MAXN, 0);
    int s2 = 0;
    for (int i = BIT; i >= 0; i--) {
        if (basis1[i] != 0) {
            cout << basis1[i] << " ";
            b2[++s2] = basis1[i];
        }
    }
    cout << endl;
    cout << "是否能异或出0 : " << (zero1 ? "true" : "false") << endl;
    cout << "普通消元得到的异或结果如下" << endl;
    printXorResults(b2, s2);
    cout << "===========================" << endl << endl;

    // 例子3
    cout << "例子3" << endl;
    fill(basis2.begin(), basis2.end(), 0);
    arr[1] = basis2[1] = 6;
    arr[2] = basis2[2] = 37;
    arr[3] = basis2[3] = 35;
    arr[4] = basis2[4] = 33;
    n = 4;
    cout << "原始数组得到的异或结果如下" << endl;
    printXorResults(arr, n);
    cout << "===========================" << endl;
    cout << "高斯消元得到的线性基 : " << endl;
    compute2();
    for (int i = 1; i <= len; i++) {
        cout << basis2[i] << " ";
    }
    cout << endl;
    cout << "是否能异或出0 : " << (zero2 ? "true" : "false") << endl;
    cout << "高斯消元得到的异或结果如下" << endl;
    printXorResults(vector<long long>(basis2.begin(), basis2.begin() + len), len);
    cout << "===========================" << endl << endl;

    // 例子4
    cout << "例子4" << endl;
    fill(basis1.begin(), basis1.end(), 0);
    fill(basis2.begin(), basis2.end(), 0);
    arr[1] = basis2[1] = 7;
    arr[2] = basis2[2] = 10;
    arr[3] = basis2[3] = 4;
    n = 3;
    cout << "原始数组得到的异或结果如下" << endl;
    printXorResults(arr, n);
    cout << "===========================" << endl;
    cout << "普通消元" << endl;
    compute1();
    for (int i = BIT; i >= 0; i--) {
        if (basis1[i] != 0) {
            cout << basis1[i] << " ";
        }
    }
    cout << endl;
    cout << "是否能异或出0 : " << (zero1 ? "true" : "false") << endl;

    cout << "===========================" << endl;

    cout << "高斯消元" << endl;
    compute2();
    for (int i = 1; i <= len; i++) {
        cout << basis2[i] << " ";
    }
    cout << endl;
    cout << "是否能异或出0 : " << (zero2 ? "true" : "false") << endl;
}

int main() {
    showDetails();
    return 0;
}
