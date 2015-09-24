#include "stack.h"
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