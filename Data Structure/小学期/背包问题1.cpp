//�����ظ�ʹ�õı�������
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
	int n,limited_weight,i,w;
	cout<<"������������:"<<endl;
	cin>>n;
	cout<<"����������Я�����������:"<<endl;
	cin>>limited_weight;
	node *bag=new node[n];
	cout<<"��ֱ�����ÿ��������ͼ�ֵ:"<<endl;
	for (i=0;i<n;++i) cin>>bag[i].weight>>bag[i].value;
	sort(bag,bag+n,cmp);
	int *sum=new int[limited_weight+1];
	for(i=0;i<limited_weight+1;++i) sum[i]=0;
	for (w=1;w<=limited_weight;++w){
		for (i=0;i<n&&bag[i].weight<=w;++i){
			sum[w]=max(sum[w],sum[w-bag[i].weight]+bag[i].value);
		}
	}
	cout<<sum[limited_weight]<<endl;
	delete [] bag;
	delete [] sum;
	return 0;
}