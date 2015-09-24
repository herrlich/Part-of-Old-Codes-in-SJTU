template <class T>
void heapSort(T a[],int size){
	int i;
	T tmp;
	for (int i=size/2-1;i>=0;i--) percolateDown(a,i,size);//创建初始的堆
	for (i=size-1;i>0;--i){
		tmp=a[0];
		a[0]=a[i];
		a[i]=tmp;
		percolateDown(a,0,i);
	}
}
template <class T>
void percolateDown(T a[],int hole,int size){
	int child;
	T tmp=a[hole];
	for (;hole*2+1<size;hole=child){
		child=hole*2+1;
		if (child!=size-1&&a[child+1]>a[child]) child++;
		if (a[child]>tmp) a[hole]=a[child];
		else break;
	}
	a[hole]=tmp;
}