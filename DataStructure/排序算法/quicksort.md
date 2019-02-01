20 40 50 10 60   

20

#### 快排思想：

第一步：首先从数组的left位置取出该数（20）作为基准（base）参照物。

第二步：从数组的right位置开始向前找，一直找到比（base）小的数。

​		如果找到，将此数赋值给left位置（也就是将10赋值给20），

​		此时数组为：10,40,50,10,60，

​		left和right指针分别指向前后的10

第三步：从数组的left位置向后找，一直找到比（base）大的数，

​		如果找到，将此数值赋值给right的位置（也就是40赋值给10），

​		此时数组为：10，40，50，40，60

​		left和right的指针分别指向前后的40.

第四步：重复第二、第三步直到left与right指针重合。

​		将base替换掉此时重合位置的元素。

​		此时数组值为：10,20,50,40,60，至此完成第一次排序。

第五步：此时20已经嵌入数组的内部，20的左侧一组数都比20小,20的右侧作为一组数都比20大，以20为切入点对左右两边数按照“第一、第二、第三、第四”步骤进行，最终快排大功告成。



#### 性能评估：

* 具有最好的平均性能，但最坏性能是O(n^2).
* 据统计在数据量大于20的时候，快速排序具有最好的性能。

```c
void QuickSort(int a[], int left, int right)
{
    int i = left;
    int j = right;
    int temp = a[left];
    if(left > right)
    	return;
    while(i!=j)
    {
        while(i<j && a[j]>=temp)
        	j--;
        if(j>i)
        	a[i] = a[j]; //a[i]已经赋值给temp，所以直接将a[j]赋值给a[i],赋值完成后a[j],有空位。
        	
        	while(i<j && a[i]<=temp)
        		i++;
        	if(i<j)
        		a[j] = a[i];
    }
    a[i] = temp;//把基准插入,此时i,j已经相等
    QuickSort(a,left,i-1);
    QuickSort(a,i+1,right);
}
int main()
{
    int a[9] = {8,2,6,12,1,9,5,5,10};
    int i;
    QuickSort(a,0,8);
    for(i=0; i<8; i++)
    	printf("%4d",a[i]);
	return 0;
}
```

