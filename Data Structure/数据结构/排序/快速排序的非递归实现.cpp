template <class T>
void quickSort(T a[],int low,int high){//此程序主要运用了模拟一个栈的思想
	if (low>=high) return;
	int mid,l,h,p=0;
	int *s=new int[high-low+1];
	s[p++]=low;
	s[p++]=high;
	while (p>0){
		h=s[--p];
		l=s[--p];
		if (l>=h) break;
		mid=divide(a,l,h);
		if (mid-l>h-mid){
			s[p++]=l;
			s[p++]=mid-1;
			if (h>mid){
				s[p++]=mid+1;
				s[p++]=h;
			}
		}
		else{
			s[p++]=mid+1;
			s[p++]=h;
			if (mid>l){
				s[p++]=l;
				s[p++]=mid-1;
			}
		}
	}
	delete [] s;
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