template <class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge>::dijkstra(TypeOfVer start,TypeOfEdge noEdge)const{
	TypeOfEdge *distance=new TypeOfEdge[Vers];
	int *prev=new int[Vers];
	bool *known=new bool[Vers];
	int u,sNo,i,j;
	edgeNode *p;
	TypeOfEdge min;
	for (i=0;i<Vers;++i){
		known[i]=false;
		distance[i]=noEdge;
	}
	for (sNo=0;sNo<Vers;++sNo){
		if (verList[sNo].ver==start) break;
	}
	if (sNo==Vers){
		cout<<"起始结点不存在"<<endl;
		return;
	}
	distance[sNo]=0;
	prev[sNo]=sNo;
	for (i=1;i<Vers;++i){
		min=noEdge;
		for (j=0;j<Vers;++j){
			if (!known[j]&&distance[j]<min){
				min=distance[j];
				u=j;
			}
		}
		known[u]=true;
		for (p=verList[u].head;p!=NULL;p=p->next){
			if (!known[p->end]&&distance[p->end]>min+p->weight){
				distance[p->end]=min+p->weight;
				prev[p->end]=u;
			}
		}
	}
	for (i=0;i<Vers;++i){
		cout<<"从"<<start<<"到"<<verList[i].ver<<"的路径为："<<endl;
		printPath(sNo,i,prev);
		cout<<"\t长度为:"<<distance[i]<<endl;
	}
}