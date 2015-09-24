#include <iostream>
#include <cstring> 
using namespace std;
class calc{
	enum Type {Data,Add,Minus,Times,Divide,Open,Close,EOL,EXP};
	//�����˿��ܳ��ֵ��������ͣ�DataΪ���֣�AddΪ�Ӻţ�MinusΪ���ţ�TimesΪ�˺ţ�DivideΪ���ţ�OpenΪ�����ţ�CloseΪ�����ţ�EXPΪ�˷���
	//����������У���������EOF���棬���Ը����Լ���Ҫ������ĳ���ض��ķ��š�
	struct node{//���������Ľ�㣬typeΪ�ڵ�洢���������ͣ�dataΪ���ֵ�ֵ��
		Type type;
		int data;
		node *left,*right;
		node(Type t,int d=0,node *l=NULL,node *r=NULL) {type=t;data=d;left=l;right=r;}//�ڵ��ʼ����
	};
	node *root;
	int typelen;//���������ж��Ƿ������������������ʱ���õı������Ҿ��÷��������۵㣬Ҫ�������Ҳ��š�����
	int array[100];//ͬ��
	node *create(char* &s); //����һ����
	Type getOp(char* &s,int &value);//�õ����Ͻ��ķ��ţ�Ϊ������׼��
	int result(node *t);//����ʱ��ĺ���
	void bracket(char *&s);//�ж������Ƿ�ƥ��ĺ���
	void checkOp(int arr[],char *&s);//�ж������֮���Ƿ����������ĺ���
public:
	calc(char *s) {
		char *t=s,*u=s;//��������ƥ�估�ж������֮���Ƿ������ĸ�ֵ
		root=create(s);
		bracket(t);//����(��˵�ˣ��������ע��)
		checkOp(array,u);//ͬ��
	}
	int result(){
		if (root==NULL) return 0;
		return result(root);//����˽�к���
	}
};

