#include <iostream>
#include <queue> 
using namespace std;
struct node{
	int num;
	node* left_son;
	node* right_brother;
};
void preOrder(node* head){
	if (head==NULL) return;
	cout<<head->num<<' ';
	preOrder(head->left_son);
	preOrder(head->right_brother);
}
void postOrder(node* head){
	if (head==NULL) return;
	postOrder(head->left_son);
	cout<<head->num<<' ';
	postOrder(head->right_brother);
}
void levelOrder(node* head){
	queue<node*> q;
    q.push(head);
	while(!q.empty()){
		head=q.front();
		q.pop();
		cout<<head->num<<' ';
        head=head->left_son;
		while(head){
			q.push(head);
			head=head->right_brother;
		}
	}
}
node *array[12345];
int judge[12345]={0};
int main(){
	int N,i,tmp1,tmp2,tmp3,head;
	cin>>N;
	for (i=0;i<N;++i){
		array[i]=new node;
		array[i]->left_son=NULL;
		array[i]->right_brother=NULL;
	}
	for (i=0;i<N;++i){
		cin>>tmp1>>tmp2>>tmp3;
		array[tmp1-1]->num=tmp1;
		if (tmp2!=0){
			judge[tmp2-1]=1;
			array[tmp1-1]->left_son=array[tmp2-1];
		}
		if (tmp3!=0){
			judge[tmp3-1]=1;
			array[tmp1-1]->right_brother=array[tmp3-1];
		}
	}
	for (i=0;i<N;++i){
		if (judge[i]==0){
			head=i;
			break;
		}
	}
	preOrder(array[head]);
	cout<<endl;
	postOrder(array[head]);
	cout<<endl;
	levelOrder(array[head]);
	cout<<endl;
	return 0;
}