#include <iostream> 
using namespace std; 
int main(){ 
    int num,temp,i; 
    cin>>num; 
    temp=num; 
    while (temp/10!=0){ 
        if (temp%10!=4&&temp%10!=7){ 
            cout<<"NO"; 
            return 0; 
        } 
        temp=temp/10; 
    } 
    if (temp!=4 && temp!=7){ 
        cout<<"NO"; 
        return 0; 
    } 
    for (i=num-1;i>1;--i){ 
        if (num%i==0){ 
            cout<<"NO"; 
            return 0; 
        } 
    } 
    cout<<"YES"; 
    return 0; 
} 