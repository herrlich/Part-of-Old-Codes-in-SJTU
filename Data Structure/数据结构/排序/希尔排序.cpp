template <class T>
void shellSort(T a[],int size){
	int step,i,j;
	T tmp;
	for (step=size/2;step>0;step/=2){
		for (i=step;i<size;++i){
			tmp=a[i];
			for (j=i-step;j>=0&&a[j]>tmp;j-=step) a[j+step]=a[j];
			a[j+step]=tmp;
		}
	}
}