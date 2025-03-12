#include<stdio.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>

#define max 10001

static int first;
static int last;
static int arr[max];

void swap(int i, int j) ;
void partition(int l, int r,int  x);
void quicksort(int l,int r);

int main()
{
    int t;
    scanf("%d",&t);
    srand(time(NULL));
    for(int i=0;i<t;i++)
    {
        arr[i]=rand()%100+1;
        printf("%4d",arr[i]);
    }
    printf("\n");//定义并输出所有的数组

    quicksort(0,t-1);//开始进行快速排序

    for(int i=0;i<t;i++)
    {
        printf("%4d",arr[i]);
    }//输出排列好的数组

    return 0;
}

void swap(int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}//交换指定下标的两个数字

void partition(int l, int r,int  x)
{
    first = l;
    last = r;
    int i = l;
    while (i <= last) {
        if (arr[i] == x) {
            i++;
        } else if (arr[i] < x) {
            swap(first++, i++);
        } else {
            swap(i, last--);
        }
    }
}//实现快排的主要程序

void quicksort(int l,int r)
{
    if(l>=r)
        return ;
    int x = arr[l + rand()%(r-l+1)];
    partition(l, r, x);
    int left=first;
    int right=last;
    quicksort(l, left - 1);
    quicksort(right + 1, r);
}//使用递归进行快排
