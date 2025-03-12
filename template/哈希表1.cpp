#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>

class Student {
public:
    int age;
    std::string name;

    Student(int a, std::string b) : age(a), name(b) {}

    // 为了让Student对象可以作为哈希表的键，我们需要提供哈希函数和相等比较函数
    struct Hash {
        size_t operator()(const Student& s) const {
            return std::hash<std::string>()(s.name) ^ std::hash<int>()(s.age);
        }
    };

    struct Equal {
        bool operator()(const Student& lhs, const Student& rhs) const {
            return lhs.age == rhs.age && lhs.name == rhs.name;
        }
    };
};

int main() {
    // 字符串示例
    std::string str1 = std::string("Hello");
    std::string str2 = std::string("Hello");
    std::cout << (str1 == str2) << std::endl; // true

    std::unordered_set<std::string> set;
    set.insert(str1);
    std::cout << set.count("Hello") << std::endl; // 1
    std::cout << set.count(str2) << std::endl; // 1
    set.insert(str2); // 不会增加大小，因为内容相同
    std::cout << set.size() << std::endl; // 1
    set.erase(str1);
    set.clear();
    std::cout << set.empty() << std::endl; // true

    std::cout << "===========" << std::endl;

    std::unordered_map<std::string, std::string> map1;
    map1[str1] = "World";
    std::cout << map1.count("Hello") << std::endl; // 1
    std::cout << map1.count(str2) << std::endl; // 1
    std::cout << map1[str2] << std::endl; // World
    std::cout << (map1.find("你好") == map1.end()) << std::endl; // true
    map1.erase("Hello");
    std::cout << map1.size() << std::endl; // 0
    map1.clear();
    std::cout << map1.empty() << std::endl; // true

    std::cout << "===========" << std::endl;

    // 使用Student作为键的哈希表
    std::unordered_map<Student, std::string, Student::Hash, Student::Equal> map3;
    Student s1(17, "张三");
    Student s2(17, "张三");
    map3[s1] = "这是张三";
    std::cout << map3.count(s1) << std::endl; // 1
    std::cout << map3.count(s2) << std::endl; // 1
    map3[s2] = "这是另一个张三"; // 实际上会覆盖s1的条目，因为s1和s2被视为相等
    std::cout << map3.size() << std::endl; // 1
    std::cout << map3[s1] << std::endl; // 这是另一个张三
    std::cout << map3[s2] << std::endl; // 这是另一个张三

    return 0;
}
