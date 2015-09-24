#include <iostream>  
#include <algorithm>  
using namespace std;  
struct node{  
    int like;  
    int pos; 
    int group; 
    node(int l=0,int p=0,int g=0) {like=l;pos=p;group=g;}  
    node operator=(const node &a){  
        like=a.like;  
        pos=a.pos; 
        group=a.group; 
        return *this;  
    }  
    bool operator<(const node &a) const{   
        if (like<a.like) return true;   
        if (like>a.like) return false;   
        if (group<a.group) return true;   
        return false;   
    }  
};  
template <class Type>  
class priorityQueue{  
private:  
    int currentSize;//队列长度  
    Type *array;  
    int maxSize;  
public:  
    priorityQueue(int capacity=100){  
        array=new Type[capacity];  
        maxSize=capacity;  
        currentSize=0;  
    }  
    priorityQueue(const Type data[],int size);  
    ~priorityQueue() {delete [] array;}  
    bool isEmpty() const {return currentSize==0;}  
    void enQueue(const Type &x);  
    Type deQueue();  
    Type getHead() const {return array[1];}  
private:  
    void doubleSpace();  
    void buildHeap();  
    void percolateDown(int hole);  
};  
    
template <class Type>  
void priorityQueue<Type>::enQueue(const Type &x){  
    if (currentSize==maxSize-1) doubleSpace();  
    int hole=++currentSize;  
    for (;hole>1&&x<array[hole/2];hole/=2) array[hole]=array[hole/2];  
    array[hole]=x;  
}  
    
template <class Type>  
Type priorityQueue<Type>::deQueue(){  
    Type minItem;  
    minItem=array[1];  
    array[1]=array[currentSize--];  
    percolateDown(1);  
    return minItem;  
}  
    
template <class Type>  
void priorityQueue<Type>::percolateDown(int hole){  
    int child;  
    Type tmp=array[hole];  
    for (;hole*2<=currentSize;hole=child){  
        child=hole*2;  
        if (child!=currentSize&&array[child+1]<array[child]) ++child;  
        if (array[child]<tmp) array[hole]=array[child];  
        else break;  
    }  
    array[hole]=tmp;  
}  
    
template <class Type>  
void priorityQueue<Type>::buildHeap(){  
    for (int i=currentSize/2;i>0;--i) percolateDown(i);  
}  
    
template <class Type>  
priorityQueue<Type>::priorityQueue(const Type *items,int size):maxSize(size+10),currentSize(size){  
    array=new Type[maxSize];  
    for (int i=0;i<size;++i) array[i+1]=items[i];  
    buildHeap();  
}  
    
template <class Type>  
void priorityQueue<Type>::doubleSpace(){  
    Type *tmp=array;  
    maxSize*=2;  
    array=new Type[maxSize];  
    for (int i=0;i<=currentSize;++i) array[i]=tmp[i];  
    delete [] tmp;  
}  
int love[50001];  
int length[50001];  
int choose[50001]={0};   
int main(){  
    int n,m,i,j,position;  
    cin>>n>>m;  
    node num;  
    node **cube=new node*[m];  
    for (i=1;i<=n;++i) cin>>love[i];  
    for (i=0;i<m;++i){  
        cin>>length[i];
		if (length[i]==0){
			cube[i]=NULL;
			continue;
		}
        cube[i]=new node[length[i]];  
        for (j=0;j<length[i];++j){  
            cin>>position;  
            cube[i][j]=node(love[position],position,i);  
        } 
    }  
    priorityQueue<node> q;  
    for (i=0;i<m;++i){
		if (cube[i]!=NULL) q.enQueue(cube[i][choose[i]]);
	}
    while (!q.isEmpty()){   
        num=q.getHead();   
        cout<<num.pos<<'\n';    
        q.deQueue();    
        for (i=0;i<m;++i){    
			if (cube[i]!=NULL&&choose[i]<length[i]&&cube[i][choose[i]].pos==num.pos) break;    
        }   
        ++choose[i];    
        if (choose[i]<length[i]) q.enQueue(cube[i][choose[i]]);    
    }  
    for (i=0;i<m;++i) delete [] cube[i];  
    delete [] cube;  
} 