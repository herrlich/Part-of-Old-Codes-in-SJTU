#include <iostream>
#include <cmath>
using namespace std;
int solute(double a,double b,double c,double &px1,double &px2);
int main()
{
	double a,b,c,x1,x2;
	int type;
	cout<<"�����뷽�̵ĸ���ϵ��"<<endl;
	cin>>a>>b>>c;
	type=solute(a,b,c,x1,x2);
	switch(type){
	case 0:cout<<"����һԪ���η���\n";break;
	case 1:cout<<"�޸�\n";break;
	case 2:cout<<"��������ȵĸ�:"<<x1<<endl;break;
	case 3:cout<<"����������ȵĸ�:"<<x1<<" "<<x2<<endl;
	}
	return 0;
}
int solute(double a,double b,double c,double &px1,double &px2)
{
	double delta;
	delta=b*b-4*a*c;
	if (a==0) return 0;
	if (delta<0) return 1;
	if (delta==0){
		px1=(-b)/(2*a);
		return 2;
	}
	px1=(-b+sqrt(delta))/(2*a);
	px2=(-b-sqrt(delta))/(2*a);
	return 3;
}