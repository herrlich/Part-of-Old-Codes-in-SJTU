#include "queue.h"
template <class elemType>
class seqQueue:public queue<elemType>{
private:
	elemType *elem;
	int front,rear;
	int maxSize;
	void doubleSpace();
public:
	seqQueue(int size=10){
		maxSize=size;
		elem=new elemType[maxSize];
		front=rear=0;
	}
	~seqQueue() {delete [] elem;}
	bool isEmpty() const {return front==rear;}
	void enQueue(const elemType &x);
	elemType deQueue();
	elemType getHead() {return elem[(front+1)%maxSize];}
};
template <class elemType>
void seqQueue<elemType>::doubleSpace(){
	elemType *tmp=elem;
	elem=new elemType[2*maxSize];
	for (int i=1;i<maxSize;++i) elem[i]=tmp[(front+i)%maxSize];
	maxSize*=2;
	front=0;
	rear=maxSize-1;
	delete tmp;
}
template <class elemType>
void seqQueue<elemType>::enQueue(const elemType &x){
	if ((rear+1)%maxSize==front) doubleSpace();
	elem[(rear+1)%maxSize]=x;
	rear=(rear+1)%maxSize;
}
template <class elemType>
elemType seqQueue<elemType>::deQueue(){
	front=(front+1)%maxSize;
	return elem[front];
}