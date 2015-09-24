#include <iostream> 
using namespace std; 
int like[103][103][103]={0}; 
int a[51][51]; 
int main(){ 
    int m,n,i,j,k,max; 
    cin>>m>>n; 
    for (i=1;i<=m;++i) 
        for (j=1;j<=n;++j) 
            cin>>a[i][j];//i,j表示两张纸条纸条的横坐标
    for (k=2;k<=m+n-1;++k){ //k代表步数的和
        for (i=1;i<=k;++i){ 
            for (j=i;j<=k;++j) { 
                if (i==j&&k<m+n-1) continue; 
                max=like[i][j][k-1]; 
                if (like[i-1][j][k-1]>max) max=like[i-1][j][k-1]; 
                if (like[i][j-1][k-1]>max) max=like[i][j-1][k-1]; 
                if (like[i-1][j-1][k-1]>max) max=like[i-1][j-1][k-1]; 
                like[i][j][k]=max+a[i][k-i+1]+a[j][k-j+1]; 
            }
		}
	}
    cout<<like[m][m][m+n-1]<<endl; 
    return 0; 
} 