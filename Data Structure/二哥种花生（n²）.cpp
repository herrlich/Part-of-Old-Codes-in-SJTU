#include <iostream>
using namespace std;
int A[1001][1001]={0},S[1001][1001]={0};
int main()
{
	int i,j,L,W,a,b,sum,max=0;
	cin>>L>>W;
	for (i=1;i<L+1;++i){
		for (j=1;j<W+1;++j){
			cin>>A[i][j];
		}
	}
	cin>>a>>b;
	for (i=1;i<L+1;++i){
		for (j=1;j<W+1;++j){
			S[i][j]=S[i][j-1]+S[i-1][j]-S[i-1][j-1]+A[i][j];
		}
	}
	for (i=1;i<=L+1-a;++i){
		for (j=1;j<=W+1-b;++j){
			sum=S[i+a-1][j+b-1]+S[i-1][j-1]-S[i-1][j+b-1]-S[i+a-1][j-1];
			max=(max>sum)?max:sum;
		}
	}
	cout<<max<<endl;
	return 0;
}