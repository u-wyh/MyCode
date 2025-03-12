#include<bits/stdc++.h>
using namespace std;

int n;
int value[260],winner[260];

void dfs(int x){
    if(x>=(1<<n))
        return ;
    else{
        dfs(2*x);
        dfs(2*x+1);
        int l=value[2*x],r=value[2*x+1];
        if(l>r){
            value[x]=l;
            winner[x]=winner[2*x];
        }else{
            value[x]=r;
            winner[x]=winner[2*x+1];
        }
    }
}

int main()
{
    cin>>n;
    for(int i=0;i<(1<<n);i++){
        cin>>value[i+(1<<n)];
        winner[i+(1<<n)]=i+1;
    }
    dfs(1);
    cout<<winner[1]<<endl<<value[winner[1]-1+(1<<n)]<<endl;
    cout<<(value[2]>value[3]?winner[3]:winner[2])<<endl<<value[value[2]>value[3]?winner[3]:winner[2]-1+(1<<n)]<<endl;
    return 0;
}
