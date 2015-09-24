#include <iostream> 
using namespace std; 
int main(){ 
    int num,sum=0; 
    cin>>num; 
    int *arr=new int[num]; 
    int *p=new int[num]; 
    for (int i=0;i<num;++i){ 
        cin>>arr[i]; 
    } 
    for (int i=0;i<num;++i){ 
        if (arr[i]==1) p[i]=0; 
        else{ 
            sum=0; 
            for (int j=2;j<arr[i];++j){ 
                if (arr[i]%j==0) sum=sum+j; 
            } 
            p[i]=sum+1; 
        } 
    } 
    for (int i=0;i<num;++i) cout<<p[i]<<endl; 
    delete [] p; 
    delete [] arr; 
    return 0; 
} 