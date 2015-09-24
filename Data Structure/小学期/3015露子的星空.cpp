#include <iostream>
#include <cstdio>
using namespace std;
class disjoint{
private:
	int size;
public:
	int parent[100001];
	disjoint(int size);
	void Union(int r1,int r2);
	int find(int num);
};
disjoint::disjoint(int size){
	for (int i=0;i<size;++i) parent[i]=-1;
}
void disjoint::Union(int root1,int root2){
	if (root1==root2) return;
	if (parent[root1]<parent[root2]){
		parent[root1]+=parent[root2];
		parent[root2]=root1;
	}
	else {
		parent[root2]+=parent[root1];
		parent[root1]=root2;
	}
}
int disjoint::find(int num){
	if (parent[num]<0) return num;
	return parent[num]=find(parent[num]);
}
int array[100001];
int main(){
	int i,n,m,x,y,total=0;
	char choice[5];
	for (i=0;i<100001;++i) array[i]=-4;
	scanf("%d",&n);
	scanf("%d",&m);
	disjoint star(n+1);
	for (i=0;i<m;++i){
		scanf("%s",choice);
		if (choice[0]=='a'){
			scanf("%d",&x);
			scanf("%d",&y);
			if (star.parent[x]==-1&&star.parent[y]==-1){
				++total;
				star.Union(x,y);
				continue;
			}
			if (star.find(x)==star.find(y)){
				star.Union(star.find(x),star.find(y));
				continue;
			}
			if (star.parent[star.find(x)]<-1&&star.parent[star.find(y)]<-1){
				--total;
				star.Union(star.find(x),star.find(y));
				continue;
			}
			star.Union(star.find(x),star.find(y));
		}
		if (choice[0]=='b') array[i]=total;
		if (choice[0]=='c'){
			scanf("%d",&x);
			scanf("%d",&y);
			if (star.find(x)!=-1&&star.find(x)==star.find(y)) array[i]=-3;
			else array[i]=-2;
		}
	}
	for (i=0;i<m;++i){
		switch(array[i]){
		case -4:continue;
		case -3:printf("YES\n");break;
		case -2:printf("NO\n");break;
		default:printf("%d\n",array[i]);
		}
	}
	return 0;
}