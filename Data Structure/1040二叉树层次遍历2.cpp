#include <iostream> 
#include <queue> 
using namespace std; 
int main(){
	queue<int> q;
	int *left,*right,n,i,num;
	cin>>n;
	left=new int[n];
	right=new int[n];
	for (i=0;i<n;++i){
		left[i]=-1;
		right[i]=-1;
	}
	for (i=1;i<n;++i){
		cin>>num;
		if (left[num]==-1) left[num]=i;
		else right[num]=i;
	}
	q.push(0);
	while (!q.empty()){
		cout<<q.front()<<' ';
		if (left[q.front()]!=-1) q.push(left[q.front()]);
		if (right[q.front()]!=-1) q.push(right[q.front()]);
		q.pop();
	}
	return 0;
}