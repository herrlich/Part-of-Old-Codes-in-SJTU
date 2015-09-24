#include <iostream>
#include <cmath>
using namespace std;
bool check(long int n);
int main(){
	long int num,root[32]={0},i;
	bool run;
	int arraytime[32]={0},count=0,times=1;
	cin>>num;
	long int temp=num;
	while (temp>=2){
		run=true;
		for (i=2;i<=(long int)sqrt((double)temp)+1;++i){
			if ((temp%i==0)&&check(i)){
				root[count]=i;
				++count;
				temp=temp/i;
				run=false;
				break;
			}
		}
		if (run){
			root[count]=temp;
			++count;
			break;
		}
	}
	long int ultimate[32];
	ultimate[0]=root[0];
	arraytime[0]=1;
	for (i=1;i<count;++i){
		if (root[i]==ultimate[times-1]) ++arraytime[times-1];
		else{
			ultimate[times]=root[i];
			arraytime[times]=1;
			++times;
		}
	}
	cout<<num<<'=';
	for (i=0;i<times;++i) cout<<ultimate[i]<<'('<<arraytime[i]<<')';
	cout<<endl;
	return 0;
}
bool check(long int n){
	for (long int j=2;j<n;++j){
		if (n%j==0) return false;
	}
	return true;
}