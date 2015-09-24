//函数名：harmony.cpp
//作用：用于去除敏感词汇（和谐。。。）
#include <iostream>
#include <cstring>
using namespace std;
int string_length,punctuation_num,useless_num,sensitive_num,type[500]={0},real_length,*declined_str_addr,*sensitive_length,count=0;
//string_length为用户声明的输入的字符串长度，punctuation_num为输入的标点符号的数目，useless_num为输入的无用字符的数目，sensitive_num为输入的敏感词汇数
//type[500]是用来区分在输入字符串中的不同字符：0为默认值，1为标点，2为无用字符和空格，3为大写字母和数字，4为小写字母（为了将来转换成大写比较）
//real_length为输入的字符串的实际长度
//declined_str_addr为指向去除了无用字符的、简单数组的元素在原来的string初始输入数组中的地址的指针，比如declined_str_addr[1]=9表示化简后的数组的第2个元素原来是string初始数组的第9个元素
//sensitive_length是指向一个由不同的敏感词汇的字符串长度所组成的一位数组的指针
//count用来计数化简后的字符串中的字符个数

char *simplified_str,ultimate_string[500];
//simplified_str是指向化简后的字符串的指针
//ultimate_string[500]是最后要输出的和谐后的数组（我觉得500个应该已经够了，要是用户不嫌累可以换成5000000。。。）

bool go_on=true;//go_on是用来判断输入数据有误从而中途返回的bool型变量

//以下为函数声明
void judge_undefined(char string[],char punctuation[],char useless[]);
void transform(int type[],char string[]);
int calculate(int n,char string[]);
void eliminate(char *sensitive[],int sensitive_length[],char string[]);

int main(){
	int i,t;//i，t为两个跑龙套的变量
	
	char string[500],punctuation[50],useless[50],**sensitive;
	//string[500]用来储存用户输入的字符串，如果嫌不够请看上文括号处
	//punctuation[50]为储存输入的标点符号的数组，useless[50]同理储存无用词汇
	//sensitive是一个指向由若干个敏感词汇组成的二维数组的指针
	//其实我觉得这些输入过程可以定义一个initial函数的，这样main就更短了，但是我懒。。。

	cout<<"请输入字符串长度:"<<endl;
	cin>>string_length;
	cout<<"请输入字符串(不多于"<<string_length<<"个字符):\n";
	cin.ignore();//此函数用来清除前一个换行符'\n',以免对下一个输入造成误伤
	cin.getline(string,500);
	real_length=strlen(string);
	if (real_length>string_length) {cout<<"输入不符合要求\n";return 0;}//输入不合要求时直接返回
	cout<<"请输入标点符号(符号间无空格，回车表示结束):\n";
	cin>>punctuation;
	punctuation_num=strlen(punctuation);
	cout<<"请输入无用符号:\n";
	cin>>useless;
	useless_num=strlen(useless);
	cout<<"请输入要被和谐的敏感词汇个数:\n";
	cin>>sensitive_num;
	sensitive=new char *[sensitive_num];//很容易理解的动态空间的申请
	sensitive_length=new int[sensitive_num];
	for (i=0;i<sensitive_num;++i) sensitive[i]=new char [50];
	cout<<"请输入要被和谐的的敏感词汇:\n";
	for (i=0;i<sensitive_num;++i){
		cin>>sensitive[i];
		sensitive_length[i]=calculate(50,sensitive[i]);//将每一个敏感词汇的长度储存起来
	}
	for (i=0;i<sensitive_num;++i){
		for (t=0;t<sensitive_length[i];++t){
			if (sensitive[i][t]>='a'&&sensitive[i][t]<='z'){
				sensitive[i][t]=sensitive[i][t]-32;//将储存敏感字符串的数组中的小写字母转换为大写字母
			}
		}
	}
	judge_undefined(string,punctuation,useless);
	if (!go_on) return 0;//输入不合要求时直接返回
	transform(type,string);
	eliminate(sensitive,sensitive_length,string);
	for (i=0;i<sensitive_num;++i) delete [] sensitive[i];//回收动态空间
	delete [] sensitive;
	delete [] simplified_str;
	delete [] declined_str_addr;
	return 0;
}

