#include <iostream> 
#include <algorithm> 
using namespace std; 
int person[300],height1[300]={0},height2[300]={0}; 
int main() 
{ 
    int n,ans=0,result; 
    cin>>n; 
    for(int i=1;i<=n;++i) cin>>person[i]; 
    for(int i=1;i<=n;++i){ 
        for(int j=1;j<=i-1;++j){ 
            if(person[i]>person[j]) height1[i]=max(height1[i],height1[j]+1); 
        } 
    } 
    for(int i=n;i>=1;--i){ 
        for(int j=i+1;j<=n;j++){ 
            if(person[i]>person[j]) height2[i]=max(height2[i],height2[j]+1); 
        } 
    } 
    for(int i=1;i<=n;++i) ans=max(height1[i]+height2[i],ans); 
    result=n-ans-1; 
    cout<<result<<endl; 
    return 0; 
} 