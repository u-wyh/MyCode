//求出比原数组大的最小的2的幂次方数组
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

int main()
{
    int t;
    scanf("%d",&t);
    int arr[t];
    srand(time(NULL));
    for(int i=0;i<t;i++)
    {
        arr[i]=rand()%100;
        printf("%4d",arr[i]);
    }
    //生成随机数
    printf("\n");
    for(int i=0;i<t;i++)
    {
        arr[i]-=1;
        arr[i]|=arr[i]>>1;
        arr[i]|=arr[i]>>2;
        arr[i]|=arr[i]>>4;
        arr[i]|=arr[i]>>8;
        arr[i]|=arr[i]>>16;
        printf("%4d",arr[i]+1);
    }
    /*
    原理解释：
    既然是2的幂次方，那么他们的二进制上必然只有一个一存在。
    他们是int型的数字，那么他们的二进制最多不会超过32位
    因为是按位或运算，那么是有一为一
    我们的目的是让这个数的二进位制上的最左边的1以右所有数字都是1（包括它本身），然后加上1，使之进位
    首先要先减去1，因为这个数如果本身就是2的幂次方，那么会有问题
    然后使他按位或运算
    最后加一，达成目的；
    */
    return 0;
}
