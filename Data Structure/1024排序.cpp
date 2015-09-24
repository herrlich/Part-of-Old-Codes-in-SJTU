#include <iostream>
#include <algorithm>//偷懒直接用stl，要不然用各种排序都行~
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