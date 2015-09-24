#include <iostream>
#include <cstdio>
using namespace std;
int main(){
	long long n,k,sum=1000000001,tmp=0,pos;
	cin>>n>>k;
	int *gold=new int [n];
	for (int i=0;i<n;++i) scanf("%d",&gold[i]);
	for (int i=0;i<n;i+=pos){
		for (int j=0;j<k;++j){
			if (gold[(i+j)%n]>tmp){
				tmp=gold[(i+j)%n];
				pos=j+1;
			}
		}
		if (tmp<sum) sum=tmp;
		tmp=0;
	}
	cout<<sum<<endl;
	delete [] gold;
	return 0;
}