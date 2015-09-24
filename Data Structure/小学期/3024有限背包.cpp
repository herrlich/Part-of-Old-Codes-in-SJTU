#include <iostream> 
#include <algorithm> 
using namespace std;  
int main(){ 
	int m,n,i,j,k,num[1001],weight[1001],value[1001],total[1001]={0}; //n为物品总数,m为背包容量
    cin>>n>>m; 
    for (i=1;i<=n;++i) cin>>num[i]>>weight[i]>>value[i]; 
    for (i=1;i<=n;++i){ 
        for (j=m;j>=0;--j){ 
            for (k=1;k<=num[i];++k){ 
                if ((j-k*weight[i]>=0)&&(total[j-k*weight[i]]>=0)){
					total[j]=max(total[j],total[j-k*weight[i]]+k*value[i]);
                } 
                else break; 
            } 
        } 
    } 
    int result=0; 
    for (i=1;i<=m;++i) result=max(result,total[i]); 
    cout<<result<<endl; 
    return 0; 
} 