//函数名：judge_undefined
//用法：judge_undefined(char string[],char punctuation[],char useless[])；
//作用：此函数用来判断是否有定义以外的符号，同时按每个字符的不同类型给这些字符一个编号，从而便于大小写的转化和无用字符在后面的去除。
void judge_undefined(char string[],char punctuation[],char useless[]){
	int i,j;
	for (i=0;i<real_length;++i){
		for (j=0;j<punctuation_num;++j){
			if (string[i]==punctuation[j]){
				type[i]=1;
				break;
			}
		}
		if (type[i]==0){
			for (j=0;j<useless_num;++j){
				if (string[i]==useless[j]){
					type[i]=2;
					break;
				}
			}
		}
		if (string[i]==' ') type[i]=2;//此处曾经打成过type[i]==2，害我找了好久错。。。
		if (type[i]==0){
			if (string[i]>='A'&&string[i]<='Z'||string[i]>='0'&&string[i]<='9'){
				type[i]=3;
			}
		}
		if (type[i]==0){
			if (string[i]>='a'&&string[i]<='z'){
				type[i]=4;
			}
		}
		if (type[i]==0){
			cout<<"输入不符合要求\n";
			go_on=false;
			break;
		}
	}
}

//函数名：transform
//用法：transform(int type[],char string[])
//作用：此函数用来得到一个去除了无用字符的新字符串数组
void transform(int type[],char string[]){
	int i,total=0;
	for (i=0;i<real_length;++i){
		if (type[i]==2) continue;
		else ++total;//此处用来精确地得到共有多少个有效的字符（为了申请动态空间方便）
	}
	simplified_str=new char[total+1];//因为字符串最后为'\0'，所以要留一位
	declined_str_addr=new int[total];
	for (i=0;i<real_length;++i){
		if (type[i]==2) continue;//如果是空格或者无用词汇就无视掉
		else{
			declined_str_addr[count]=i;//以count作为创建数组的每一位的位置变量
			if (type[i]==4){
				simplified_str[count]=string[i]-32;//将小写字母转化为大写字母储存（我就喜欢大写字母）
			}
			else simplified_str[count]=string[i];//否则直接收了
			++count;
		}
	}
	simplified_str[count]='\0';//最后要给字符数组加上'\0'
}

//函数名：calculate
//用法：calculate(int n,char string[])
//作用：计数敏感词汇长度
int calculate(int n,char string[])
{
	int k=0;//龙套。。。
	for(int j=0;j<n;++j){
		if(string[j]=='\0')break;//读到结束标志是停止
		++k;
	}
	return k;
}

//函数名:eliminate
//用法：eliminate(char *sensitive[],int sensitive_length[],char string[])
//作用：此函数用来和谐要和谐的敏感字符串，同时输出和谐后的字符串
void eliminate(char *sensitive[],int sensitive_length[],char string[]){
	int i,j,*final_judge;//i，j依旧龙套。。。
	//final_judge用来创建一个判断化简后的字符串中是否有敏感字符串的数组，相应的位置标记1（有），0（没有）
	final_judge=new int[count];
	for (i=0;i<count;++i) {final_judge[i]=0;}
	for (i=0;i<sensitive_num;++i){   //从每一个敏感词汇开始
		for (j=0;j<=count-sensitive_length[i];++j){    //到首字符能到的最远距离
			if (strncmp(simplified_str+j,sensitive[i],sensitive_length[i])==0&&final_judge[j]==0){
				//用strncmp函数比较最多为sensitive_length[i]的字符串是否相同，若相同且未被标记则予以标记
				final_judge[j]=1;
				final_judge[j+sensitive_length[i]-1]=1;//只标记开头和结尾
			}
		}
	}
	int *mark;//mark用来在最初始的数组中判断哪些字符可以有。。。
	mark=new int[real_length];
	for (i=0;i<real_length;++i){
		mark[i]=0;
	}//初始化为0,下文中0表示可以有。。。
	for (j=0;j<count;++j){
		if (final_judge[j]==1){
			mark[declined_str_addr[j]]=1;//对化简选出的字符串做额外标记，用作判断是否可以有
		}
	}
	int temp=0;//temp作为临时的计量最后生成的字符串长度的变量
	i=0;//我是龙套我怕谁
	while (i<real_length){    //这里用while最方便，因为可以跳跃式地调整i
		if (mark[i]==0){    //凡是新开始标记为0的直接收掉
			ultimate_string[temp]=string[i];
			++temp;
			++i;
		}
		if (mark[i]==1){    //如果标记为1，则从这个1开始到下面一个1的过程中的所有零项全部被和谐（隐藏是没用的。。。）
			for (j=i+1;j<real_length;++j){
				if (mark[j]==1) break;
			}
			i=j+1;//再从下一个开始计数
		}
	}
	ultimate_string[temp]='\0';//最后加上'\0'
	cout<<"和谐后:"<<endl;
	cout<<ultimate_string<<endl;
	delete [] final_judge;//回收动态空间
	delete [] mark;
}