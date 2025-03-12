//P1127
//建图方式比较难  比较独特
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
const int MAXM = 30;

int n;
vector<pair<string,int>>vec[MAXM];//虽然这是有向边  但是string类型不易标记 所以加上一个cnt标记
stack<string>st;

//有向边
int in[MAXM];
int out[MAXM];
bool exist[MAXN];

//判断是否联通
int fa[MAXM];
bool vis[MAXM];

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void dfs(int u){
    for(int i=0;i<vec[u].size();i++){
        if(!exist[vec[u][i].second]){
            exist[vec[u][i].second]=true;
            int len=vec[u][i].first.length();
            int v=vec[u][i].first[len-1]-'a';
            dfs(v);
            st.push(vec[u][i].first);
        }
    }
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
    }
}

int main()
{
    cin>>n;
    for(int i=0;i<=26;i++){
        fa[i]=i;
    }
    int tmp=30;
    for(int i=1;i<=n;i++){
        string str;
        cin>>str;
        int len=str.length();
        int s=str[0]-'a';
        int e=str[len-1]-'a';
        tmp=min(tmp,s);
        vec[s].push_back({str,i});
        in[e]++,out[s]++;
        un(e,s);
        vis[e]=true,vis[s]=true;
    }
    for(int i=0;i<=26;i++){
        if(vis[i]){
            sort(vec[i].begin(),vec[i].end());
        }
    }
    int father=30;
    for(int i=0;i<=25;i++){
        if(vis[i]){
            if(father==30){
                father=find(i);
            }
            else {
                if(father!=find(i)){
                    cout<<"***"<<endl;
                    return 0;
                }
            }
        }
    }
    //执行到了这里 说明最起码都是联通的
    int cnt1=0,cnt2=0,s=26;
    bool flag=true;
    for(int i=0;i<26;i++){
        if(vis[i]){
            if(out[i]-in[i]==1){
                flag=false;
                cnt1++;
                if(s==26){
                    s=i;
                }
            }
            else if(in[i]-out[i]==1){
                flag=false;
                cnt2++;
            }
            else if(out[i]!=in[i]){
                cout<<"***"<<endl;
                return 0;
            }
        }
    }
    if(!flag&&!(cnt1==cnt2&&cnt1==1)){
        cout<<"***"<<endl;
        return 0;
    }
    if(s==26){
        s=tmp;
    }
    dfs(s);
    cout<<st.top();
    st.pop();
    while(!st.empty()){
        cout<<'.'<<st.top();
        st.pop();
    }
    return 0;
}
