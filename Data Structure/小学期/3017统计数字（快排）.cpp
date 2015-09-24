#include <iostream> 
using namespace std; 
int num[200000]; 
int divide(int a[],int low,int high){ 
    int k=a[low]; 
    do{ 
        while(low<high&&a[high]>=k) --high; 
        if (low<high){ 
            a[low]=a[high]; 
            ++low; 
        } 
        while (low<high&&a[low]<=k) ++low; 
        if (low<high){ 
            a[high]=a[low]; 
            --high; 
        } 
    }while(low!=high); 
    a[low]=k; 
    return low; 
} 
void quickSort(int a[],int low,int high){ 
    int mid; 
    if (low>=high) return; 
    mid=divide(a,low,high); 
    quickSort(a,low,mid-1); 
    quickSort(a,mid+1,high); 
} 
  
int main(){ 
    int n; 
    cin>>n; 
    for(int i=0;i<n;++i) cin>>num[i]; 
    num[n]=0; 
    quickSort(num,0,n-1); 
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