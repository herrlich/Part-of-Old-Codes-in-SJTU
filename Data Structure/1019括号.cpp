#include <iostream> 
#include <cstring> 
using namespace std; 
//此函数识别时不允许cin.ignore()......
int main(){ 
    int i,j,n; 
    cin>>n; 
    int *temp=new int[n]; 
    for (i=0;i<n;++i){ 
        char col[100]; 
        temp[i]=1; 
        int len,le[51],ri[51],left=0,right=0; 
        cin>>col; 
        len=strlen(col); 
        if (len%2!=0){ 
            temp[i]=0; 
            continue; 
        } 
        for (j=0;j<len;++j){ 
            if (col[j]=='('){ 
                le[left]=j; 
                ++left; 
            } 
            else { 
                ri[right]=j; 
                ++right; 
            } 
        } 
        if (right!=left){ 
            temp[i]=0; 
        } 
        for (j=0;j<len/2;++j){ 
            if (le[j]>ri[j]){ 
                temp[i]=0; 
            } 
        } 
    } 
    for (i=0;i<n;++i){ 
        if (temp[i]==1) cout<<"YES\n"; 
        else cout<<"NO\n"; 
    } 
    delete [] temp; 
    return 0; 
} 