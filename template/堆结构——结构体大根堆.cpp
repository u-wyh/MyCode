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

// 比较函数，用于小根堆，当 l 值相等时，可以通过添加额外的比较来保持稳定性
bool compare(const Range& a, const Range& b) {
    return a.l < b.l; // 注意这里是小于号，因为我们要使用 greater<> 来获得大根堆
    // 如果需要更复杂的排序逻辑（如 l 相等时按 r 排序），可以在这里添加
}

int main() {
    int n;
    std::cin >> n;

    std::priority_queue<Range, std::vector<Range>, decltype(&compare)> pq(compare);

    Range range;
    for (int i = 0; i < n; i++) {
        std::cin >> range.l >> range.r;
        pq.push(range);
        // 不在这里立即 pop 和 print
        std::cout << "堆顶元素: " << pq.top() << std::endl;
    }



    return 0;
}
