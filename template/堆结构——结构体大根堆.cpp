#include <iostream>
#include <queue>
#include <vector>
#include <functional>

struct Range {
    int l, r;

    friend std::ostream& operator<<(std::ostream& os, const Range& range) {
        os << "(" << range.l << ", " << range.r << ")";
        return os;
    }
};

// �ȽϺ���������С���ѣ��� l ֵ���ʱ������ͨ����Ӷ���ıȽ��������ȶ���
bool compare(const Range& a, const Range& b) {
    return a.l < b.l; // ע��������С�ںţ���Ϊ����Ҫʹ�� greater<> ����ô����
    // �����Ҫ�����ӵ������߼����� l ���ʱ�� r ���򣩣��������������
}

int main() {
    int n;
    std::cin >> n;

    std::priority_queue<Range, std::vector<Range>, decltype(&compare)> pq(compare);

    Range range;
    for (int i = 0; i < n; i++) {
        std::cin >> range.l >> range.r;
        pq.push(range);
        // ������������ pop �� print
        std::cout << "�Ѷ�Ԫ��: " << pq.top() << std::endl;
    }



    return 0;
}
