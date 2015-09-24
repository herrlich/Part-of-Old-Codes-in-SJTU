#include <iostream>
using namespace std;
struct node{
    int like,pos,group;
	node *next;
    node(int l,int p,int g) {like=l;pos=p;group=g;next=NULL;}
	node() {next=NULL;}
    node operator=(const node &a){
        like=a.like;
        pos=a.pos;
        group=a.group;
		next=a.next;
        return *this;
	}
    bool operator<(const node &a) const{
        if (like<a.like) return true;
        if (like>a.like) return false;
        if (group<a.group) return true;
        return false;
    }
};
template <class Type>
void percolateDown(Type array[],int hole,int currentSize){
    int child;
    Type tmp=array[hole];
    for (;hole*2+1<currentSize;hole=child){
        child=hole*2+1;
        if (child!=currentSize-1&&array[child+1]<array[child]) ++child;
        if (array[child]<tmp) array[hole]=array[child];
        else break;
    }
    array[hole]=tmp;
}
int love[50001];
node pile[50001];
node *cube[50001];
int main(){
    int n,m,i,j,position,times=0,length;
    cin>>n>>m;
	node *p;
    for (i=1;i<=n;++i) cin>>love[i];
    for (i=0;i<m;++i){
        cin>>length;
		cube[i]=NULL;
        for (j=0;j<length;++j){
			cin>>position;
			p=cube[i];
			if (cube[i]==NULL) cube[i]=new node(love[position],position,i);
			else{
				while(p->next!=NULL) p=p->next;  
				p->next=new node(love[position],position,i);
			}
		}
	}
	for (i=0;i<m;++i){
		if (cube[i]!=NULL){
			p=cube[i];
			pile[times].group=cube[i]->group;
			pile[times].like=cube[i]->like;
			pile[times].pos=cube[i]->pos;
			cube[i]=p->next;
			delete p;
			++times;
		}
	}
	for (int i=times/2-1;i>=0;--i) percolateDown(pile,i,times);
	for (i=0;i<n;++i){
		cout<<pile[0].pos<<'\n';
		if (cube[pile[0].group]!=NULL){
			pile[0]=*cube[pile[0].group];
			p=cube[pile[0].group];
			cube[pile[0].group]=cube[pile[0].group]->next;
			delete p;
			percolateDown(pile,0,times);
		}
		else{
			pile[0]=pile[times-1];
			--times;
			percolateDown(pile,0,times);
		}
	}
	return 0;
}