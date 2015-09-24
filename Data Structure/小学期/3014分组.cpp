#include <iostream>
using namespace std;
inline int abs(int num){
	return (num>0)?num:-num;
}
void bubble(int a[],int size){
	int i,j,tmp;
	bool flag;
	for (i=1;i<size;++i){
		flag=false;
		for (j=0;j<size-1;++j){
			if (a[j]>a[j+1]){
				tmp=a[j+1];
				a[j+1]=a[j];
				a[j]=tmp;
				flag=true;
			}
		}
		if (!flag) break;
	}
}
int main(){
	int n,boy[1000]={0},girl[1000]={0},total=0;
	cin>>n;
	for (int i=0;i<n;++i) cin>>boy[i];
	for (int i=0;i<n;++i) cin>>girl[i];
	bubble(boy,n);
	bubble(girl,n);
	for (int i=0;i<n;++i) total+=abs(boy[i]-girl[i]);
	cout<<total<<'\n';
	return 0;
}