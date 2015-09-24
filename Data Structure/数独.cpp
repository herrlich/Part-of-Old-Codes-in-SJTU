#include <iostream>
using namespace std;
int main()
{
	int num,i,j,k,s,t,q,**list,compare[9]={0},*p;
	list=new int*[9];
	for (i=0;i<9;++i) list[i]=new int[9];
	cin>>num;
	p=new int [num];
	for (i=0;i<num;++i) p[i]=1;
	for (i=0;i<num;++i){
		for (j=0;j<9;++j){
			for (k=0;k<9;++k){
				cin>>list[j][k];
			}
		}
		for (s=0;s<9;++s){
			for (t=0;t<9;++t){
				compare[list[s][t]-1]+=1;
			}
			for (q=0;q<9;++q){
				if (compare[q]>1){
					p[i]=0;
					break;
				}
			}
			for (q=0;q<9;++q) compare[q]=0;
			if (p[i]==0) break;
		}
		if (p[i]==1){
			for (t=0;t<9;++t){
				for (s=0;s<9;++s){
					compare[list[s][t]-1]+=1;
				}
				for (q=0;q<9;++q){
					if (compare[q]>1){
						p[i]=0;
						break;
					}
				}
				for (q=0;q<9;++q) compare[q]=0;
				if (p[i]==0) break;
			}
		}
		if (p[i]==1){
			for (s=0;s<3;s++){
				for (t=0;t<3;t++) {
					compare[list[3*s][3*t]-1]+=1;
					compare[list[3*s][3*t+1]-1]+=1;
					compare[list[3*s][3*t+2]-1]+=1;
					compare[list[3*s+1][3*t]-1]+=1;
					compare[list[3*s+1][3*t+1]-1]+=1;
					compare[list[3*s+1][3*t+2]-1]+=1;
					compare[list[3*s+2][3*t]-1]+=1;
					compare[list[3*s+2][3*t+1]-1]+=1;
					compare[list[3*s+2][3*t+2]-1]+=1;
					for (q=0;q<9;++q){
						if (compare[q]>1){
							p[i]=0;
							break;
						}
					}
					for (q=0;q<9;++q) compare[q]=0;
					if (p[i]==0) break;
				}
			}
		}
	}
	for (i=0;i<num;++i){
		if (p[i]==1) cout<<"Right\n";
		else cout<<"Wrong\n";
	}
	delete [] p;
	for (i=0;i<9;++i) delete [] list[i];
	delete list;
	return 0;
}