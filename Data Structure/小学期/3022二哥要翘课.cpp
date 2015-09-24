#include <iostream>
#include <cstring>
using namespace std;
int a[100000]={0},b[100000]={0},c[100000]={0},d[100000]={0};
char n1[100000],n2[100000],n3[100000];
int main(){
	int n,len1,len2,len3,max,sum,i,t;
	cin>>n;
	n1[0]='1';
	n2[0]='2';
	n3[0]='4';
	for (t=0;t<n-2;++t){
		len1=strlen(n1);
		len2=strlen(n2);
		len3=strlen(n3);
		max=(len1>len2)?len1:len2;
		max=(max>len3)?max:len3;
		for (i=0;i<len1;++i) a[i]=n1[len1-i-1]-'0';
		for (i=0;i<len2;++i) b[i]=n2[len2-i-1]-'0';
		for (i=0;i<len3;++i) c[i]=n3[len3-i-1]-'0';
		for (i=0;i<max;++i) d[i]=0;
		for (i=0;i<max;++i){
			sum=a[i]+b[i]+c[i];
			d[i]+=sum;
			d[i+1]=d[i]/10;
			d[i]%=10;
		}
		if (d[max]!=0) ++max;
		for (i=0;i<len2;++i) n1[i]=n2[i];
		for (i=0;i<len3;++i) n2[i]=n3[i];
		for (i=0;i<max;++i) n3[i]=d[max-i-1]+'0';
	}
	for (i=0;i<max;++i) cout<<n3[i];
	cout<<endl;
	return 0;
}