calc::node *calc::create(char* &s){
	node *p,*root=NULL;
	Type returnType;
	int value;
	while (*s){
		returnType=getOp(s,value);//�õ��������Ϊ�������Ĺ�����׼��
		if (returnType==Data&&root!=NULL){
			node *flag=root;
			while (flag->right!=NULL) flag=flag->right;
			if (flag->type==EXP){
				p=new node(Data,value);
				flag->right=p;
				continue;
			}
		}
		//����ĳ����ǽ��˷������������������һ�����������ұ߽ڵ��У���Ϊ�˷���������ҽ�ϵģ��������ȼ�������������
		switch(returnType){
		case Data:
		case Open:
			if (returnType==Data) p=new node(Data,value);
			else p=create(s);
			if ((returnType==Data)&&(root!=NULL)){//�����ڵ�Ϊ��ʱ����
				int t=0;
				while (t<2){
					if (*(--s)!=' ') ++t;
				}//ȡ�˷�����ǰ���������
				if (getOp(s,value)==EXP){
					node *tmp=root;
					while (tmp->right!=NULL) tmp=tmp->right;
					tmp->right=p;
					getOp(s,value);
				    break;
				}//���ǰһ�������Ϊ�˷��������ַ��������������Ҷ���
				getOp(s,value);//��ԭsӦ��λ��
			}
			if (root==NULL) root=p;
			else{
				if (root->right==NULL) root->right=p;
				else root->right->right=p;
			}
			break;
			//����ǿ����ţ������⹹��һ������
			//��������֣��Ͳ������ϡ����У�������ڵ�Ϊ�գ���������ڵ㣻������ڵ�û�����������Ͳ�����ڵ���Ҷ����У����������ڵ��Ҷ��ӵ��Ҷ����С�
		case Close:
		case EOL:return root;//�����źͽ�����ֱ�ӷ������ڵ�����
		case Add:
		case Minus:
			root=new node(returnType,0,root);
			break;//�Ӽ������ȼ���ͣ���˽�����Ϊ�����ĸ����¹���һ������
		case Times:
		case Divide:
			if (root->type==Data || root->type==Divide || root->type==Times || root->type==EXP){
				root=new node(returnType,0,root);
				break;
			}
			//�˳������ȼ����ڼӼ��������������ڵ�Ϊ���ݻ�˳�����˷��������ڵõ��ĳ˺Ż������Ϊ���ڵ�
			else {
				if (root->type==Add || root->type==Minus){//������ڵ��ǼӺŻ���ţ������ж�����ӺŻ�����ǲ����������������ġ�
					int t=0;
					while (t<2){
						if (*(--s)!=' ') ++t;
					}//ȡ�˺Ż������ǰ���������
					if (getOp(s,value)==Close){
						root=new node(returnType,0,root);
						getOp(s,value);
					}//����ǣ��򽫵õ��ĳ˺Ż������Ϊ���ڵ㡣
					else{
						getOp(s,value);
						root->right=new node(returnType,0,root->right);
					}
					//������ǣ������ڵõ��ĳ˺Ż������Ϊ���ڵ���Ҷ������½���
				}
				else root->right=new node(returnType,0,root->right);
				break;
			}
		case EXP:
			if (root->type==Data || root->type==Divide || root->type==Times || root->type==Add||root->type==Minus){
				if ((root->type==Data)&&(root->right==NULL&&root->left==NULL)){
					root=new node(EXP,0,root);
					break;
				}//������ڵ�ֻ�����֣��򽫳˷���Ϊ���ڵ㡣
				int t=0;
				while (t<2){
					if (*(--s)!=' ') ++t;
				}//ȡ�˷���ǰ���������
				if (getOp(s,value)==Close){
					root=new node(returnType,0,root);
					getOp(s,value);
					break;
				}//�ж��Ƿ��������Խ������ȼ�����
				getOp(s,value);//��s��ԭ��Ӧ��λ��
			}
			if (root->right!=NULL){
				node *tmp=root;
				while (tmp->right->right!=NULL) tmp=tmp->right;
				tmp->right=new node(EXP,0,tmp->right);
			}
			else root=new node(EXP,0,root);
			//������ڵ���Ҷ��Ӳ�Ϊ�գ������ڳ˷����ȼ���ߣ�����������ұ��������Ҷ����У���������ڵ���Ϊ���ұ߽�㹹�����������ĸ��ڵ㣬�������Ľṹ
			//��������Ϊ���ڵ���Ҷ��ӡ�
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
	}//���������ض�ȡ����
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
	//��������Ϊ�ݹ�������
	switch(t->type){
	case Add:t->data=num1+num2;break;
	case Minus:t->data=num1-num2;break;
	case Times:t->data=num1*num2;break;
	case Divide:
		if (num2==0){
			cout<<"��������Ϊ��"<<endl;
			exit(1);
		}
		t->data=num1/num2;break;
	case EXP:
		if (num1==0&&num2==0){
			cout<<"ָ���͵�������ͬʱΪ��"<<endl;
			break;
		}
		if (num1==0&&num2<0){
			cout<<"�㲻������ĸ"<<endl;
			exit(1);
		}
		int tmp=1;//��֤�˵�0���Ƿ�ĸʱ��һ��������0�η�Ϊ1.
		for (int i=0;i<num2;++i) tmp*=num1;
		t->data=tmp;
	}
	return t->data;
}

void calc::bracket(char *&s){//��֤�����Ƿ�ƥ�䣬��oj�ϵ�ԭ����ͬ
    int j,temp=1;
    char col[100];
    int len=0,le[51],ri[51],left=0,right=0; 
    while (*s!='\0'){//�����Ŵӱ��ʽ����ȡ�������洢��һ��������
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
		cout<<"���Ų�ƥ��!"<<endl;
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
	}//������洢����������֣������Ϊ1������Ϊ0,������Ϊ2��������Ϊ3
	for (int i=0;i<typelen-2;++i){
		if ((array[i]==0)&&(array[i+1]==1)&&(array[i+2]==1)){
				cout<<"�������������"<<endl;//�������������������ŵ������ʱ������,��ֹ
				exit(1);
		}
		if ((array[i]==0)&&(array[i+1]==2)||(array[i]==3)&&(array[i+1]==0)){
			//�����ź���ֱ����һ�����ֻ������ź���ֱ����һ������ʱ����
			cout<<"�������������"<<endl;
			exit(1);
		}
		if ((array[i]==2)&&(array[i+1]==3)){
			cout<<"������������"<<endl;
			exit(1);
		}//�������ż�û���κ����ֻ�����ʱ������
	}
	if (array[typelen-1]==1||array[0]==1){//����ʱ�׻�βΪ�����ʱ������
		cout<<"�������������"<<endl;
		exit(1);
	}
}