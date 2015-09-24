#include <iostream>
using namespace std;
int main(){
	int N,i,j,x;
	cin>>N;
	int **array,*num;
	num=new int[200];
	array=new int*[N];
	for (i=0;i<N;++i){
		cin>>num[i];
		array[i]=new int[201];
		array[i][0]=0;
	}
	for (i=0;i<N;++i){
		for (j=0;j<num[i];++j){
			cin>>x;
			array[i][x]=1;
		}
	}
	int times,a,b;
	char op;
	cin>>times;
	for (i=0;i<times;++i){
		cin>>op;
		cin>>a>>b;
		if (op=='+'){
			for (j=0;j<=200;++j){
				if (array[b-1][j]==1) array[a-1][j]=1;
			}
		}
		if (op=='-'){
			for (j=0;j<=200;++j){
				if (array[b-1][j]==1&&array[a-1][j]==1) array[a-1][j]=0;
			}
		}
		if (op=='*'){
			for (j=0;j<=200;++j){
				if (array[b-1][j]==1&&array[a-1][j]==1) array[a-1][j]=1;
				else array[a-1][j]=0;
			}
		}
	}
	for (i=0;i<N;++i){
		for (j=0;j<=200;++j){
			if (array[i][j]==1) cout<<j<<' ';
		}
		cout<<endl;
	}
	for (i=0;i<N;++i) delete [] array[i];
	delete [] array;
	delete num;
	return 0;
}