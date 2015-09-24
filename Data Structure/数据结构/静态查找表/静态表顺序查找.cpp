#include <vector>
template <class Type>
int seqsearch(vector<Type>&data,const Type &x){
	data[0]=x;
	int i;
	for (i=data.size();x!=data[i];--i);
	return i;
}