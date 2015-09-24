#include <iostream> 
using namespace std; 
int num[1000000]={0}; 
int main(){ 
    long int n,*array,i,large=0,small=0,tmp,l=0,s=0,max=0,min=1000000; 
    cin>>n;
    array=new long int[2*n]; 
    for (i=0;i<2*n;++i){ 
        cin>>array[i]; 
        max=(array[i]>max)?array[i]:max; 
        min=(array[i]<min)?array[i]:min; 
    } 
    for (i=0;i<n;++i){ 
        for (tmp=array[2*i];tmp<array[2*i+1];++tmp) num[tmp]=1; 
    } 
    long int t=min; 
    while (t<max){ 
        if (num[t]==0){ 
            while (t<max){ 
                ++s;
				++t; 
                if (num[t]==1) break;
            } 
            if (s>small) small=s; 
            s=0; 
        } 
        else{
            while (t<max){ 
                ++l;
				++t; 
                if (num[t]==0) break; 
            } 
            if (l>large) large=l; 
            l=0; 
        } 
    } 
    cout<<large<<'\t'<<small<<endl; 
    delete [] array; 
    return 0; 
} 