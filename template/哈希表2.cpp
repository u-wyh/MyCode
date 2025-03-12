#include <iostream>
#include <set>
#include <string>
using namespace std;

int main()
{
    set<string> ds;
    string s1 = "wuyuhui"; // 直接使用字符串字面量初始化
    string s2 = "wuyuhui"; // 同样

    ds.insert(s1); // 将s1插入到集合中

    // 尝试查找s2，注意find返回的是一个迭代器
    auto it = ds.find(s2);
    if (it != ds.end()) { // 如果迭代器不是end()，说明找到了元素
        cout << "Found: " << *it << endl; // 输出找到的元素
    } else {
        cout << "Not found" << endl; // 否则，输出未找到
    }
    cout<<ds.size()<<endl;
    ds.insert(s2);
    cout<<ds.size()<<endl;
    return 0;
}
