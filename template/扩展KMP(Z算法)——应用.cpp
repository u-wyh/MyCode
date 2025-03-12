//https://codeforces.com/problemset/problem/126/B
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int z[MAXN];
int maxx[MAXN];//在i之前最大的z数组的值
char a[MAXN];
int n;

void zArray(char* s, int n) {
    z[0] = 0;
    maxx[0]=0;
    int maxlen=0;
    for (int i = 1, c = 1, r = 1, len; i < n; i++) {
        len = r > i ? min(r - i, z[i - c]) : 0;
        while (i + len < n && s[i + len] == s[len]) {
            len++;
        }
        if (i + len > r) {
            r = i + len;
            c = i;
        }
        z[i] = len;
        maxx[i]=maxlen;
        maxlen=max(len,maxlen);
    }
}

int main()
{
    scanf("%s",a);
    n=strlen(a);
    zArray(a,n);
    int ans=0;
    for(int i=1;i<n;i++){
        if(z[i]==n-i&&maxx[i]>=z[i]){
            ans=z[i];
            break;
        }
    }
    if(ans==0){
        cout<<"Just a legend" << endl;
    }
    else{
        for(int i=0;i<ans;i++){
            cout<<a[i];
        }
    }
    return 0;
}
