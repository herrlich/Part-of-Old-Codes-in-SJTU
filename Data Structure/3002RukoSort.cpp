#include <iostream>
using namespace std;
int main(){
	int n,a[100],i,j,b[100],count=0,temp;
	bool go;
	cin>>n;
	for (i=0;i<n;++i){
		cin>>a[i];
	}
	for (i=0;i<n;++i){
		go=false;
		for (j=i+1;j<n;++j){
			if (a[j]==a[i]) go=true;
		}
		if (!go){
			b[count]=a[i];
			++count;
		}
	}
	bool flag;
	for (i=1;i<count;++i){
		flag=false;
		for (j=0;j<count-i;++j){
			if (b[j]>b[j+1]){
				temp=b[j];
				b[j]=b[j+1];
				b[j+1]=temp;
				flag=true;
			}
		}
		if (!flag) break;
	}
	cout<<count<<endl;
	for (i=0;i<count;++i) cout<<b[i]<<' ';
	return 0;
}