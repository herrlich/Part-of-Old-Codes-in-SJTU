#include <iostream>  
#include <list>  
#include <queue>  
using namespace std;  
int array[4000000]; 
int main(){ 
    int n,i,father; 
    cin>>n; 
    for (int p=0;p<4000000;++p) array[p]=-1; 
    array[0]=0; 
    for (i=1;i<n;++i){ 
        cin>>father; 
        array[4*i]=i; 
        if (array[4*father+2]==-1) array[4*father+2]=i; 
        else array[4*father+3]=i; 
        array[4*i+1]=father; 
    } 
    queue<int> q1; 
    q1.push(array[0]); 
    long int times=0,num=0; 
    while (times<n){ 
        num=q1.front(); 
        cout<<q1.front()<<' '; 
        ++times; 
        q1.pop(); 
        if (array[4*num+2]!=-1) q1.push(array[4*(array[4*num+2])]); 
        if (array[4*num+3]!=-1) q1.push(array[4*(array[4*num+3])]); 
    } 
    return 0; 
} 