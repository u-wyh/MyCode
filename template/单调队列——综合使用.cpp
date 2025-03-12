#include<bits/stdc++.h>
using namespace std;

int n,m,s,pills;
int workers[10000],tasks[10000];
int h,t;
int q[10005];

bool f(int tl,int tr,int wl,int wr){
    h=t=0;
    int cnt=0;
    for(int i=wl,j=tl;i<=wr;i++){
        for(;j<=wr&&tasks[j]<=workers[i];j++){
            q[t++]=j;
        }
        if(h<t&&tasks[q[h]]<=workers[i]){
            h++;
        }else{
            for(;j<=wr&&tasks[j]<=workers[i]+s;j++){
                q[t++]=j;
            }
            if(h<t){
                cnt++;
                t--;
            }else{
                return false;
            }
        }
    }
    return cnt<=pills;
}

int main()
{
    cin>>n>>m>>s>>pills;
    for(int i=0;i<n;i++)
        cin>>workers[i];
    for(int j=0;j<m;j++)
        cin>>tasks[j];
    sort(workers,workers+n);
    sort(tasks,tasks+m);
    int ans=-1;
    for (int l = 0, r = min(m, n), mid; l <= r;) {
        // m中点，一定要完成的任务数量
        mid = (l + r) / 2;
        if (f(0, mid - 1,n-mid,n-1)) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout<<ans<<endl;
    return 0;
}
