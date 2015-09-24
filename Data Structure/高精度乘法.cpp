#include <iostream>
#include <cstring>
using namespace std;
char a[310],b[310];
int c[100000]={0},d[100000]={0};
int main()
{
	int i=0,lena,lenb,j=0,k=0;
	cin>>a>>b;
	lena=strlen(a);
	lenb=strlen(b);
	for (i=0;i<lena;++i){
		for (j=0;j<lenb;++j){
			c[i+j+1]+=(a[i]-'0')*(b[j]-'0');
		}
	}
	for (i=0;i<lena+lenb;++i){
		d[lena+lenb-1-i]=(c[lena+lenb-i-1]%10+c[lena+lenb-i]/10+k)%10;
		if (c[lena+lenb-i-1]%10+c[lena+lenb-i]/10+k>=10) k=(c[lena+lenb-i-1]%10+c[lena+lenb-i]/10+k)/10;
		else k=0;
	}
	if (d[0]!=0){
		for (i=0;i<lena+lenb;++i) cout<<d[i];
	}
	if (d[0]==0){
		for (i=1;i<lena+lenb;++i) cout<<d[i];
	}
	return 0;
}