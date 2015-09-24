#include <vector>
template <class Type>
int binarySearch(const vector<Type> &data,const Type &x){
	int low=1,high=data.size(),mid;
	while(low<=high){
		mid=(low+high)/2;
		if (data[mid]==x) return mid;
		if (x<data[mid]) high=mid-1;
		else low=mid+1;
	}
	return 0;
}