//P6464
#include<bits/stdc++.h>
using namespace std;

int n,m;
int F[105][105];
int f[105][105];

void floyd() {
    for (int bridge = 1; bridge <= n; bridge++) { // Ìø°å
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (f[i][bridge] != INT_MAX && f[bridge][j] != INT_MAX && f[i][j] > f[i][bridge] + f[bridge][j]) {
                    f[i][j] = f[i][bridge] + f[bridge][j];
                }
            }
        }
    }
}

inline void restore(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            F[i][j]=f[i][j];
        }
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            f[i][j]=INT_MAX;
            F[i][j]=INT_MAX;
        }
        f[i][i]=0;
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        f[u][v]=w;
        f[v][u]=w;
    }
    floyd();
    long long ans=LLONG_MAX;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            restore();
            F[i][j]=F[j][i]=0;
            for(int x=1;x<=n;x++){
                for(int y=1;y<=n;y++){
                    if(F[x][y]>F[x][i]+F[i][y]){
                        F[x][y]=F[x][i]+F[i][y];
                    }
                    if(F[x][y]>F[x][j]+F[j][y]){
                        F[x][y]=F[x][j]+F[j][y];
                    }
                }
            }
//            }
//            for(int x=1;x<=n;x++){
//                for(int y=1;y<=n;y++){
//                    if(F[x][y]>F[x][j]+F[j][y]){
//                        F[x][y]=F[x][j]+F[j][y];
//                    }
//                }
//            }
            long long res=0;
            for(int i=1;i<=n;i++){
                for(int j=i+1;j<=n;j++){
                    res+=F[i][j];
                }
            }
            ans=min(ans,res);
        }
    }
    cout<<ans<<endl;
    return 0;
}
