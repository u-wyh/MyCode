#include<bits/stdc++.h>
using namespace std;

int n,m,k;
int edge[205][205];
int t[205];
struct node{
    int a,b,t;
}arr[50005];
int ans[50005];
int f[205][205];

void floyd(int bridge) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (f[i][bridge] != INT_MAX && f[bridge][j] != INT_MAX && f[i][j] > f[i][bridge] + f[bridge][j]) {
                    f[i][j] = f[i][bridge] + f[bridge][j];
                }
            }
        }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>t[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            edge[i][j]=INT_MAX;
        }
    }
    for(int i=1;i<=m;i++){
        int u,v,len;
        cin>>u>>v>>len;
        u++,v++;
        edge[u][v]=edge[v][u]=len;
    }
    cin>>k;
    for(int i=1;i<=k;i++){
        cin>>arr[i].a>>arr[i].b>>arr[i].t;
        arr[i].a++,arr[i].b++;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            f[i][j]=INT_MAX;
        }
    }
    int l=1;
    for(int i=1;i<=k;i++){
        //int flag=1;
        while(t[l]<=arr[i].t&&l<=n){
            //flag=0;
            for(int j=1;j<l;j++){
                f[l][j]=f[j][l]=edge[l][j];
            }
            floyd(l);
            l++;
        }
        //cout<<i<<' '<<l<<' '<<arr[i].a<<' '<<arr[i].b<<endl;
//        if(flag==0){
//            for (int bridge = 1; bridge < l; bridge++) {
//                for (int i = 1; i <= n; i++) {
//                    for (int j = 1; j <= n; j++) {
//                        if (f[i][bridge] != INT_MAX && f[bridge][j] != INT_MAX && f[i][j] > f[i][bridge] + f[bridge][j]) {
//                            f[i][j] = f[i][bridge] + f[bridge][j];
//                        }
//                    }
//                }
//            }
//        }
        if(f[arr[i].a][arr[i].b]==INT_MAX){
            cout<<-1<<endl;
            continue;
        }
        else{
            cout<<f[arr[i].a][arr[i].b]<<endl;
        }
    }
    return 0;
}
