#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int f(int* arr, int n, int time) {
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += (time / arr[i]) + 1;
    }
    return ans;
}

int waitingTime2(int* arr, int n, int w) {
    int min = INT_MAX;
    for (int i = 0; i < n; i++) {
        min = (arr[i] < min) ? arr[i] : min;
    }

    int left = 0, right = min * w, mid, ans = 0;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (f(arr, n, mid) >= w + 1) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return ans;
}

int main() {
    int n,m;
    scanf("%d %d",&n,&m);
    int arr[n];
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    printf("%d\n",waitingTime2(arr,n,m));
    return 0;
}
