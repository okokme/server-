/*设计一个算法，实现将一维数组A（下标从1开始）中的元素循环右移k位，要求只用一个元素大小的辅助空间，并给出算法的时间复杂度。*/

void change( char A[], int len, int k)
{
    int i,j;
    int t;
    for(i=0; i<k; i++)
    {
        t = a[size - 1];
        for(j=size-1; j>0; j--)
        {
            a[j] = a[j-1];
        }
        a[0] = t;
    }
}
