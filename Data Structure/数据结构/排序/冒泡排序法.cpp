template <class T>
void bubbleSort(T a[],int size){
	int i,j;
	T tmp;
	bool flag;
	for (i=1;i<size;++i){
		flag=false;
		for (j=0;j<size-i;++j){
			if (a[j+1]<a[j]){
				tmp=a[j];
				a[j]=a[j+1];
				a[j+1]=tmp;
				flag=true;
			}
		}
		if (!flag) break;
	}
}