#include <iostream> 
using namespace std; 
int list[1000][1000]={0}; 
int main() 
{ 
    int L,W,i=0,j=0,sum=0,a,b,k,all=0,**array,num=0; 
    cin>>L>>W; 
      
    array=new int*[L]; 
        for (i=0;i<L;++i){ 
            array[i]=new int [W]; 
            for (j=0;j<W;++j){ 
                cin>>array[i][j]; 
            } 
        } 
    cin>>a>>b; 
    for (i=0;i<L;++i){ 
        for (j=0;j<=W-b;++j){ 
            for (k=0;k<b;++k){ 
                sum+=array[i][j+k]; 
            } 
            list[i][j]=sum; 
            sum=0; 
        } 
    } 
    for(j=0;j<=W-b;++j){ 
        for(i=0;i<=L-a;++i){ 
            for (k=0;k<a;++k){ 
                num+=list[i+k][j]; 
            } 
            all=(all>num)?all:num; 
            num=0; 
        } 
    } 
    cout<<all<<endl; 
    return 0; 
} 