#include <iostream>
using namespace std;
int main(){
	int num,i,times,root;
	int tmp[512][3]={0};
	int ever[1024]={0};
	cin>>num;
	int *tree=new int[num];
	times=num/2;
	for (int j=0;j<times;++j){
		cin>>tmp[j][0]>>tmp[j][1]>>tmp[j][2];
		++ever[tmp[j][0]];
		++ever[tmp[j][1]];
		++ever[tmp[j][2]];
	}
	for (i=0;i<times;++i){
		if (ever[tmp[i][0]]==1){
			root=tmp[i][0];
			break;
		}
	}
	tree[1]=root;
	int point=0;
	for (i=1;i<=times;++i){
		for (int j=0;j<times;++j){
			if (tree[i]==tmp[j][0]){
				point=j;
				break;
			}
		}
		tree[2*i]=tmp[point][1];
		tree[2*i+1]=tmp[point][2];
	}
	for (i=1;i<=num;++i) cout<<tree[i]<<endl;
	return 0;
}