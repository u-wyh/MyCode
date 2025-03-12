#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000;

int n;
int indegree[MAXN];
int favorite[MAXN];
int deep[MAXN];
queue<int >q;

int main()
{
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>favorite[i];
        indegree[favorite[i]]++;
    }
    for(int i=0;i<n;i++){
        if(indegree[i]==0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        int Next=favorite[cur];
        deep[Next]=max(deep[Next],deep[cur]+1);
        if(--indegree[Next]==0){
            q.push(indegree[Next]);
        }
    }

    // 可能性1 : 所有小环(中心个数 == 2)，算上中心点 + 延伸点，总个数
    int sumOfSmallRings = 0;
    // 可能性2 : 所有大环(中心个数 > 2)，只算中心点，最大环的中心点个数
    int bigRings = 0;
    for (int i = 0; i < n; i++) {
        // 只关心的环！
        if (indegree[i] > 0) {
            int ringSize = 1;
            indegree[i] = 0;
            for (int j = favorite[i]; j != i; j = favorite[j]) {
                ringSize++;
                indegree[j] = 0;
            }
            if (ringSize == 2) {
                sumOfSmallRings += 2 + deep[i] + deep[favorite[i]];
            } else {
                bigRings = max(bigRings, ringSize);
            }
        }
    }
    cout<<max(sumOfSmallRings, bigRings);
    return 0;
}
