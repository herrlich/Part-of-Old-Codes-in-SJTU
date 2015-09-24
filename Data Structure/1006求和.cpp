#include <iostream>
using namespace std;
int main(){
	int n,*a,max=0,temp=0,i;
	cin>>n;
	a=new int[n];
	for (i=0;i<n;++i) cin>>a[i];
	for (i=0;i<n-1;++i){
		if (temp==0){
			if (a[i]>=0) temp=a[i];
			else continue;
		}
		temp=(temp+a[i+1]>0)?temp+a[i+1]:0;
		max=(temp>max)?temp:max;
	}
	if (max>0) cout<<max<<endl;
	else cout<<"Game Over"<<endl;
	delete [] a;
	return 0;
}