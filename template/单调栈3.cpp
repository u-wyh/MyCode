#include<bits/stdc++.h>
using namespace std;

const int MOD = 100000007;
int n;
int st[10000];
int arr[10000];

int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>arr[i];

    long ans = 0;
    int r = 0;
    for (int i = 0; i < n; i++) {
        while (r > 0 && arr[st[r - 1]] >= arr[i]) {
            int cur = st[--r];
            int left = r == 0 ? -1 : st[r - 1];
            ans = (ans + (long) (cur - left) * (i - cur) * arr[cur]) % MOD;
        }
        st[r++] = i;
    }
    while (r > 0) {
        int cur = st[--r];
        int left = r == 0 ? -1 : st[r - 1];
        ans = (ans + (long) (cur - left) * (n - cur) * arr[cur]) % MOD;
    }
    cout<<ans;
    return 0;
}
