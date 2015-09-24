template <class T>
void simpleInsertSort(T a[],int size){
	int j;
	T tmp;
	for (int i=1;i<size;++i){
		tmp=a[i];
		for (j=i-1;tmp<a[j]&&j>=0;--j) a[j+1]=a[j];
		a[j+1]=tmp;
	}
}