//不允许重复使用的背包问题
#include<iostream>  
#include<algorithm>  
using namespace std;
struct node{
	int weight;
	int value;
	node() {weight=0;value=0;}
};
int cmp(const node &n1,const node &n2){
	if (n1.weight>n2.weight) return 0;
	else return 1;
}
int main(){
	int n,limited_weight,i,w,j;
	cout<<"请输入类型数:"<<endl;
	cin>>n;
	cout<<"请输入允许携带的最大重量:"<<endl;
	cin>>limited_weight;
	node *bag=new node[n+1];
	cout<<"请分别输入每组的重量和价值:"<<endl;
	for (i=1;i<=n;++i) cin>>bag[i].weight>>bag[i].value;
	sort(bag,bag+n,cmp);
	int **sum=new int*[limited_weight+1];
	for (i=0;i<limited_weight+1;++i) sum[i]=new int[n+1];
	for(i=0;i<limited_weight+1;++i){
		for (j=0;j<n+1;++j){
			sum[i][j]=0;
		}
	}
	for (i=1;i<=n;++i){
		for (w=1;w<=limited_weight;++w){
			if (bag[i].weight>w) sum[w][i]=sum[w][i-1];
			else sum[w][i]=max(sum[w][i-1],sum[w-bag[i].weight][i-1]+bag[i].value);
		}
	}
	cout<<sum[limited_weight][n]<<endl;
	delete [] bag;
	for (i=0;i<limited_weight+1;++i) delete [] sum[i];
	delete [] sum;
	return 0;
}