//P1439
#include<iostream>
#include<cstdio>
using namespace std;

int a[100001],b[100001],map[100001],f[100001];

int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        map[a[i]]=i;
    }
	for(int i=1;i<=n;i++){
        scanf("%d",&b[i]);
        f[i]=0x7fffffff;
    }
	int len=0;
	f[0]=0;
	for(int i=1;i<=n;i++){
		int l=0,r=len,mid;
		if(map[b[i]]>f[len])
            f[++len]=map[b[i]];
		else{
            while(l<r){
                mid=(l+r)/2;
                if(f[mid]>map[b[i]])
                    r=mid;
                else
                    l=mid+1;
            }
            f[l]=min(map[b[i]],f[l]);
     	}
    }
    cout<<len;
    return 0;
}
