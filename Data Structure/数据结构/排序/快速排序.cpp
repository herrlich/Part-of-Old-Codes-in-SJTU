template <class T>
void quickSort(T a[],int low,int high){
	int mid;
	if (low>=high) return;
	mid=divide(a,low,high);
	quickSort(a,low,mid-1);
	quickSort(a,mid+1,high);
}
template <class T>
void quickSort(T a[],int size){
	quickSort(a,0,size-1);
}
template <class T>
int divide(T a[],int low,int high){
	T k=a[low];
	do{
		while (low<high&&a[high]>=k) --high;
		if (low<high){
			a[low]=a[high];
			++low;
		}
		while (low<high&&a[low]<=k) ++low;
		if (low<high){
			a[high]=a[low];
			--high;
		}
	}while(low!=high);
	a[low]=k;
	return low;
}