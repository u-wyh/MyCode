#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXK = 1000;

int n,k;
struct Candidate{
    int val,cnt;
}cand[MAXK];
int arr[MAXN];

void update(int num){
    for(int i=1;i<k;i++){
        if(cand[i].val==num){
            cand[i].cnt++;
            return ;
        }
    }
    for(int i=1;i<k;i++){
        if(cand[i].cnt==0){
            cand[i].val=num;
            cand[i].cnt++;
            return ;
        }
    }
    for(int i=1;i<k;i++){
        if(cand[i].cnt>0)
            cand[i].cnt--;
    }
}

void check(){
    for(int i=1,real;i<k;i++){
        real=0;
        if(cand[i].cnt>0){
            int cur=cand[i].val;
            for(int j=1;j<=n;j++){
                if(arr[j]==cur){
                    real++;
                }
            }
            if(real<=n/k){
                cand[i].cnt=0;
            }
        }
    }
}

int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    for(int i=1;i<=n;i++){
        update(arr[i]);
    }
    for(int i=1;i<k;i++){
        printf("%3d %3d\n",cand[i].val,cand[i].cnt);
    }
    check();
    for(int i=1;i<k;i++){
        if(cand[i].cnt){
            printf("%3d",cand[i].val);
        }
    }
    return 0;
}

//int n;
//int arr[MAXN],cand,hp;
//
//int main()
//{
//    cin>>n;
//    for(int i=1;i<=n;i++){
//        cin>>arr[i];
//    }
//    for(int i=1;i<=n;i++){
//        if(hp==0){
//            cand=arr[i];
//            hp=1;
//        }else if(arr[i]!=cand){
//            hp--;
//        }else if(cand==arr[i]){
//            hp++;
//        }
//    }
//    if(hp==0){
//        cout<<"there is no water-king"<<endl;
//        return 0;
//    }
//    int cnt=0;
//    for(int i=1;i<=n;i++){
//        if(arr[i]==cand){
//            cnt++;
//        }
//    }
//    if(cnt*2>n){
//        cout<<"the water-king is :"<<cand<<endl;
//    }else{
//        cout<<"there is no water-king"<<endl;
//    }
//    return 0;
//}
