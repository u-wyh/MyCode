#include <iostream>
#include <set>
#include <string>
using namespace std;

int main()
{
    set<string> ds;
    string s1 = "wuyuhui"; // ֱ��ʹ���ַ�����������ʼ��
    string s2 = "wuyuhui"; // ͬ��

    ds.insert(s1); // ��s1���뵽������

    // ���Բ���s2��ע��find���ص���һ��������
    auto it = ds.find(s2);
    if (it != ds.end()) { // �������������end()��˵���ҵ���Ԫ��
        cout << "Found: " << *it << endl; // ����ҵ���Ԫ��
    } else {
        cout << "Not found" << endl; // �������δ�ҵ�
    }
    cout<<ds.size()<<endl;
    ds.insert(s2);
    cout<<ds.size()<<endl;
    return 0;
}
