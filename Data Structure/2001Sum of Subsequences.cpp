#include <iostream>
using namespace std;
int main(){
	int num,i,j,k,t,times;
	cin>>num;
	int *array1=new int[num];
	for (i=0;i<num;++i) cin>>array1[i];
	cin>>times;
	int *array2=new int[times];
	for (i=0;i<times;++i){
		int sum=0;
		cin>>j>>k;
		for (t=j-1;t<=k-1;++t) sum+=array1[t];
		array2[i]=sum;
	}
	for (i=0;i<times;++i) cout<<array2[i]<<endl;
	delete [] array1;
	delete [] array2;
	return 0;
}