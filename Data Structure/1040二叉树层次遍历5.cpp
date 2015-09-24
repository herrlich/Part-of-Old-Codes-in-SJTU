#include <iostream>  
#include <vector> 
using namespace std; 
struct node{  
    int data;  
    node *left,*right;  
    node(int num,node *l=NULL,node *r=NULL) {data=num;left=l;right=r;}  
};  
node *array[1000000];  
int main(){  
    int n,i,father;  
    cin>>n;  
    array[0]=new node(0);  
    for (i=1;i<n;++i){  
        cin>>father;  
        array[i]=new node(i);  
        if (array[father]->left==NULL) array[father]->left=array[i];  
        else array[father]->right=array[i];  
    }  
    vector<node*> vec; 
    vec.push_back(array[0]); 
    int cur=0; 
    int last=1; 
    while(cur<vec.size()) { 
        cout<<vec[cur]->data<<' '; 
        if(vec[cur]->left) vec.push_back(vec[cur]->left);
        if(vec[cur]->right) vec.push_back(vec[cur]->right); 
        cur++; 
    } 
    return 0; 
} 