template <class T>
void simpleSelectSort(T a[],int size){
	int i,j,k;
	T tmp;
	for (i=0;i<size-1;++i){
		k=i;
		for (j=i+1;j<size;++j){
			if (a[j]<a[i]) k=j;
		}
		tmp=a[i];
		a[i]=a[k];
		a[k]=tmp;
	}
}