//这个程序要插入adjMatrixGraph的类中才有效
#include "adjMatrixGraph.h"
template <class TypeOfVer,class TypeOfEdge>
void adjMatrixGraph<TypeOfVer,TypeOfEdge>::floyd() const{
	TypeOfEdge** d=new TypeOfEdge*[Vers];
	int **prev=new int*[Vers];
	int i,j,k;
	for (i=0;i<Vers;++i){
		d[i]=new TypeOfEdge[Vers];
		prev[i]=new int[Vers];
		for (j=0;j<Vers;++j){
			d[i][j]=edge[i][j];
			prev[i][j]=(edge[i][j]!=noEdge)?i:-1;
		}
	}
	for (k=0;k<Vers;++k){
		for (i=0;i<Vers;++i){
			for (j=0;j<Vers;++j){
				if (d[i][k]+d[k][j]<d[i][j]){
					d[i][j]=d[i][k]+d[k][j];
					prev[i][j]=prev[k][j];
				}
			}
		}
	}
	cout<<"最短路径长度:"<<endl;
	for (i=0;i<Vers;++i){
		cout<<endl;
		for (j=0;j<Vers;++j) cout<<d[i][j]<<'\t';
	}
	cout<<"最短路径:"<<endl;
	for (i=0;i<Vers;++i){
		cout<<endl;
		for (j=0;j<Vers;++j) cout<<prev[i][j]<<'\t';
	}
}