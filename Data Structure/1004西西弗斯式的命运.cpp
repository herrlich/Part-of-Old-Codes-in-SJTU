#include <iostream> 
using namespace std; 
char condi[100000]; 
int main(){ 
    int up,plain,down,time,parts,result=0,sum=0; 
    cin>>time>>parts>>up>>plain>>down; 
    for (int i=0;i<parts;++i) cin>>condi[i]; 
    for (int i=0;i<parts;++i){ 
        if (condi[i]=='u'||condi[i]=='d'){ 
            if (result+up+down<=time){ 
                result=result+up+down; 
                ++sum; 
                continue; 
            } 
            else break; 
        } 
        if (condi[i]=='f'){ 
            if (result+2*plain<=time){ 
                result=result+2*plain; 
                ++sum; 
                continue; 
            } 
            else break; 
        } 
    } 
    cout<<sum<<endl; 
    return 0; 
} 