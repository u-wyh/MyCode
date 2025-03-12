#include<bits/stdc++.h>
using namespace std;

int n;
char str[1000];
int nums[30],enter[30];
int r=0,st[1000];

int main()
{
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>str[i];
        nums[str[i]-'a']++;
    }
    for(int i=0;i<26;i++)
        printf("%3d",nums[i]);
    printf("\n");
    for(int i=0;i<n;i++){
        if(!enter[str[i]-'a']){
            while(r>0&&nums[str[st[r-1]]-'a']>0&&str[st[r-1]]>str[i]){
                enter[str[st[r-1]]-'a']=0;
                r--;
            }
            st[r++]=i;
            enter[str[i]-'a']=1;
        }
        nums[str[i]-'a']--;
    }
    for(int i=0;i<r;i++)
        cout<<str[st[i]];
    return 0;
}
