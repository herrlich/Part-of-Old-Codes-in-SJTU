#include <iostream>
using namespace std;
int main(int argc,char** argv){
	if (argc!=4) {cout<<"������������\n";return 0;}
	double result,a,b;
	char op=*argv[2];//����argv[2][0],�����ŵõ��ˡ�+�����еġ�+��
	a=atof(argv[1]);
	b=atof(argv[3]);
	switch(op){
	case '+'://ò�ơ�+�����Ա��������ͳ���������+������
		result=a+b;break;
	case '-':
		result=a-b;break;
	case '*':
		result=a*b;break;
	case '/':
		result=a/b;break;
	}
	cout<<a<<op<<b<<"="<<result<<endl;
	return 0;
}