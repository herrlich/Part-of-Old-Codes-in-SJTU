#include <iostream>
#include <cmath>
using namespace std;
int post(long int ini,int array[]);
int main(){
	int n,*array,x,y,z;
	long int *sit;
	cin>>n;
	double node=pow(2,(double)16);
	long int high=node;
	array=new int[high];
	sit=new long int[n];
	for (long int t=0;t<high;++t) array[t]=-1;
	for (int t=0;t<n;++t) sit[t]=0;
	long int pos;
	array[1]=1;
	sit[0]=1;
	for (int i=0;i<n;++i){
		pos=0;
		cin>>x>>y>>z;
		for (long int j=0;j<high;++j){
			if (array[j]==x){
				pos=j;
				break;
			}
		}
		sit[x-1]=pos;
		array[2*pos]=y;
		array[2*pos+1]=z;
	}
	for (i=0;i<n;++i) cout<<sit[i]<<' ';
	cout<<endl;
	post(1,array);
	cout<<endl;
	delete array;
	delete sit;
	return 0;
}
int post(long int ini,int array[]){
	if (array[ini]==-1) return 0;
	if (array[2*ini]==-1&&array[2*ini+1]==-1){
		cout<<array[ini]<<' ';
	}
	else {
		post(2*ini,array);
		post(2*ini+1,array);
		cout<<array[ini]<<' ';
	}
	return 0;
}