#include<bits/stdc++.h>
using namespace std;

const int goal[6][6]={
    {0,0,0,0,0,0},
    {0,1,1,1,1,1},
    {0,0,1,1,1,1},
    {0,0,0,2,1,1},
    {0,0,0,0,0,1},
    {0,0,0,0,0,0}
};

int arr[6][6];
int walk[8][2]={{2,1},{2,-1},{1,2},{-1,2},{-2,1},{-2,-1},{1,-2},{-1,-2}};
int ans;
int stx,sty;

int predict(){
    int cnt=0;
    for(int i=1;i<=5;i++){
        for(int j=1;j<=5;j++){
            if(arr[i][j]!=goal[i][j]){
                cnt++;
            }
        }
    }
    if(cnt){
        cnt--;
    }
    return cnt;
}

bool IDAdfs(int x,int y,int t){
    int pre=predict();
    if(pre+t>ans){
        return false;
    }
    if(pre==0){
        return true;
    }
    for(int i=0;i<8;i++){
        int nx=x+walk[i][0];
        int ny=y+walk[i][1];
        if(nx<=0||nx>5||ny<=0||ny>5){
            continue;
        }

        arr[x][y]=arr[nx][ny];
        arr[nx][ny]=2;

        if(IDAdfs(nx,ny,t+1)){
            return true;
        }

        arr[nx][ny]=arr[x][y];
        arr[x][y]=2;
    }
    return false;
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        for(int i=1;i<=5;i++){
            for(int j=1;j<=5;j++){
                char c;
                cin>>c;
                if(c=='*'){
                    arr[i][j]=2;
                    stx=i,sty=j;
                }
                else{
                    arr[i][j]=c-'0';
                }
            }
        }
        ans=predict();
        while(!IDAdfs(stx,sty,0)){
            ans++;
            if(ans>15){
                ans=-1;
                break;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
