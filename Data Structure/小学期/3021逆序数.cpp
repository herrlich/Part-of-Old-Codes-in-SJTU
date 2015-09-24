#include <iostream>
using namespace std;
long long count=0;//计数逆序对数的变量
void merge_sort(long long array[],long long low,long long high);//排序函数
void merge_count(long long array[],long long low,long long mid,long long high);//归并并计算逆序对数
int main(){
	int num;
	cin>>num;
	long long* arr=new long long[num];
	for (long long i=0;i<num;++i) cin>>arr[i];
	merge_sort(arr,0,num-1);
	cout<<count<<endl;
	return 0;
}
void merge_sort(long long array[],long long low, long long high){
	if(low<high){
		long long mid=low+(high-low)/2;
		merge_sort(array,low, mid);
		merge_sort(array,mid+1,high);
		merge_count(array,low,mid,high);
	}
}
void merge_count(long long array[],long long low,long long mid,long long high){
	long long length=high-low+1;
	long long *temp=new long long[length]; //存储临时排好序的序列
	long long begin1=low,end1=mid;
	long long begin2=mid+1,end2=high;
	long long k=0;
	while(begin1<=end1&&begin2<=end2){
		//将array[i]和array[j]中小的那个赋给temp[k]
		if(array[begin1]<=array[begin2]) temp[k++]=array[begin1++];
		else{
			temp[k++]=array[begin2++];
			count+=end1-begin1+1;
		}
	}
	//当在上文的循环中某数组没有处理完的时候，把剩下的元素直接赋给temp[k]
	while(begin1<=end1) temp[k++]=array[begin1++];
	while(begin2<=end2) temp[k++]=array[begin2++];
	//把临时数组中的元素赋给array
	for(long long i=0;i<k;++i) array[low+i]=temp[i];
	delete [] temp;
}