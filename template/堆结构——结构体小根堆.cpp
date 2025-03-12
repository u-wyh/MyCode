#include <iostream>
#include <queue>
#include <vector>
#include <functional>

struct Range {
    int l, r;

//    friend std::ostream& operator<<(std::ostream& os, const Range& range) {
//        os << "(" << range.l << ", " << range.r << ")";
//        return os;
//    }
};

// �ȽϺ���������С���ѣ��� l ֵ���ʱ������ͨ����Ӷ���ıȽ��������ȶ���
bool compare(const Range& a, const Range& b) {
    return a.l > b.l; // ע�������Ǵ��ںţ���Ϊ����Ҫʹ�� greater<> �����С����
    // �����Ҫ�����ӵ������߼����� l ���ʱ�� r ���򣩣��������������
}

int main() {
    int n;
    std::cin >> n;

    std::priority_queue<Range, std::vector<Range>, decltype(&compare)> pq(compare);
    //std::priority_queue<Range, std::vector<Range>, bool> pq(compare);
//    std::priority_queue<Range, std::vector<Range>, std::function<bool(Range, Range)>> pq(
//        [](const Range& a, const Range& b) { return a.l < b.l; } // С����
//    );
    Range range;
    for (int i = 0; i < n; i++) {
        std::cin >> range.l >> range.r;
        pq.push(range);
        // ������������ pop �� print
        Range a=pq.top();
        std::cout << "�Ѷ�Ԫ��(�ڶ���): " << a.r << std::endl;
    }



    return 0;
}
