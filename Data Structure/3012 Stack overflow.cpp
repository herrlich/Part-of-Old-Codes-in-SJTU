#include <iostream> 
using namespace std; 
template <class elemType> 
class stack{ 
public: 
    virtual bool isEmpty() const=0; 
    virtual void push(const elemType &x)=0; 
    virtual elemType pop()=0; 
    virtual elemType top() const=0; 
    virtual ~stack() {} 
}; 
template <class elemType> 
class linkStack:public stack<elemType>{ 
private: 
    struct node{ 
        elemType data; 
        node *next; 
        node(const elemType &x,node *N=NULL){data=x;next=N;} 
        node():next(NULL) {} 
        ~node() {} 
    }; 
    node *elem; 
public: 
    linkStack() {elem=NULL;} 
    ~linkStack(); 
    bool isEmpty() const{return elem==NULL;} 
    void push(const elemType &x){ 
        node *tmp=new node(x,elem); 
        elem=tmp; 
    } 
    elemType pop(){ 
        node *tmp=elem; 
        elemType x=tmp->data; 
        elem=elem->next; 
        delete tmp; 
        return x; 
    } 
    elemType top() const {return elem->data;} 
}; 
template <class elemType> 
linkStack<elemType>::~linkStack(){ 
    node *tmp=elem; 
    while (elem!=NULL){ 
        tmp=elem; 
        elem=elem->next; 
        delete tmp; 
    } 
} 
int main(){ 
    int n,op,num,tmp; 
    linkStack<int> arr; 
    cin>>n; 
    int *array=new int[n]; 
    for (int i=0;i<n;++i){ 
        cin>>op>>num; 
        if (op==1){ 
            arr.push(num); 
            array[i]=1; 
        } 
        if (op==2){ 
            if (arr.isEmpty()){ 
                array[i]=2; 
                continue; 
            } 
            tmp=arr.top(); 
            arr.pop(); 
            if (num==tmp){ 
                array[i]=3; 
            } 
            else array[i]=4; 
        } 
    } 
    for (int i=0;i<n;++i){ 
        if (array[i]==1) cout<<"OK"<<endl; 
        if (array[i]==2) cout<<"ERROR"<<endl; 
        if (array[i]==3) cout<<"YES"<<endl; 
        if (array[i]==4) cout<<"NO"<<endl; 
    } 
    return 0; 
}