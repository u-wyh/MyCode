#include<stdio.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>
#define max 10001
void swap(int i, int j) ;
static int arr[max];
int partition(int l, int r,int  x);
void quicksort(int left,int right);
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
    printf("\n");
    quicksort(0,t-1);

    for(int i=0;i<t;i++)
    {
        printf("%4d",arr[i]);
    }
    return 0;
}
void swap(int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int partition(int l, int r,int  x)
{
    int a = l,xi=0;
		for (int i = l; i <= r; i++) {
			if (arr[i] <= x) {
				swap(a, i);
            if (arr[a] == x) {
                xi = a;
            }
            a++;
        }
    }
    swap(xi, a - 1);
    return a - 1;
}
void quicksort(int l,int r)
{
    if(l>=r)
        return ;
    int x = arr[l + rand()%(r-l+1)];
    int mid = partition(l, r, x);
    quicksort(l, mid - 1);
    quicksort(mid + 1, r);
}
