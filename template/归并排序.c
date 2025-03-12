#include<stdio.h>

static int arr[20];
static int help[20];

void merge(int mid,int left ,int right)
{
    int i=left;
    int a=left;
    int b=mid+1;
    while(a<=mid&&b<=right)
        help[i++]=arr[a]<=arr[b]?arr[a++]:arr[b++];
    while(a<=mid)
        help[i++]=arr[a++];
    while(b<=right)
        help[i++]=arr[b++];
    for(i=left;i<=right;i++)
    {
        arr[i]=help[i];
    }
}
//该函数可以实现数组的归并
void mergesort2() {
    // 一共发生O(logn)次
    int n=20;//在这种方法中，n所有元素的个数，不是下标。
    for (int l, m, r, step = 1; step < n; step <<= 1) {
    // 内部分组merge，时间复杂度O(n)
        l = 0;
        while (l < n) {
            m = l + step - 1;//其实这里的m是根据l和r的表达式得来的
            if (m + 1 >= n) {
                break;//这里表示剩下的数字数量不足以进行下一个比较，就是说不到step个数字
            }
            r = (l + (step << 1) - 1)> (n - 1)?(n-1):(l + (step << 1) - 1);
            merge(m,l, r);
            l = r + 1;
        }
    }
}
//该函数不使用递归方法
/*void mergesort(int left,int right)
{
    if(left==right)
        return ;
    int mid=(left+right)/2;
    mergesort(left,mid);
    mergesort(mid+1,right);
    merge(mid,left,right);
}*/
//该函数是使用用递归方法进行归并排序
int main()
{
    for(int i=0;i<20;i++)
    {
        scanf("%d",&arr[i]);
    }
    //mergesort(0,19);
    mergesort2();
    for(int i=0;i<20;i++)
    {
        printf("%4d",arr[i]);
    }
    return 0;
}
