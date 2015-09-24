#include <iostream> 
#include <cstring> 
using namespace std; 
char a[201],b[201],e[3],f[3],g[201],h[201]; 
int c[201]={0},d[201]={0}; 
int main() 
{
	char *p,*q;
    int i=0,lena,lenb,min,max,j=0; 
	cin.getline(a,201,'.');
	cin.getline(e,3);
	cin.getline(b,201,'.');
	cin.getline(f,3);
	p=strncat(a,e,3);
	q=strncat(b,f,3);
    lena=strlen(p); 
    lenb=strlen(q);
    min=(lena<lenb)?lena:lenb; 
    max=(lena>lenb)?lena:lenb; 
    for (i=0;i<min;++i){ 
        c[max-i-1]=(p[lena-i-1]-'0')+(q[lenb-i-1]-'0'); 
    } 
    if (lena==max){ 
        for (i=0;i<max-min;++i){ 
            c[i]=p[i]-'0'; 
        } 
    } 
    if (lenb==max){ 
        for (i=0;i<max-min;++i){ 
            c[i]=q[i]-'0'; 
        } 
    } 
    for (i=0;i<max+1;++i){ 
        d[max-i]=(c[max-i-1]%10+c[max-i]/10+j)%10; 
        if (c[max-i-1]%10+c[max-i]/10+j>=10) j=1; 
        else j=0; 
    }
    if (d[0]!=0){ 
        for (i=0;i<max-1;++i) cout<<d[i];
		cout<<"."<<d[max-1]<<d[max]<<endl;
    } 
    if (d[0]==0){ 
        for (i=1;i<max-1;++i) cout<<d[i]; 
		cout<<"."<<d[max-1]<<d[max]<<endl;
    } 
    return 0; 
} 