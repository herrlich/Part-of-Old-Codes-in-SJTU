#include <iostream> 
#include <iomanip> 
using namespace std; 
class MyComplex{ 
private: 
  double x,y; 
public: 
    MyComplex(double a,double b) {x=a;y=b;} 
    MyComplex(){x=0;y=0;} 
    MyComplex operator +(const MyComplex &z2) const {return MyComplex(x+z2.x,y+z2.y);} 
    MyComplex operator -(const MyComplex &z2) const {return MyComplex(x-z2.x,y-z2.y);} 
    MyComplex operator *(const MyComplex &z2) const {return MyComplex(x*z2.x-y*z2.y,x*z2.y+y*z2.x);} 
    MyComplex operator /(const MyComplex &z2) const {return MyComplex((x*z2.x+y*z2.y)/(z2.x*z2.x+z2.y*z2.y),(y*z2.x-x*z2.y)/(z2.x*z2.x+z2.y*z2.y));} 
    MyComplex operator +=(const MyComplex &z2) {return MyComplex(x+z2.x,y+z2.y);} 
    MyComplex operator -=(const MyComplex &z2) {return MyComplex(x,y);} 
    MyComplex operator *=(const MyComplex &z2) {return MyComplex(x*z2.x-y*z2.y,x*z2.y+y*z2.x);} 
    MyComplex operator /=(const MyComplex &z2) {return MyComplex(x,y);} 
    friend istream& operator >> (istream &is,MyComplex &z) {is>>z.x;is>>z.y;return is;} 
    friend ostream& operator << (ostream &os,const MyComplex &z) {os.setf(ios::fixed);os<<setprecision(2);os<<z.x<<'\t'<<z.y;return os;} 
}; //os.setf(ios::fixed);os<<setprecision(2);用来控制小数位数为两位
int main() 
{ 
    MyComplex z1; 
    MyComplex z2; 
    cin >> z1 >> z2; 
    cout << z1 + z2 <<endl; 
    cout << z1 - z2 <<endl; 
    cout << z1 * z2 <<endl; 
    cout << z1 / z2 <<endl; 
    cout << (z1 += z2) <<endl; 
    cout << (z1 -= z2) <<endl; 
    cout << (z1 *= z2) <<endl; 
    cout << (z1 /= z2) <<endl; 
    return 0; 
}