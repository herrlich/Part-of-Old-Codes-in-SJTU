#include <iostream> 
#include <cstring> 
using namespace std; 
char a[100001],b[100001]; 
int c[100001]={0},d[100001]={0}; 
int main() 
{ 
    int i=0,lena,lenb,min,max,j=0; 
    cin>>a>>b;
    lena=strlen(a); 
    lenb=strlen(b); 
    min=(lena<lenb)?lena:lenb; 
    max=(lena>lenb)?lena:lenb; 
    for (i=0;i<min;++i){ 
        c[max-i-1]=(a[lena-i-1]-'0')+(b[lenb-i-1]-'0'); 
    } 
    if (lena==max){ 
        for (i=0;i<max-min;++i){ 
            c[i]=a[i]-'0'; 
        } 
    } 
    if (lenb==max){ 
        for (i=0;i<max-min;++i){ 
            c[i]=b[i]-'0'; 
        } 
    } 
    for (i=0;i<max;++i){ 
        d[max-i]=(c[max-i-1]%10+c[max-i]/10+j)%10; 
        if (c[max-i-1]%10+c[max-i]/10+j>=10) j=1; 
        else j=0; 
    }
	d[0]=(j+c[0]/10)%10;
    if (d[0]!=0){ 
        for (i=0;i<max+1;++i) cout<<d[i]; 
    } 
    if (d[0]==0){ 
        for (i=1;i<max+1;++i) cout<<d[i]; 
    } 
    return 0; 
} 