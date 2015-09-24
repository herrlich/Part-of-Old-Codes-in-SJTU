#include <iostream>
#include <cstring> 
using namespace std;
class calc{
	enum Type {Data,Add,Minus,Times,Divide,Open,Close,EOL,EXP};
	//定义了可能出现的数据类型：Data为数字，Add为加号，Minus为减号，Times为乘号，Divide为除号，Open为开括号，Close为闭括号，EXP为乘方。
	//在这个程序中，结束符用EOF代替，可以根据自己需要而换成某个特定的符号。
	struct node{//定义了树的结点，type为节点存储的数据类型，data为数字的值。
		Type type;
		int data;
		node *left,*right;
		node(Type t,int d=0,node *l=NULL,node *r=NULL) {type=t;data=d;left=l;right=r;}//节点初始化。
	};
	node *root;
	int typelen;//是下文中判断是否有两个运算符紧连着时所用的变量，我觉得放这里显眼点，要不老是找不着。。。
	int array[100];//同上
	node *create(char* &s); //创建一棵树
	Type getOp(char* &s,int &value);//得到树上结点的符号，为运算做准备
	int result(node *t);//计算时候的函数
	void bracket(char *&s);//判断括号是否匹配的函数
	void checkOp(int arr[],char *&s);//判断运算符之间是否有运算数的函数
public:
	calc(char *s) {
		char *t=s,*u=s;//用于括号匹配及判断运算符之间是否有数的赋值
		root=create(s);
		bracket(t);//检验(不说了，见上面的注释)
		checkOp(array,u);//同上
	}
	int result(){
		if (root==NULL) return 0;
		return result(root);//调用私有函数
	}
};

calc::node *calc::create(char* &s){
	node *p,*root=NULL;
	Type returnType;
	int value;
	while (*s){
		returnType=getOp(s,value);//得到运算符，为下文树的构建做准备
		if (returnType==Data&&root!=NULL){
			node *flag=root;
			while (flag->right!=NULL) flag=flag->right;
			if (flag->type==EXP){
				p=new node(Data,value);
				flag->right=p;
				continue;
			}
		}
		//上面的程序是将乘方运算符插入数的最右一棵子树的最右边节点中，因为乘方运算符是右结合的，而且优先级在运算符中最高
		switch(returnType){
		case Data:
		case Open:
			if (returnType==Data) p=new node(Data,value);
			else p=create(s);
			if ((returnType==Data)&&(root!=NULL)){//当根节点为空时跳过
				int t=0;
				while (t<2){
					if (*(--s)!=' ') ++t;
				}//取乘方号以前的运算符。
				if (getOp(s,value)==EXP){
					node *tmp=root;
					while (tmp->right!=NULL) tmp=tmp->right;
					tmp->right=p;
					getOp(s,value);
				    break;
				}//如果前一个运算符为乘方，则将数字放在最右子树的右儿子
				getOp(s,value);//还原s应有位置
			}
			if (root==NULL) root=p;
			else{
				if (root->right==NULL) root->right=p;
				else root->right->right=p;
			}
			break;
			//如果是开括号，就另外构建一棵树。
			//如果是数字，就插入树上。其中，如果根节点为空，及插入根节点；如果根节点没有右子树，就插入根节点的右儿子中；否则插入根节点右儿子的右儿子中。
		case Close:
		case EOL:return root;//闭括号和结束符直接返回现在的树。
		case Add:
		case Minus:
			root=new node(returnType,0,root);
			break;//加减法优先级最低，因此将其作为新树的根重新构建一棵树。
		case Times:
		case Divide:
			if (root->type==Data || root->type==Divide || root->type==Times || root->type==EXP){
				root=new node(returnType,0,root);
				break;
			}
			//乘除法优先级高于加减法，因此如果根节点为数据或乘除法或乘方，则将现在得到的乘号或除号作为根节点
			else {
				if (root->type==Add || root->type==Minus){//如果根节点是加号或减号，则先判断这个加号或减号是不是由括号括起来的。
					int t=0;
					while (t<2){
						if (*(--s)!=' ') ++t;
					}//取乘号或除号以前的运算符。
					if (getOp(s,value)==Close){
						root=new node(returnType,0,root);
						getOp(s,value);
					}//如果是，则将得到的乘号或除号作为根节点。
					else{
						getOp(s,value);
						root->right=new node(returnType,0,root->right);
					}
					//如果不是，则将现在得到的乘号或除号作为根节点的右儿子重新建树
				}
				else root->right=new node(returnType,0,root->right);
				break;
			}
		case EXP:
			if (root->type==Data || root->type==Divide || root->type==Times || root->type==Add||root->type==Minus){
				if ((root->type==Data)&&(root->right==NULL&&root->left==NULL)){
					root=new node(EXP,0,root);
					break;
				}//如果根节点只有数字，则将乘方作为根节点。
				int t=0;
				while (t<2){
					if (*(--s)!=' ') ++t;
				}//取乘方以前的运算符。
				if (getOp(s,value)==Close){
					root=new node(returnType,0,root);
					getOp(s,value);
					break;
				}//判断是否有括号以进行优先级运算
				getOp(s,value);//将s还原至应有位置
			}
			if (root->right!=NULL){
				node *tmp=root;
				while (tmp->right->right!=NULL) tmp=tmp->right;
				tmp->right=new node(EXP,0,tmp->right);
			}
			else root=new node(EXP,0,root);
			//如果根节点的右儿子不为空，则由于乘方优先级最高，将其放入最右边子树的右儿子中，并以这个节点作为最右边结点构建的新子树的根节点，调整树的结构
			//否则将其作为根节点的右儿子。
		}
	}
	return root;
}

