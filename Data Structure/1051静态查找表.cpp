#include <iostream>
using namespace std;
struct node{
	double num;
	node *next;
};
int main(){
	double x;
	int m,n,i,total=0;
	node *head,*p,*rear,*q;
	head=rear=new node;
	cin>>n;
	for (i=0;i<n;++i){
		cin>>x;
		p=new node;
		p->num=x;
		rear->next=p;
		rear=p;
	}
	rear->next=NULL;
	cin>>m;
	for (i=0;i<m;++i){
		int times=0;
		q=head;
		p=head->next;
		cin>>x;
		while (p!=NULL && p->num!=x){
			++times;
			q=p;
			p=p->next;
		}
		if (p!=NULL) ++times;
		if (q!=head&&p!=NULL&&p->num==x){
			q->next=p->next;
			q=head->next;
			head->next=p;
			p->next=q;
			p=head;
		}
		total+=times;
	}
	cout<<total<<endl;
	return 0;
}