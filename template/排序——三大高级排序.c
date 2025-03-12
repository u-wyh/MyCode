#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define Max 100001

static int arr[Max];
static int help[Max];
static int first;
static int last;

void swap(int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int partition(int l, int r,int  x)
{
    int a=l,xi=0;
    for(int i=l;i<=r;i++)
    {
        if(arr[i]<=x)
        {
            swap(a,i);
            if(arr[a]==x)
                xi=a;
            a++;
        }
    }
    swap(xi,a-1);
    return a-1;
}
void quicksort(int l,int r)
{
    if(l>=r)
        return ;
    int x=arr[rand()%(r-l+1)+l];
    int mid=partition(l,r,x);
    quicksort(l,mid-1);
    quicksort(mid+1,r);
}
//随机快速排序原始版本
void partition2(int l, int r,int  x)
{
    first=l;
    last=r;
    int i=l;
    while(i<=last)
    {
        if(arr[i]<x)
            swap(first++,i++);
        else if(arr[i]>x)
            swap(last--,i);
        else
            i++;
    }
}
void quicksort2(int l,int r)
{
    if(l>=r)
        return ;
    int x=arr[rand()%(r-l+1)+l];
    partition2(l,r,x);
    int left=first;
    int right=last;
    quicksort(l,left-1);
    quicksort(right+1,r);
}
//随机快速排序优化后的版本

//以上均为随机快速排序  包括了原始模式和优化后的效果

/*
随机快速排序原理介绍（原始版本和优化后的版本）：
    原始版本：
        我们随机选择一个还没有排好序的下标，然后根据这个下标对应的值将数组分为大于它的和小于等于它的，
        所有的数字小于等于它的放在左边，他自己在这些数字的右边
        然后我们将分为的两类继续以上操作，从而使顺序排好，每次只能排好一个数字
    优化后的版本：
        我们随机选择一个还没有排好序的下标，然后根据这个下标对应的值将数组分为大于它的和小于它的，
        然后我们将分为的两类继续以上操作，从而使顺序排好
        这个是左右同时开始
        优化体现在我们每次选择的不只是那一个数，而是所有值等于这个数的数字，一次至少可以完成一个
*/

void merge(int l,int m,int r)
{
    int a=l;
    int b=m+1;
    int i=l;
    while(a<=m&&b<=r)
        help[i++]=arr[a]<=arr[b]?arr[a++]:arr[b++];
    while(a<=m)
        help[i++]=arr[a++];
    while(b<=r)
        help[i++]=arr[b++];
    for(i=l;i<=r;i++)
        arr[i]=help[i];
}
void mergesort(int l,int r)
{
    if(l>=r)
        return ;
    int m=(l+r)/2;
    mergesort(l,m);
    mergesort(m+1,r);
    merge(l,m,r);
}
void mergesort2(int t)
{
    for(int l,m,r,step=1;step<t;step*=2)
    {
        l=0;
        while(l<t)
        {
            m=l+step-1;
            if(m+1>=t)
                break;
            r=(l+step*2-1)<(t-1)?(l+step*2-1):(t-1);
            merge(l,m,r);
            l=r+1;
        }
    }
}
//以上是归并排序的两种方式，一种是直接递归，另外一种是没有使用递归的方式

/*
归并排序原理介绍（递归和非递归）：
    递归版：
        我们将所有的数字分为两个数组，然后两个数组在各自的递归中实现了有序化，我们将两个有序的数组合并为一个有序的数组
        从而实现排序的功能
    非递归版：
        通过增加步长来实现有序
*/

void heapinsert(int i)
{
    while(arr[i]>arr[(i-1)/2])
    {
        swap(i,(i-1)/2);
        i=(i-1)/2;
    }
}//将堆进行排序    从顶到底
void heapify(int i,int size)
{
    int l=i*2+1;
    while(l<size)
    {
        int best=((l+1)<size&&arr[l+1]>arr[l])?(l+1):l;
        best=arr[best]>arr[i]?best:i;
        if(best==i)
            break;
        swap(best,i);
        i=best;
        l=2*i+1;
    }
}//将堆进行排序    从底到顶
void heapsort1(int t)
{
    for(int i=0;i<t;i++)
    {
        heapinsert(i);
    }
    int size=t;
    while(size>1)
    {
        swap(0,--size);
        heapify(0,size);
    }
}//实现堆排序，每次将第一个数和最后一个数互换，并且减少数字规模，使最大的数独立出来
//这是从顶到底建堆
void heapsort2(int t)
{
    for(int i=t-1;i>0;i--)
    {
        heapify(i,t);
    }
    int size=t;
    while(size>1)
    {
        swap(0,--size);
        heapify(0,size);
    }
}
//以上两种是堆排序的代码实现，一种是从顶到底建堆，另外一种是从底到顶建堆

/*
堆排序原理解释（顶到底 和 底到顶）：
    从顶到底建堆：
        我们在完成一个堆的时候可以选择两种方法，其中第一个就是把新生的数字放在最顶端
    从底到顶建堆：
        我们在完成一个堆的时候可以选择两种方法，其中第二个就是把新生的数字放在最底端
    堆排序的原理是把最大数从最顶端拿下来，因为最大的的数字就在最顶端，把数字拿下来放在数组中之后，把堆的大小减少1
    从而实现数组的有序化
*/
int main()
{
    int t;
    scanf("%d",&t);
    srand(time(NULL));
    int max=0;
    for(int i=0;i<t;i++)
    {
        arr[i]=rand()%100;
        if(max<arr[i])
            max=arr[i];
        printf("%3d",arr[i]);
    }

    printf("\n");

    mergesort(0,t-1);
    //mergesort2(t);
    //quicksort(0,t-1);
    //quicksort2(0,t-1);
    //heapsort1(t);
    //heapsort2(t);
    for(int i=0;i<t;i++)
        printf("%3d",arr[i]);
    return 0;
}
