#include <iostream>
#include "linkQueue.h"
using namespace std;
template <class Type>
class BinaryTree{
private:
	struct Node{
		Type data;
		Node *left,*right;
		Node():left(NULL),right(NULL) {};
		Node(Type item,Node *L=NULL,Node*R=NULL):data(item),left(L),right(R) {}
		~Node() {}
	};
	Node *root;
	struct StNode{
		Node* node;
		int TimesPop;
		StNode(Node *N=NULL):node(N),TimesPop(0) {}
	};
public:
	BinaryTree():root(NULL) {}
	BinaryTree(const Type &value){
		root=new Node(value);
	}
	~BinaryTree() {clear();}
	Type getRoot() {return root->data;}
	Type getLeft() {return root->left->data;}
	Type getRight() {return root->right->data;}
	void makeTree(const Type &x,BinaryTree &lt,BinaryTree &rt){
		root=new Node(x,lt,rt);
		lt=NULL;
		rt=NULL;
	}
	void delLeft(){
		BinaryTree tmp=root->left;
		root->left=NULL;
		tmp.clear();
	}
	void delRight(){
		BinaryTree tmp=root->right;
		root->right=NULL;
		tmp.clear();
	}
	bool isEmpty() {return root=NULL;}
	void clear() {if(root!=NULL) clear(root);root=NULL;}
	int size() const {return size(root);}
	int height() const {return height(root);}
	void preOrder() const{
		if (root!=NULL){
			cout<<"\n前序遍历"<<endl;
			preOrder(root);
		}
	}
	void midOrder() const{
		if (root!=NULL){
			cout<<"\n中序遍历"<<endl;
			midOrder(root);
		}
	}
	void postOrder() const{
		if (root!=NULL){
			cout<<"\n后序遍历"<<endl;
			postOrder(root);
		}
	}
	void createTree(Type flag);
private:
	int height(Node *t) const{
		if (t==NULL) return 0;
		else{
			int lh=height(t->left),rh=height(t->right);
			return 1+((lh>rh)?lh:rh);
		}
	}
	void clear(Node *t){
		if (t->left!=NULL) clear(t->left);
		if (t->right!=NULL) clear(t->right);
		delete t;
	}
	int size(Node *t){
		if (t==NULL) return 0;
		else return size(t->left)+size(t->right)+1;
	}
	void preOrder(Node *t) const{
		if (t!=NULL){
			cout<<t->data<<' ';
			preOrder(t->left);
			preOrder(t->right);
		}
	}
	void postOrder(Node *t) const{
		if (t!=NULL){
			postOrder(t->left);
			postOrder(t->right);
			cout<<t->data<<' ';
		}
	}
};
template <class Type>
void BinaryTree<Type>::createTree(Type flag){
	linkQueue<Node *>que;
	Node * tmp;
	Type ldata,rdata,x;
	cout<<"输入根结点"<<endl;
	cin>>x;
	root=new Node(x);
	que.enQueue(root);
	while (!que.isEmpty()){
		tmp=que.deQueue();
		cout<<"输入"<<tmp->data<<"的两个儿子："<<endl;
		cin>>ldata>>rdata;
		if (ldata!=flag) {que.enQueue(tmp->left=new Node(ldata));}
		if (rdata!=flag) {que.enQueue(tmp->right=new Node(rdata));}
	}
	cout<<"树创建完毕"<<endl;
}
template <class Type>
void BinaryTree<Type>::posrOrder() const{
	linkStack<StNode> s;
	StNode current(root);
	cout<<"后序遍历:";
	s.push(current);
	while (!s.empty()){
		current=s.pop();
		if (++current.TimesPop==3){
			cout<<current.node->data;
			continue;
		}
		s.push(current);
		if (current.TimesPop==1){
			if (current.node->left!=NULL) s.push(StNode(current.node->left));
		}
		else {
			if (current.node->right!=NULL) s.push(StNode(current.node->right));
		}
	}
}