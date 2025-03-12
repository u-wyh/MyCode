//https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=396
#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstring>
using namespace std;
const int MAXN = 101;

int z[MAXN];
char a[MAXN];
int n;

void zArray(char* s, int n) {
    z[0] = 0;
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
    }
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        scanf("%s",a);
        n=strlen(a);
        zArray(a,n);
        int ans=n;
        for(int i=1;i<n;i++){
            if(n%i==0&&i+z[i]==n){
                ans=i;
                break;
            }
        }
        cout<<ans<<endl<<endl;
    }
    return 0;
}
