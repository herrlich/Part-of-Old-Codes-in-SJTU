#include <iostream>
using namespace std;
struct node{
	int data;
	node *next;
};
int main()
{
	int i,n;
	cin>>n;
	node *head,*p,*q;
	head=q=new node;
	head->data=0;
	for (i=1;i<n;++i){
		p=new node;
		p->data=i;
		q->next=p;
		q=p;
	}
	q->next=head;

	q=head;
	while(q->next!=q){
		p=q->next;
		q=p->next;
		p->next=q->next;
		cout<<q->data<<'\t';
		delete q;
		q=p->next;
	}
	cout<<"\n×îºóÊ£ÏÂ"<<q->data<<endl;
	delete q;
	return 0;
}