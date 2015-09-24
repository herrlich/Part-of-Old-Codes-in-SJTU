#include <iostream>
using namespace std;
int candy,total=0;
template <class elemType>
class linkQueue{
private:
	struct node{
		elemType data;
		node *next;
		node(const elemType &x,node *N=NULL) {data=x;next=N;}
		node():next(NULL) {}
		~node() {}
	};
	node *front,*rear;
public:
	linkQueue() {front=rear=NULL;}
	~linkQueue();
	bool isEmpty() const {return front==NULL;}
	void enQueue(const elemType &x);
	elemType deQueue();
	elemType getHead() {return front->data;}
};
template <class elemType>
linkQueue<elemType>::~linkQueue(){
	node *tmp;
	while (front!=NULL){
		tmp=front;
		front=front->next;
		delete tmp;
	}
}
template <class elemType>
void linkQueue<elemType>::enQueue(const elemType &x){
	if (rear==NULL) front=rear=new node(x);
	else{
		rear->next=new node(x);
		rear=rear->next;
	}
}
template <class elemType>
elemType linkQueue<elemType>::deQueue(){
	node *tmp=front;
	elemType value=front->data;
	front=front->next;
	if (front==NULL) rear=NULL;
	delete tmp;
	return value;
}
template <class TypeOfVer>
class adjListGraph{
public:
	adjListGraph(int vSize);
	bool insert(int u,int v);
	void topSort() const;
	~adjListGraph();
private:
	struct edgeNode{
		int end;
		edgeNode *next;
		edgeNode(int e,edgeNode *n=NULL){
			end=e;
			next=n;
		}
	};
	struct verNode{
		TypeOfVer ver;
		edgeNode *head;
		verNode(edgeNode *h=NULL) {head=h;}
	};
	int Vers,Edges;
	verNode* verList;
};
template <class TypeOfVer>
adjListGraph<TypeOfVer>::adjListGraph(int vSize){
	Vers=vSize;
	Edges=0;
	verList=new verNode[vSize];
	for (int i=0;i<Vers;++i) verList[i].ver=-1;
}
template <class TypeOfVer>
adjListGraph<TypeOfVer>::~adjListGraph(){
	int i;
	edgeNode* p;
	for (i=0;i<Vers;++i){
		while ((p=verList[i].head)!=NULL){
			verList[i].head=p->next;
			delete p;
		}
	}
	delete [] verList;
}
template <class TypeOfVer>
bool adjListGraph<TypeOfVer>::insert(int u,int v){
	verList[u].head=new edgeNode(v,verList[u].head);
	++Edges;
	return true;
}
template <class TypeOfVer>
void adjListGraph<TypeOfVer>::topSort() const{
	linkQueue<int> q;
	edgeNode* p;
	int current,times=0,plusx=0;
	int *inDegree=new int[Vers];
	for (int i=0;i<Vers;++i) inDegree[i]=0;
	for (int i=0;i<Vers;++i){
		for (p=verList[i].head;p!=NULL;p=p->next){
			++inDegree[p->end];
		}
	}
	for (int i=0;i<Vers;++i){
		if (inDegree[i]==0){
			inDegree[i]=-1;
			q.enQueue(i);
			++times;
		}
	}
	while (!q.isEmpty()){
		for (int i=0;i<times;++i){
			current=q.deQueue();
			++total;
			candy=candy+plusx+100;
			for (p=verList[current].head;p!=NULL;p=p->next) --inDegree[p->end];
		}
		times=0;
		++plusx;
		for (int i=0;i<Vers;++i){
			if (inDegree[i]==0){
				inDegree[i]=-1;
				q.enQueue(i);
				++times;
			}
		}
	}
}
int main(){
	int n,m,i,a,b;
	cin>>n>>m;
	adjListGraph<int> qu(n);
	for (i=0;i<m;++i){
		cin>>a>>b;
		qu.insert(b-1,a-1);
	}
	qu.topSort();
	if (total!=n){
		cout<<"hehe"<<endl;
		return 0;
	}
	cout<<candy<<endl;
	return 0;
}