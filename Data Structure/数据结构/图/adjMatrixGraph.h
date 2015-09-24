#include "graph_abstract.h"
template <class TypeOfVer,class TypeOfEdge>
class adjMatrixGraph:public graph<TypeOfEdge>{
public:
	adjMatrixGraph(int vSize,const TypeOfVer d[],const TypeOfEdge noEdgeFlag);
	bool insert(int u,int v,TypeOfEdge w);
	bool remove(int u,int v);
	bool exist(int u,int v)const;
	~adjMatrixGraph();
private:
	TypeOfEdge **edge;//存放邻接矩阵
	TypeOfVer *ver;//存放结点值
	TypeOfEdge noEdge;//邻接矩阵中的∞的表示值
};
template <class TypeOfVer,class TypeOfEdge>
adjMatrixGraph<TypeOfVer,TypeOfEdge>::adjMatrixGraph(int vSize,const TypeOfVer d[],const TypeOfEdge noEdgeFlag){
	int i,j;
	Vers=vSize;
	Edges=0;
	noEdge=noEdgeFlag;
	ver=new TypeOfVer[Vers];
	for (i=0;i<Vers;++i) ver[i]=d[i];
	edge=new TypeOfEdge*[Vers];
	for (i=0;i<Vers;++i){
		edge[i]=new TypeOfEdge[Vers];
		for (j=0;j<Vers;++j){
			edge[i][j]=noEdge;
		}
		edge[i][i]=0;
	}
}
template <class TypeOfVer,class TypeOfEdge>
adjMatrixGraph<TypeOfVer,TypeOfEdge>::~adjMatrixGraph(){
	delete [] ver;
	for (int i=0;i<Vers;++i) delete [] edge[i];
	delete [] edge;
}
template <class TypeOfVer,class TypeOfEdge>
bool adjMatrixGraph<TypeOfVer,TypeOfEdge>::insert(int u,int v,TypeOfEdge w){
	if (u<0||u>Vers-1||v<0||v>Vers-1) return false;
	if (edge[u][v]!=noEdge) return false;
	edge[u][v]=w;
	++Edges;
	return true;
}
template <class TypeOfVer,class TypeOfEdge>
bool adjMatrixGraph<TypeOfVer,TypeOfEdge>::remove(int u,int v){
	if (u<0||u>Vers-1||v<0||v>Vers-1) return false;
	if (edge[u][v]==noEdge) return false;
	edge[u][v]=noEdge;
	--Edges;
	return true;
}
template <class TypeOfVer,class TypeOfEdge>
bool adjMatrixGraph<TypeOfVer,TypeOfEdge>::exist(int u,int v)const{
	if (u<0||u>Vers-1||v<0||v>Vers-1) return false;
	if (edge[u][v]==noEdge) return false;
	else return true;
}