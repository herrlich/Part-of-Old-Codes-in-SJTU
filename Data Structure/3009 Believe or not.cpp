#include <iostream> 
#include <cstring> 
using namespace std; 
int main(){ 
    bool flag=true; 
    int tmp1,tmp2; 
    char a[1000],b[1000]; 
    cin.getline(a,1000); 
    cin.getline(b,1000); 
    int len=strlen(a); 
    for (int i=0;i<len;++i){ 
        if (a[i]!=b[i]){ 
            flag=false; 
            tmp1=i; 
            break; 
        } 
    } 
    if (flag){
		cout<<"YES"<<endl;
        return 0; 
    }
    flag=true; 
    for (int i=tmp1+1;i<len;++i){ 
        if (a[i]!=b[i]){ 
            tmp2=i; 
            flag=false; 
            break; 
        } 
    } 
    if (!flag&&a[tmp1]==b[tmp2]&&a[tmp2]==b[tmp1]){ 
        cout<<"YES"<<endl; 
        return 0; 
    }
    cout<<"NO"<<endl; 
    return 0; 
}