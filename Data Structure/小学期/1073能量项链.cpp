#include <iostream>
#include <algorithm>
using namespace std;
int main(){
	int n,i,j,k,s;
	cin>>n;
	long int necklace[101],energy[101][101]={0},sum=0;
	for (i=0;i<n;++i) cin>>necklace[i];
	for (s=1;s<n;++s){
		for (i=0;i<n;++i){
			j=(i+s)%n;
			for (k=i;k<i+s;++k){
				energy[i][j]=max(energy[i][j],energy[i][k%n]+energy[(k+1)%n][j]+necklace[i]*necklace[(k+1)%n]*necklace[(j+1)%n]);
			}
		}
	}
	for (i=0;i<n;++i) sum=(sum>energy[i][(i+n-1)%n])?sum:energy[i][(i+n-1)%n];
	cout<<sum<<endl;
	return 0;
}