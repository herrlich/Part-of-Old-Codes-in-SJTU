#include <iostream> 
using namespace std; 
int main(){ 
    int dif=1001,weight,num,given_weight,apple,tmp; 
    cin>>num>>given_weight; 
    for (int i=0;i<num;++i){ 
        cin>>apple; 
        if (apple>given_weight) tmp=apple-given_weight; 
        else tmp=given_weight-apple; 
        if (tmp<dif){ 
            dif=tmp; 
            weight=apple; 
        } 
        if (tmp==dif) weight=(weight>apple)?weight:apple; 
    } 
    cout<<weight<<endl; 
    return 0; 
} 