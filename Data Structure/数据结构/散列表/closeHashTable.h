#include "hashTable.h"
template <class Type>
class closeHashTable:public hashTable<Type>{
private:
	struct node{
		Type data;
		int state;//0--empty;1--active;2--deleted
		node() {state=0;}
	};
	node *array;
	int size;
public:
	closeHashTable(int length=101,int (*f)(const Type &x)=defaultKey);
	~closeHashTable() {delete [] array;}
	bool find(const Type &x) const;
	bool insert(const Type &x);
	bool remove(const Type &x);
	void rehash();
};
template <class Type>
closeHashTable<Type>::closeHashTable(int length,int(*f)(const Type &x)){
	size=length;
	array=new node[size];
	key=f;
}
template <class Type>
bool closeHashTable<Type>::insert(const Type &x){
	int initPos,pos;
	initPos=pos=key(x)%size;
	do{
		if (array[pos].state!=1){
			array[pos].data=x;
			array[pos].state=1;
			return true;
		}
		if (array[pos].state==1&&array[pos].data==x){
			return true;
		}
		pos=(pos+1)%size;
	}while(pos!=initPos);
	return false;
}
template <class Type>
bool closeHashTable<Type>::remove(const Type &x){
	int initPos,pos;
	initPos=pos=key(x)%size;
	do{
		if (array[pos].state==0) return false;
		if (array[pos].state==1&&array[pos].data==x){
			array[pos].state=2;
			return true;
		}
		pos=(pos+1)%size;
	}while(pos!=initPos);
	return false;
}
template <class Type>
bool closeHashTable<Type>::find(const Type &x) const{
	int initPos,pos;
	initPos=pos=key(x)%size;
	do{
		if (array[pos].state==0) return false;
		if (array[pos].state==1&&array[pos].data==x){
			return true;
		}
		pos=(pos+1)%size;
	}while(pos!=initPos);
	return false;
}
template <class Type>
void closeHashTable<Type>::rehash(){
	node *tmp=array;
	array=new node[size];
	for (int i=0;i<size;++i){
		if (tmp[i].state==1) insert(tmp[i].data);
	}
	delete [] tmp;
}