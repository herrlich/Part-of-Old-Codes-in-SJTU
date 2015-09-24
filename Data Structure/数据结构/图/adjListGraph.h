#include "graph_abstract.h"
#include "linkQueue.h"
template <class TypeOfVer,class TypeOfEdge>
class adjListGraph:public graph<TypeOfEdge>{
public:
	adjListGraph(int vSize,const TypeOfVer d[]);
	bool insert(int u,int v,TypeOfEdge w);
	bool remove(int u,int v);
	bool exist(int u,int v)const;
	void dfs() const;//�����������
	void bfs() const;//�����������
	void EulerCircuit(TypeOfVer start);//Ѱ��ŷ����·
	void topSort() const;//Ѱ����������
	void kruscal() const;
	void prim(TypeOfEdge noEdge) const;
	void unweightedShortDistance(TypeOfVer start,TypeOfEdge noEdge) const;
	void dijkstra(TypeOfVer start,TypeOfEdge noEdge) const;
	~adjListGraph();
private:
	struct edgeNode{
		int end;//�е���
		TypeOfEdge weight;//�ߵ�Ȩֵ
		edgeNode *next;
		edgeNode(int e,TypeOfEdge w,edgeNode *n=NULL){
			end=e;
			weight=w;
			next=n;
		}
	};//����ߵĽ����
	struct verNode{
		TypeOfVer ver;//����ֵ
		edgeNode *head;//��Ӧ�������ͷָ��
		verNode(edgeNode *h=NULL) {head=h;}
	};//���涥��Ľ����
	struct EulerNode{
		int NodeNum;
		EulerNode *next;
		EulerNode(int ver) {NodeNum=ver;next=NULL;}
	};//����ŷ����·�Ľ����
	struct edge{
		int beg,end;
		TypeOfEdge w;
		bool operator<(const edge &rp) const {return w<rp.w;}
	};//kruskal�������õ�
	verNode* verList;//�ڽӱ�Ψһ�����ݳ�Ա
	void dfs(int start,bool p[])const;
	void printPath(int start,int end,int prev[]) const;
	EulerNode *EulerCircuit(int start,EulerNode *&end);
	verNode* clone() const;
};
template <class TypeOfVer,class TypeOfEdge>
adjListGraph<TypeOfVer,TypeOfEdge>::adjListGraph(int vSize,const TypeOfVer d[]){
	Vers=vSize;
	Edges=0;
	verList=new verNode[vSize];
	for (int i=0;i<Vers;++i) verList[i].ver=d[i];
}
template <class TypeOfVer,class TypeOfEdge>
adjListGraph<TypeOfVer,TypeOfEdge>::~adjListGraph(){
	int i;
	edgeNode* p;
	for (i=0;i<Vers;++i){
		while ((p=verList[i].head)!=NULL){//�ͷŵ�i�����ĵ�����
			verList[i].head=p->next;
			delete p;
		}
	}
	delete [] verList;
}
template <class TypeOfVer,class TypeOfEdge>
bool adjListGraph<TypeOfVer,TypeOfEdge>::insert(int u,int v,TypeOfEdge w){
	verList[u].head=new edgeNode(v,w,verList[u].head);
	++Edges;
	return true;
}
template <class TypeOfVer,class TypeOfEdge>
bool adjListGraph<TypeOfVer,TypeOfEdge>::remove(int u,int v){
	edgeNode *p=verList[u].head,*q;
	if (p==NULL) return false;
	if (p->end==v){//�����е�һ�������Ǵ�ɾ���ı�
		verList[u].head=p->next;
		delete p;
		--Edges;
		return true;
	}
	while (p->next!=NULL&&p->next->end!=v) p=p->next;
	if (p->next==NULL) return false;
	q=p->next;
	p->next=q->next;
	delete q;
	--Edges;
	return true;
}
template <class TypeOfVer,class TypeOfEdge>
bool adjListGraph<TypeOfVer,TypeOfEdge>::exist(int u,int v)const{
	edgeNode* p=verList[u].head;
	while (p!=NULL&&p->end!=v) p=p->next;
	if (p==NULL) return false;
	else return true;
}
//����Ϊ�������������ʵ��
template <class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge>::dfs()const{
	bool *visited=new bool[Vers];
	for (int i=0;i<Vers;++i) visited[i]=false;
	cout<<"��ǰͼ��������ȱ�������Ϊ:"<<endl;
	for (int i=0;i<Vers;++i){
		if (visited[i]==true) continue;
		dfs(i,visited);
		cout<<endl;
	}
}
template <class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge>::dfs(int start,bool visited[])const{
	edgeNode *p=verList[start].head;
	cout<<verList[start].ver<<'\t';
	visited[start]=true;
	while (p!=NULL){
		if (visited[p->end]==false) dfs(p->end,visited);
		p=p->next;
	}
}
template <class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge>::bfs()const{
	bool *visited=new bool[Vers];
	int currentNode;
	linkQueue<int> q;
	edgeNode *p;
	for (int i=0;i<Vers;++i) visited[i]=false;
	cout<<"��ǰͼ�Ĺ����������Ϊ:"<<endl;
	for (int i=0;i<Vers;++i){
		if (visited[i]==true) continue;
		q.enQueue(i);
		while (!q.isEmpty()){
			currentNode=q.deQueue();
			if (visited[currentNode]==true) continue;
			cout<<verList[currentNode].ver<<'\t';
			visited[currentNode]=true;
			p=verList[currentNode].head;
			while (p!=NULL){
				if (visited[p->end]==false) q.enQueue(p->end);
				p=p->next;
			}
		}
		cout<<endl;
	}
}
template <class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge>::EulerCircuit(TypeOfVer start){
	EulerNode *beg,*end,*p,*q,*tb,*te;
	int numOfDegree,i;
	edgeNode *r;
	verNode *tmp;
	if (Edges==0){
		cout<<"������ŷ����·"<<endl;
		return;
	}
	for (int i=0;i<Vers;++i){
		numOfDegree=0;
		r=verList[i].head;
		while (r!=NULL){
			++numOfDegree;
			r=r->next;
		}
		if (numOfDegree==0||numOfDegree%2){
			cout<<"������ŷ����·"<<endl;
			return;
		}
	}
	for (i=0;i<Vers;++i){
		if (verList[i].ver==start) break;
	}
	if (i==Vers){
		cout<<"��ʼ��㲻����"<<endl;
		return;
	}
	tmp=clone();
	beg=EulerCircuit(i,end);//Ѱ�Ҵ�i������·����·���������յ��ַ�ֱ���beg��end
	while(true){
		p=beg;
		while(p->next!=NULL){
			if (verList[p->next->NodeNum].head!=NULL) break;
			else p=p->next;
		}
		if (p->next==NULL) break;
		q=p->next;//����δ���ʵĽ��
		tb=EulerCircuit(q->NodeNum,te);//�Ӵ˽�㿪ʼ�����������
		te->next=q->next;//����������·��ƴ�ӵ�ԭ����·����
		p->next=tb;
		delete q;
	}
	delete [] verList;
	verList=tmp;
	cout<<"ŷ����·��:"<<endl;
	while (beg!=NULL){
		cout<<verList[beg->NodeNum].ver<<'\t';
		p=beg;
		beg=beg->next;
		delete p;
	}
	cout<<endl;
}
template <class TypeOfVer,class TypeOfEdge>
typename adjListGraph<TypeOfVer,TypeOfEdge>::verNode* adjListGraph<TypeOfVer,TypeOfEdge>::clone() const{
	verNode* tmp=new verNode[Vers];
	edgeNode *p;
	for (int i=0;i<Vers;++i){
		tmp[i].ver=verList[i].ver;
		p=verList[i].head;
		while (p!=NULL){
			tmp[i].head=new edgeNode(p->end,p->weight,tmp[i].head);
			p=p->next;
		}
	}
	return tmp;
}
template <class TypeOfVer,class TypeOfEdge>
typename adjListGraph<TypeOfVer,TypeOfEdge>::EulerNode* adjListGraph<TypeOfVer,TypeOfEdge>::EulerCircuit(int start,EulerNode* &end){
	EulerNode *beg;
	int nextNode;
	beg=end=new EulerNode(start);
	while (verList[start].head!=NULL){
		nextNode=verList[start].head->end;
		remove(start,nextNode);
		remove(nextNode,start);
		start=nextNode;
		end->next=new EulerNode(start);
		end=end->next;
	}
	return beg;
}
template <class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge>::topSort() const{
	linkQueue<int> q;
	edgeNode* p;
	int current;
	int *inDegree=new int[Vers];
	for (int i=0;i<Vers;++i) inDegree[i]=0;
	for (int i=0;i<Vers;++i){
		for (p=verList[i].head;p!=NULL;p=p->next){
			++inDegree[p->end];
		}
	}
	for (int i=0;i<Vers;++i){
		if (inDegree[i]==0) q.enQueue(i);
	}
	cout<<"��������Ϊ:"<<endl;
	while (!q.isEmpty()){
		current=q.deQueue();
		cout<<verList[current].ver<<'\t';
		for (p=verList[current].head;p!=NULL;p=p->next){
			if (--inDegree[p->end]==0) q.enQueue(p->end);
		}
	}
	cout<<endl;
}