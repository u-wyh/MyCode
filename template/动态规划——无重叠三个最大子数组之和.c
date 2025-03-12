#include<stdio.h>
#define Max 100

int main()
{
    int nums[Max];
    int i=0;
    while(scanf("%d",&nums[i++])==1);
    int n=i-1;
    int k;
    printf("please enter the k: ");
    scanf("%d",&k);

    int sums[n];
    for (int l = 0, r = 0, sum = 0; r < n; r++) {
        // l....r
        sum += nums[r];
        if (r - l + 1 == k) {
            sums[l] = sum;
            sum -= nums[l];
            l++;
        }
    }

    int prefix [n];
    prefix[k-1]=0;
    for (int l = 1, r = k; r < n; l++, r++) {
        if (sums[l] > sums[prefix[r - 1]]) {
            // 注意>，为了同样最大累加和的情况下，最小的字典序
            prefix[r] = l;
        } else {
            prefix[r] = prefix[r - 1];
        }
    }

    int suffix [n];
    suffix[n - k] = n - k;
    for (int l = n - k - 1; l >= 0; l--) {
        if (sums[l] >= sums[suffix[l + 1]]) {
            // 注意>=，为了同样最大累加和的情况下，最小的字典序
            suffix[l] = l;
        } else {
            suffix[l] = suffix[l + 1];
        }
    }

    int a = 0, b = 0, c = 0, max = 0;
    // 0...i-1    i...j    j+1...n-1
    //   左     中(长度为k)     右
    for (int p, s, i = k, j = 2 * k - 1, sum; j < n - k; i++, j++) {
        // 0.....i-1   i.....j  j+1.....n-1
        // 最好开头p      i开头     最好开头s
        p = prefix[i - 1];
        s = suffix[j + 1];
        sum = sums[p] + sums[i] + sums[s];
        if (sum > max) {
            // 注意>，为了同样最大累加和的情况下，最小的字典序
            max = sum;
            a = p;
            b = i;
            c = s;
        }
    }
    printf("%5d %5d %5d\n",a,b,c);
    return 0;
}
