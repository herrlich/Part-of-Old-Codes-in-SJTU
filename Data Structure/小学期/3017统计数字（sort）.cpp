#include <iostream> 
#include <algorithm> 
using namespace std; 
int num[200000]; 
int main(){ 
    int n; 
    cin>>n; 
    for(int i=0;i<n;++i) cin>>num[i]; 
    num[n]=0; 
    sort(num,num+n); 
    int s=1; 
    for(int i=0;i<n;++i){ 
        if(num[i] != num[i+1]){ 
            cout<<num[i]<<" "<<s<<endl; 
            s=1; 
        } 
        else ++s; 
    } 
    return 0; 
} 