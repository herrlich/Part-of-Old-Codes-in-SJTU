#include <iostream>
using namespace std;
int main(){
	int num,sum=0,i,tmp;
	cin>>num;
	for (i=0;i<num;++i){
		cin>>tmp;
		sum+=tmp;
	}
	cout<<sum<<endl;
	return 0;
}