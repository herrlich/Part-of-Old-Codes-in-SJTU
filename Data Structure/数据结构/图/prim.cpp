#include "DisjointSet.h"
#include "adjListGraph.h"
#include "priorityQueue.h"
template <class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge>::prim(TypeOfEdge noEdge) const{
	bool *flag=new bool[Vers];
	TypeOfEdge *lowCost=new TypeOfEdge[Vers];
	int *startNode=new int[Vers];
	edgeNode *p;
	TypeOfEdge min;
	int start,i,j;
	for (i=0;i<Vers;++i){
		flag[i]=false;
		lowCost[i]=noEdge;
	}
	start=0;
	for (i=1;i<Vers;++i){
		for (p=verList[start].head;p!=NULL;p=p->next){
			if (!flag[p->end]&&lowCost[p->end]>p->weight){
				lowCost[p->end]=p->weight;
				startNode[p->end]=start;
			}
		}
		flag[start]=true;
		min=noEdge;
		for (j=0;j<Vers;++j){
			if (lowCost[j]<min){
				min=lowCost[j];
				start=j;
			}
		}
		cout<<'('<<verList[startNode[start]].ver<<','<<verList[start].ver<<")\t";
		lowCost[start]=noEdge;
	}
	delete [] flag;
	delete [] startNode;
	delete [] lowCost;
}