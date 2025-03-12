#include<bits/stdc++.h>
using namespace std;

int n;
int nums[100];

void swap1(int i,int j){
    int tmp=nums[i];
    nums[i]=nums[j];
    nums[j]=tmp;
}

int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>nums[i];
    for(int odd=1,even=0;odd<n&&even<n;){
        if((nums[n-1]&1)==1){
            swap1(n-1,even);
            even+=2;
        }else{
            swap1(n-1,odd);
            odd+=2;
        }
    }
    for(int i=0;i<n;i++)
        printf("%3d",nums[i]);
    return 0;
}
