#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>

class Student {
public:
    int age;
    std::string name;

    Student(int a, std::string b) : age(a), name(b) {}

    // Ϊ����Student���������Ϊ��ϣ��ļ���������Ҫ�ṩ��ϣ��������ȱȽϺ���
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
    // �ַ���ʾ��
    std::string str1 = std::string("Hello");
    std::string str2 = std::string("Hello");
    std::cout << (str1 == str2) << std::endl; // true

    std::unordered_set<std::string> set;
    set.insert(str1);
    std::cout << set.count("Hello") << std::endl; // 1
    std::cout << set.count(str2) << std::endl; // 1
    set.insert(str2); // �������Ӵ�С����Ϊ������ͬ
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
    std::cout << (map1.find("���") == map1.end()) << std::endl; // true
    map1.erase("Hello");
    std::cout << map1.size() << std::endl; // 0
    map1.clear();
    std::cout << map1.empty() << std::endl; // true

    std::cout << "===========" << std::endl;

    // ʹ��Student��Ϊ���Ĺ�ϣ��
    std::unordered_map<Student, std::string, Student::Hash, Student::Equal> map3;
    Student s1(17, "����");
    Student s2(17, "����");
    map3[s1] = "��������";
    std::cout << map3.count(s1) << std::endl; // 1
    std::cout << map3.count(s2) << std::endl; // 1
    map3[s2] = "������һ������"; // ʵ���ϻḲ��s1����Ŀ����Ϊs1��s2����Ϊ���
    std::cout << map3.size() << std::endl; // 1
    std::cout << map3[s1] << std::endl; // ������һ������
    std::cout << map3[s2] << std::endl; // ������һ������

    return 0;
}
