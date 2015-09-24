#include <iostream>
#include <cstring>
using namespace std;
struct node{
	char data;
	node *left,*right;
	node():left(NULL),right(NULL) {}
	node(char d,node *l=NULL,node *r=NULL):data(d),left(l),right(r) {}
	~node();
};
void postorder(const char* p1,const char* p2,const char* m1,const char* m2);
int main(){
	char pre[27],mid[27];
	cin>>pre;
	cin>>mid;
	int len1=strlen(pre);
	int len2=strlen(mid);
	postorder(pre,pre+len1,mid,mid+len2);
	return 0;
}
void postorder(const char* p1,const char* p2,const char* m1,const char* m2){
	char root=*p1;
	int len=p2-p1,i=0;
	for (i=0;*(m1+i)!=root;++i);
	if (i!=0) postorder(p1+1,p1+i,m1,m1+i-1);
	if (i!=len) postorder(p1+i+1,p2,m1+i+1,m2);
	if (root!='\0') cout<<root;
}