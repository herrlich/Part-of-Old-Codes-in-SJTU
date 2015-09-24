#include <iostream> 
using namespace std; 
char a[1111][1111]; 
int main(){ 
    int w,h; 
    int up,down,left,right,cen1,cen2; 
    double distance_square=0,tmp=0,area=0,area2,asdf; 
    cin>>w>>h; 
    for (int i=0;i<h;i++) for (int j=0;j<w;j++) { 
        cin>>a[i][j]; 
        if (a[i][j]=='1') area++; 
    } 
    for (int i=0;i<h;i++){ 
        for (int j=0;j<w;j++){ 
            if (a[i][j]=='1') { 
                up=i; 
                i=h; 
                break; 
            } 
        } 
    } 
    for (int i=h-1;i>=0;i--){ 
        for (int j=0;j<w;j++){ 
            if (a[i][j]=='1') { 
                down=i; 
                i=0; 
                break; 
            } 
        } 
    } 
    for (int i=0;i<w;i++){ 
        for (int j=0;j<h;j++){ 
            if (a[j][i]=='1') { 
                left=i; 
                i=w; 
                break; 
            } 
        } 
    } 
    for (int i=w-1;i>=0;i--){ 
        for (int j=0;j<h;j++){ 
            if (a[j][i]=='1') { 
                right=i; 
                i=0; 
                break; 
            } 
        } 
    } 
    cen1=(up+down)/2; 
    cen2=(left+right)/2; 
    for (int i=0;i<h;i++){ 
        for (int j=0;j<w;j++){ 
            if (a[i][j]=='1'){ 
                tmp = (cen1-i)*(cen1-i)+(cen2-j)*(cen2-j); 
                if (tmp>distance_square) distance_square = tmp; 
            } 
        } 
    } 
    area2 = 3.1415926*distance_square; 
    asdf = area/area2; 
    if (asdf>0.9) cout<<"circle"; //根据面积比例来判断形状
    else if(asdf>0.6) cout<<"square"; 
    else cout<<"triangle"; 
    return 0; 
} 