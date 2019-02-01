
function insertSort(arr)
{
	int len = arr.length;
	int preIndex, current;
	for(int i=1; i<len; i++)
	{
		preIndex = i-1;
		current = arr[i];
		while(preIndex>=0 && current< arr[preIndex])
		{
			arr[preIndex+1] = arr[preIndex];
			preIndex--;
		}
		arr[preIndex+1] = current;
	}
	return arr;
}
