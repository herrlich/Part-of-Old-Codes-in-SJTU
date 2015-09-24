#include <iostream>
using namespace std;
int main()
{
	int n,**p,i,k,j;
	cout<<"ÇëÊäÈëÐÐÊýn"<<endl;
	cin>>n;
	p=new int *[n];
	for (i=0;i<n;++i){
		p[i]=new int [n];
	}
	for (i=0;i<n;++i){
		p[i][0]=1;
		p[i][i]=1;
		if (i>=2){
			for (k=1;k<i;++k){
				p[i][k]=p[i-1][k-1]+p[i-1][k];
			}
		}
	}

	for (i=0;i<n;++i){
		for (k=0;k<n-i;++k){
			cout<<' ';
		}
		for (j=0;j<i+1;++j){
			cout<<p[i][j]<<' ';
		}
		cout<<'\n';
	}
	for (i=0;i<n;++i) delete [] p[i];
	delete [] p;
	return 0;
}