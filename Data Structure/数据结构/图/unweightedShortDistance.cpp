template <class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge>::unweightedShortDistance(TypeOfVer start,TypeOfEdge noEdge) const{
	linkQueue<int> q;
	TypeOfEdge *distance=new TypeOfEdge[Vers];
	int *prev=new int[Vers];
	int u,sNo;
	edgeNode* p;
	for (int i=0;i<Vers;++i) distance[i]=noEdge;
	for (sNo=0;sNo<Vers;++sNo) if (verList[sNo].ver==start) break;
	if (sNo==Vers){
		cout<<"起始结点不存在"<<endl;
		return;
	}
	distance[sNo]=0;
	prev[sNo]=sNo;
	q.enQueue(sNo);
	while (!q.isEmpty()){
		u=q.deQueue();
		for (p=verList[u].head;p!=NULL;p=p->next){
			if (distance[p->end]==noEdge){
				distance[p->end]=distance[u]+1;
				prev[p->end]=u;
				q.enQueue(p->end);
			}
		}
	}
	for (int i=0;i<Vers;++i){
		cout<<"从"<<start<<"到"<<verList[i].ver<<"的路径为:"<<endl;
		printPath(sNo,i,prev);
		cout<<endl;
	}
}
template <class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge>::printPath(int start,int end,int prev[]) const{
	if (start==end){
		cout<<verList[start].ver;
		return;
	}
	printPath(start,prev[end],prev);
	cout<<"-"<<verList[end].ver;
}