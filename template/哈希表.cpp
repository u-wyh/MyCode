#include<iostream>
#include<vector>

#define mod 233333

int n,x,ans;
vector<int>linker[mod+2];

inline void insert(int x){
    for(int i=0;i<linker[x%mod].size();i++){
        if(linker[x%mod][i]==x){
            return ;
        }
    }
    linker[x%mod].push_back(x);
    ans++;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>x;
        insert(x);
    }
    cout<<ans;
    return 0;
}
