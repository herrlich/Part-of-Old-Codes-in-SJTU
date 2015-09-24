#include <iostream> 
using namespace std; 
int poker[100]={0}; 
int main(){ 
    int n,i,sum=0,average,tmp=0,times=0; 
    cin>>n; 
    for (i=0;i<n;++i){ 
        cin>>poker[i]; 
        sum+=poker[i]; 
    } 
    average=sum/n; 
    for (i=0;i<n-1;++i){ 
        if (poker[i]>average){ 
            tmp=poker[i]-average; 
            poker[i+1]+=tmp; 
            ++times; 
            continue; 
        } 
        if (poker[i]<average){ 
            tmp=average-poker[i]; 
            poker[i+1]-=tmp; 
            ++times; 
            continue; 
        } 
    } 
    cout<<times<<'\n'; 
    return 0; 
} 