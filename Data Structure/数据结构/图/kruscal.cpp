#include "DisjointSet.h"
#include "adjListGraph.h"
#include "priorityQueue.h"
template <class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge>::kruscal() const{
	int edgesAccepted=0,u,v;
	edgeNode* p;
	edge e;
	DisjointSet ds(Vers);
	priorityQueue<edge> pq;
	for (int i=0;i<Vers;++i){
		for (p=verList[i].head;p!=NULL;p=p->next){
			if (i<p->end){
				e.beg=i;
				e.end=p->end;
				e.w=p->weight;
				pq.enQueue(e);
			}
		}
	}
	while (edgesAccepted<Vers-1){
		e=pq.deQueue();
		u=ds.Find(e.beg);
		v=ds.Find(e.end);
		if (u!=v){
			++edgesAccepted;
			ds.Union(u,v);
			cout<<'('<<verList[e.beg].ver<<','<<verList[e.end].ver<<")\t";
		}
	}
}