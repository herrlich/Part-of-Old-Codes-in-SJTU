#include "list.h"
class OutOfBound {};
class IllegalSize {};
template <class elemType>
class seqList:public list<elemType>{
private:
	int currentLength;
	int maxSize;
	elemType *data;
	void doubleSpace();
public:
	seqList(int initSize=10);
	virtual void clear() {currentLength=0;} 
	virtual int length() const {return currentLength;}
	virtual void insert(int i,const elemType &x);
	virtual void remove(int i);
	virtual int search(const elemType &x) const;
	virtual elemType visit(int i) const;
	virtual void traverse() const;
	virtual ~seqList() {delete [] data;}
};
template <class elemType>
void seqList<elemType>::doubleSpace(){
	elemType *tmp=data;
	maxSize*=2;
	data=new elemType[maxSize];
	for (int i=0;i<maxSize;++i) data[i]=tmp[i];
	delete [] tmp;
}
template <class elemType>
seqList<elemType>::seqList(int initSize){
	if (initSize<=0) throw IllegalSize();
	data=new elemType[initSize];
	maxSize=initSize;
	currentLength=0;
}
template <class elemType>
void seqList<elemType>::insert(int i,const elemType &x){
	if (i<0 || i>currentLength) throw OutOfBound();
	if (currentLength==maxSize) doubleSpace();
	for (int j=currentLength;j>i;--j) data[j]=data[j-1];
	data[i]=x;
	++currentLength;
}
template <class elemType>
void seqList<elemType>::remove(int i){
	if (i<0 || i>currentLength-1) throw OutOfBound();
	for (int j=i;j<currentLength-1;++j) data[j]=data[j+1];
	--currentLength;
}
template <class elemType>
int seqList<elemType>::search(const elemType &x) const{
	int i=0;
	for (;i<currentLength&&data[i]!=x;++i);
	if (i==currentLength) return -1;
	else return i;
}
template <class elemType>
elemType seqList<elemType>::visit(int i) const{
	if (i<0 || i>currentLength-1) throw OutOfBound();
	return data[i];
}
template <class elemType>
void seqList<elemType>::traverse() const{
	cout<<endl;
	for (int i=0;i<currentLength;++i) cout<<data[i]<<' ';
}