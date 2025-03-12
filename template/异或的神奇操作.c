//求出一个数组中只有两个数出现奇数次，剩下的数全部出现偶数次，返回这两个数字
#include<stdio.h>

int main()
{
    int t;
    scanf("%d",&t);
    int arr[t];
    int eor1=0,eor2=0;
    for(int i=0;i<t;i++)
    {
        scanf("%d",&arr[i]);
        eor1=eor1^arr[i];
    }
    //既然所有的数字都会出现偶数次（除了我们要求的数字），那么它们异或后的结果就是出现了奇数次的两个数字异或的结果

    int rightone=eor1&(-eor1);
    //这两个出现奇数次的的数字必然不一样，那么它们异或后的二进制结果中必然有一个一，rightone就是最右边的那个一
    /*
    求最右边的一原理是
        比如                    a=0010111
        将a取反                ~a=1101000
        然后加一（如果这一位上是0，则说明原来是1，那么加上一后，异或后的结果就是1，即为所求
                  如果是1，则说明原来是0，那么加上1后，会进位到下一个数，直至出现0为止，即为所求）
        而取反后加上1正是它的负数
        所以我们这么求rightone
    */
    for(int i=0;i<t;i++)
    {
        if((arr[i]&rightone)==0)//rightone二进位制表达是只有一个一，其余位置都是0
            //如果数字二进位制上有和rightone一样位置的1，那么它的结果就不是0
            eor2=eor2^arr[i];
            //eor2是在rightone位置上有1的所有数字和的异或，可以求出一个值
    }
    printf("%d %d\n",eor2,eor2^eor1);
    //eor1=a^b  a(或者b)=eor2  所以b(或者a)=eor2^eor1=a^b^a=a^a^b
    return 0;
}
