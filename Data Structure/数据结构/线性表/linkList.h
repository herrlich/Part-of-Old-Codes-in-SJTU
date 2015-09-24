#include "list.h"
class OutOfBound {};
template <class elemType>
class linkList:public list<elemType>{
private:
	struct node{
		elemType data;
		node *prev,*next;
		node (const elemType &x,node *p=NULL,node *n=NULL) {data=x;prev=p;next=n;}
		node ():next(NULL),prev(NULL) {}
		~node() {}
	};
	node *head,*tail;
	int currentLength;
	node * move(int i) const;
public :
	linkList();
	~linkList() {clear();delete head;delete tail;}
	void clear();
	int length() const {return currentLength;}
	void insert(int i,const elemType &x);
	void remove(int i);
	int search(const elemType &x) const;
	elemType visit(int i) const;
	void traverse() const;
};
template <class elemType>
typename linkList<elemType>::node * linkList<elemType>::move(int i) const{
	node *p=head->next;
	if (i<0 || i>currentLength) throw OutOfBound();
	while (i--) p=p->next;
	return p;
}
template <class elemType>
linkList<elemType>::linkList(){
	head=new node;
	head->next=tail=new node;
	tail->prev=head;
	currentLength=0;
}
template <class elemType>
void linkList<elemType>::clear(){
	node *p=head->next,*q;
	head->next=tail;
	tail->prev=head;
	while (p!=tail){
		q=p->next;
		delete p;
		p=q;
	}
	currentLength=0;
}
template <class elemType>
void linkList<elemType>::insert(int i,const elemType &x){
	node *pos,*tmp;
	pos=move(i);
	tmp=new node(x,pos->prev,pos);
	pos->prev->next=tmp;
	pos->prev=tmp;
	++currentLength;
}
template <class elemType>
void linkList<elemType>::remove(int i){
	node *pos;
	pos=move(i);
	pos->prev->next=pos->next;
	pos->next->prev=pos->prev;
	delete pos;
	--currentLength;
}
template <class elemType>
int linkList<elemType>::search(const elemType &x) const{
	node *p=head->next;
	int i=0;
	while (p!=tail&&p->data!=x) {p=p->next;++i;}
	if (p==tail) return -1;
	else return i;
}
template <class elemType>
elemType linkList<elemType>::visit(int i) const{
	node *p=move(i);
	return p->data;
}
template <class elemType>
void linkList<elemType>::traverse() const{
	node *p=head->next;
	cout<<endl;
	while (p!=tail){
		cout<<p->data<<' ';
		p=p->next;
	}
	cout<<endl;
}