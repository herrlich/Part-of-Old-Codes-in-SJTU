#include <iostream> 
using namespace std; 
template <class elemType> 
class queue{ 
public: 
    virtual bool isEmpty() const=0; 
    virtual void enQueue(const elemType &x)=0; 
    virtual elemType deQueue()=0; 
    virtual elemType getHead()=0; 
    virtual ~queue () {} 
}; 
  
template <class elemType> 
class seqQueue:public queue<elemType>{ 
private: 
    elemType *elem; 
    int front,rear; 
    int maxSize; 
public: 
    seqQueue(int size=1000000){ 
        maxSize=size; 
        elem=new elemType[maxSize]; 
        front=rear=0; 
    } 
    ~seqQueue() {delete [] elem;} 
    bool isEmpty() const {return front==rear;} 
    void enQueue(const elemType &x); 
    elemType deQueue(); 
    elemType getHead() {return elem[front+1];} 
}; 
template <class elemType> 
void seqQueue<elemType>::enQueue(const elemType &x){ 
    elem[(rear+1)]=x; 
    rear=rear+1; 
} 
template <class elemType> 
elemType seqQueue<elemType>::deQueue(){ 
    front=front+1; 
    return elem[front]; 
} 
int array[4000000]; 
int main(){ 
    int n,i,father; 
    cin>>n; 
    for (int p=0;p<4000000;++p) array[p]=-1; 
    array[0]=0; 
    for (i=1;i<n;++i){ 
        cin>>father; 
        array[4*i]=i; 
        if (array[4*father+2]==-1) array[4*father+2]=i; 
        else array[4*father+3]=i; 
        array[4*i+1]=father; 
    } 
    seqQueue<int> q1; 
    q1.enQueue(array[0]); 
    long int times=0,num=0; 
    while (times<n){ 
        num=q1.getHead(); 
        cout<<q1.getHead()<<' '; 
        ++times; 
        q1.deQueue(); 
        if (array[4*num+2]!=-1) q1.enQueue(array[4*(array[4*num+2])]); 
        if (array[4*num+3]!=-1) q1.enQueue(array[4*(array[4*num+3])]); 
    } 
    return 0; 
} 