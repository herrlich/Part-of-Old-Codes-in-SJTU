#include <iostream>
#include <algorithm>//͵��ֱ����stl��Ҫ��Ȼ�ø���������~
using namespace std;
int main(){
	int n,*array;
	cin>>n;
	array=new int[n];
	for (int i=0;i<n;++i) cin>>array[i];
	sort(array,array+n);
	for (int i=0;i<n;++i) cout<<array[i]<<' ';
	return 0;
}