#include <iostream> 
#include <list> 
#include <queue> 
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
    queue<node,list<node*> > q1; 
    q1.push(array[0]); 
    while (!q1.empty()){ 
        node *p=q1.front(); 
        cout<<p->data<<' '; 
        q1.pop();
        if (p->left!=NULL) q1.push(p->left); 
        if (p->right!=NULL) q1.push(p->right); 
		delete p;
    } 
    return 0; 
} 