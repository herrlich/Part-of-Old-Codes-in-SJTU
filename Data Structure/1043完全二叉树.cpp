#include <iostream>
using namespace std;
int array[1000001]={0};
int tree[1000001]={0};
int main(){
	int num,i,tmp;
	bool flag=true;
	cin>>num;
	array[0]=1;
	for (i=0;i<num-1;++i){
		cin>>tmp;
		if (2*tree[tmp]+1>1000000){
			cout<<"false"<<endl;
			return 0;
		}
		if (array[2*tree[tmp]+1]==0){
			array[2*tree[tmp]+1]=1;
			tree[i+1]=2*tree[tmp]+1;
		}
		else{
			array[2*tree[tmp]+2]=1;
			tree[i+1]=2*tree[tmp]+2;
		}
	}
	for (i=0;i<num;++i){
		if (array[i]==0){
			flag=false;
			break;
		}
	}
	if (flag) cout<<"true"<<endl;
	else cout<<"false"<<endl;
	return 0;
}