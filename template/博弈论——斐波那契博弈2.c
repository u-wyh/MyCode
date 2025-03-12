#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000000000000000LL
#define MAXM 101

long long fi[MAXM];
int size;

void build(){
    fi[0]=1;
    fi[1]=2;
    size=1;
    while (fi[size] <= MAXN) {
        fi[size + 1] = fi[size] + fi[size - 1];
        size++;
    }
}

long long bs(long long n){
    int l=0,r=size,mid;
    long long ans=-1;
    while(l<=r){
        mid=l+((r-l)>>1);
        if(fi[mid]<=n){
            ans=fi[mid];
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    return ans;
}

long long compute(long long n){
    long long ans=-1,find;
    while(n!=1&&n!=2){
        find=bs(n);
        if(find==n){
            ans=n;
            break;
        }else{
            n-=find;
        }
    }
    if (ans != -1) {
        return ans;
    } else {
        return n;
    }
}

int main()
{
    build();
    long long n;
    scanf("%lld",&n);
    printf("%lld\n",compute(n));
    return 0;
}