calc::Type calc::getOp(char* &s,int &data){
	char type;
	while (*s==' ') ++s;
	if (*s>='0' && *s<='9'){
		data=0;
		while (*s>='0' && *s<='9') {data=data*10+*s-'0';++s;}
		return Data;
	}//用来完整地读取数字
	if (*s=='\0') return EOL;
	type=*s;++s;
	switch(type){
	case '+':return Add;
	case '-':return Minus;
	case '*':return Times;
	case '/':return Divide;
	case '(':return Open;
	case ')':return Close;
	case '^':return EXP;
	default:return EOL;
	}
}

int calc::result(node *t){
	int num1,num2;
	if (t->type==Data) return t->data;
	num1=result(t->left);
	num2=result(t->right);
	//上面三行为递归计算过程
	switch(t->type){
	case Add:t->data=num1+num2;break;
	case Minus:t->data=num1-num2;break;
	case Times:t->data=num1*num2;break;
	case Divide:
		if (num2==0){
			cout<<"除数不能为零"<<endl;
			exit(1);
		}
		t->data=num1/num2;break;
	case EXP:
		if (num1==0&&num2==0){
			cout<<"指数和底数不能同时为零"<<endl;
			break;
		}
		if (num1==0&&num2<0){
			cout<<"零不能做分母"<<endl;
			exit(1);
		}
		int tmp=1;//保证了当0不是分母时，一个整数的0次方为1.
		for (int i=0;i<num2;++i) tmp*=num1;
		t->data=tmp;
	}
	return t->data;
}

void calc::bracket(char *&s){//验证括号是否匹配，与oj上的原理相同
    int j,temp=1;
    char col[100];
    int len=0,le[51],ri[51],left=0,right=0; 
    while (*s!='\0'){//将括号从表达式中提取出来，存储在一个数组中
		if (*s==')'||*s=='('){
			col[len]=*s;
			++len;
		}
		++s;
	}
    if (len%2!=0) temp=0;
    for (j=0;j<len;++j){
        if (col[j]=='('){
			le[left]=j;
            ++left;
        }
		else{
            ri[right]=j;
            ++right;
		}
	}
	if (right!=left) temp=0;
    for (j=0;j<len/2;++j){
        if (le[j]>ri[j]){
            temp=0;
        }
    }
    if (temp!=1){
		cout<<"括号不匹配!"<<endl;
		exit(1);
	}
}

void calc::checkOp(int arr[],char *&s){
	typelen=0;
	while (*s!='\0'){
		while (*s==' ') ++s;
		if (*s>='0' && *s<='9'){
			while (*s>='0' && *s<='9') ++s;
			array[typelen]=0;
			++typelen;
			continue;
		}
		else{
			if (*s=='+'||*s=='-'||*s=='*'||*s=='^'||*s=='/') array[typelen]=1;
			if (*s=='(') array[typelen]=2;
			if (*s==')') array[typelen]=3;
			++s;
			++typelen;
		}
	}//用数组存储运算符和数字，运算符为1，数字为0,左括号为2，右括号为3
	for (int i=0;i<typelen-2;++i){
		if ((array[i]==0)&&(array[i+1]==1)&&(array[i+2]==1)){
				cout<<"运算符输入有误！"<<endl;//接连出现两个不是括号的运算符时，报错,中止
				exit(1);
		}
		if ((array[i]==0)&&(array[i+1]==2)||(array[i]==3)&&(array[i+1]==0)){
			//左括号后面直接有一个数字或右括号后面直接有一个数字时报错
			cout<<"运算符输入有误！"<<endl;
			exit(1);
		}
		if ((array[i]==2)&&(array[i+1]==3)){
			cout<<"括号输入有误！"<<endl;
			exit(1);
		}//两个括号间没有任何数字或运算时，报错
	}
	if (array[typelen-1]==1||array[0]==1){//运算时首或尾为运算符时，报错
		cout<<"运算符输入有误！"<<endl;
		exit(1);
	}
}