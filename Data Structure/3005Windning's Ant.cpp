#include <cstdio>
#include <iostream>
using namespace std;
int main(){
	int n,l,v,dir;
	cin>>n>>l>>v;
	double *pos=new double[n];
	double time=0,tmp;
	for (int i=0;i<n;++i) cin>>pos[i];
	for (int i=0;i<n;++i){
		cin>>dir;
		if (dir==0) tmp=pos[i]/v;
		else tmp=(l-pos[i])/v;
		time=(time>tmp)?time:tmp;
	}
	printf("%.3f\n",time);
	return 0;
}