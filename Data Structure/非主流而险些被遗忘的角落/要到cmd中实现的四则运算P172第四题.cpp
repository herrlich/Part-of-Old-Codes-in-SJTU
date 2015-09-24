#include <iostream>
using namespace std;
int main(int argc,char** argv){
	if (argc!=4) {cout<<"参数个数错误\n";return 0;}
	double result,a,b;
	char op=*argv[2];//或者argv[2][0],这样才得到了“+”串中的‘+’
	a=atof(argv[1]);
	b=atof(argv[3]);
	switch(op){
	case '+'://貌似‘+’可以被看做整型常量，而“+”不能
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