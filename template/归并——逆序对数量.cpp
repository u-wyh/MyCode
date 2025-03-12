#include<bits/stdc++.h>
using namespace std;
#define int long long

int n;
int arr[500005];
int help[500005];

int mergesort(int l,int r){
    int mid=(l+r)/2;
    if(l==r)
        return 0;
    for(int i=l;i<=r;i++){
        help[i]=arr[i];
    }
    int i=l;
    int j=mid+1;
    int cnt=0;
    for(int k=l;k<=r;k++){
        if(i==mid+1){
            arr[k]=help[j];
            j++;
        }else if(j==r+1){
            arr[k]=help[i];
            i++;
        }else if(help[i]<=help[j]){
            arr[k]=help[i];
            i++;
        }else if(help[j]<help[i]){
            arr[k]=help[j];
            j++;
            cnt+=(mid-i+1);
        }else
            break;
    }
    return cnt;
}

int merge(int l,int r){
    if(l==r)
        return 0;
    int mid=(l+r)/2;
    int ans=0;
    ans+=merge(l,mid);
    ans+=merge(mid+1,r);
    ans+=mergesort(l,r);
    return ans;
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    cout<<merge(1,n);
    return 0;
}
