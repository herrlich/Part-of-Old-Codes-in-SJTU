#include <iostream>  
#include <cstring>  
using namespace std;  
char a[310],b[310];  
int c[310]={0},d[310]={0},e[310]={0},f[310]={0},g[310]={0};  
int main()  
{ 
    int i=0,lena,lenb,j=0,time=0,k,temp; 
    bool stop=true,turn=true; 
    cin>>a>>b; 
    lena=strlen(a); 
    lenb=strlen(b); 
    if (lena<lenb){ 
        cout<<0; 
        return 0; 
    }
    for (i=0;i<lena;++i){ 
        d[i]=a[i]-'0'; 
    }
	for (i=0;i<lenb;++i) e[i]=b[i]-'0';
	for (k=lenb-1;k<lena;++k){
		time=0;
		do{ 
			stop=true;
			turn=true; 
			j=0;
			temp=310;
			for (i=0;i<310;++i) g[i]=0;
			for (i=0;i<lenb;++i){
				g[i+k-lenb+1]=e[i];
			}
			for (i=0;i<=k;++i){  
				c[i]=d[i]-g[i];  
			}
			for (i=0;i<=k;++i){
				if (c[i]!=0){
					temp=i;
					break;
				}
			}
			if (c[temp]>0){
				stop=false;
			}
			for (i=0;i<=k;++i){ 
				if (c[i]!=0) turn=false;
			}
			if (turn){
				for (i=0;i<=k;++i){
					d[i]=c[i];
				}
			}
			if (!stop){
				for (i=0;i<k+1;++i){ 
					d[k-i]=(c[k-i]+10-j)%10; 
					if (c[k-i]-j<0) j=1; 
					else j=0; 
				}
			}
			++time;
		}while (!stop);
		if (turn) ++time;
		f[k]=time;
	}
	if (f[lenb-1]==1){
		for (k=lenb;k<lena;++k){
		cout<<f[k]-1;
		}
	}
	else{
		for (k=lenb-1;k<lena;++k){
			cout<<f[k]-1;
		}
	}
	return 0;  
} 