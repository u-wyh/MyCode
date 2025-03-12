#include <stdio.h>
#include <stdlib.h>

// 定义会议结构体
typedef struct {
    int start;
    int end;
} Event;

// 比较函数，用于qsort
int compare(const void *a, const void *b) {
    Event *eventA = (Event *)a;
    Event *eventB = (Event *)b;
    return eventA->start - eventB->start;
}

// 最小堆的实现（简化版）
#define MAX_EVENTS 1000
int heap[MAX_EVENTS];
int heapSize = 0;

void heapifyDown(int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heapSize && heap[left] < heap[smallest]) {
        smallest = left;
    }
    if (right < heapSize && heap[right] < heap[smallest]) {
        smallest = right;
    }
    if (smallest != i) {
        int temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;
        heapifyDown(smallest);
    }
}

void insertHeap(int value) {
    heap[heapSize++] = value;
    int i = heapSize - 1;
    while (i > 0 && heap[(i - 1) / 2] > heap[i]) {
        int temp = heap[i];
        heap[i] = heap[(i - 1) / 2];
        heap[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

int deleteMin() {
    if (heapSize == 0) return -1;
    int min = heap[0];
    heap[0] = heap[heapSize - 1];
    heapSize--;
    heapifyDown(0);
    return min;
}

int maxEvents(Event events[], int n) {
    qsort(events, n, sizeof(Event), compare);

    int min = events[0].start;
    int max = events[0].end;
    for (int i = 1; i < n; i++) {
        if (events[i].end > max) {
            max = events[i].end;
        }
    }

    int ans = 0;
    int i = 0;
    for (int day = min; day <= max; day++) {
        while (i < n && events[i].start == day) {
            insertHeap(events[i++].end);
        }
        while (heapSize > 0 && heap[0] < day) {
            deleteMin();
        }
        if (heapSize > 0) {
            deleteMin();
            ans++;
        }
    }

    return ans;
}

int main() {
    // 示例用法
    int n;
    scanf("%d",&n);
    Event events[n] ;
    for(int i=0;i<n;i++)
    {
        scanf("%d %d",&events[i].start,&events[i].end);
    }
    printf("Max events: %d\n", maxEvents(events, n));
    return 0;
}
