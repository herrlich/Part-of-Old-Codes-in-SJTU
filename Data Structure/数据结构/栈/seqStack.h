#include "stack.h"
template <class elemType>
class seqStack:public stack<elemType>{
private:
	elemType *elem;
	int top_p;
	int maxSize;
	void doubleSpace();
public:
	seqStack(int initSize=10){
		elem=new elemType[initSize];
		top_p=-1;
		maxSize=initSize;
	}
	~seqStack() {delete [] elem;}
	bool isEmpty() const {return top_p==-1;}
	void push(const elemType &x){
		if (top_p==maxSize-1) doubleSpace();
		elem[++top_p]=x;
	}
	elemType pop() {return elem[top_p--];}
	elemType top() const {return elem[top_p];}
};
template <class elemType>
void seqStack<elemType>::doubleSpace(){
	elemType *tmp=elem;
	elem=new elemType[2*maxSize];
	for (int i=0;i<maxSize;++i) elem[i]=tmp[i];
	maxSize*=2;
	delete [] tmp;
}	