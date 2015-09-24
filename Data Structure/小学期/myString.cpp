#include <iostream>
using namespace std;
#define MAX 255
class String{
	friend String operator+(const String &s1,const String &s2);
	friend istream& operator>>(istream &in,String &obj);
	friend ostream& operator<<(ostream &os,const String &obj);
private:
	char *my_str;
	int size;
public:
	String(const char *str=NULL);//构造函数
	String(const String &str);//拷贝构造函数
	~String() {delete [] my_str;}//析构函数
	String operator=(const String &s);
	bool operator==(const String &s);
	String operator+=(const String &s);
	int find(const String &str);
	int rfind(const String &str);
	int find_first_of(const String &str);
	int find_not_first_of(const String &str);
	int find_last_of(const String &str);
	int find_not_last_of(const String &str);
	char *substr(int start,int length=-1);
	char *erase(int start,int length);
	char *replace(int start,int length,const String &str);
	char &operator[](int pos);
};
String::String(const char *str){
	if (str==NULL){
		size=0;
		my_str=new char[1];
		my_str[0]='\0';
	}
	else {
		size=strlen(str);
		my_str=new char[size+1];
		for (int i=0;i<size;++i) my_str[i]=str[i];
		my_str[size]='\0';
	}
}
String::String(const String &str){
	size=str.size;
	my_str=new char[size+1];
	for (int i=0;i<size;++i) my_str[i]=str.my_str[i];
	my_str[size]='\0';
}
bool String::operator==(const String &str){
	if (size!=str.size) return false;
	return strcmp(my_str,str.my_str)?false:true;
}
String String::operator=(const String &str){
	if (this==&str) return *this;
	delete [] my_str;
	size=str.size;
	my_str=new char[size+1];
	for (int i=0;i<size;++i) my_str[i]=str.my_str[i];
	my_str[size]='\0';
	return *this;
}
String operator+(const String &s1,const String &s2){
	String s;
	s.size=s1.size+s2.size;
	s.my_str=new char[s.size+1];
	for (int i=0;i<s1.size;++i) s.my_str[i]=s1.my_str[i];
	for (int i=0;i<s2.size;++i) s.my_str[i+s1.size]=s2.my_str[i];
	s.my_str[s.size]='\0';
	return s;
}
String String::operator+=(const String &s){
	int ori_size=size;
	size+=s.size;
	char *new_str=new char[size+1];
	for (int i=0;i<ori_size;++i) new_str[i]=my_str[i];
	for (int i=0;i<s.size;++i) new_str[i+ori_size]=s.my_str[i];
	new_str[size]='\0';
	char *tmp=my_str;
	my_str=new_str;
	delete [] tmp;
	return *this;
}
istream& operator>>(istream &in,String &obj){
	obj.my_str=new char[MAX];
	in>>obj.my_str;
	return in;
}
ostream& operator<<(ostream &os,const String &obj){
	os<<obj.my_str;
	return os;
}
char *String::substr(int start,int length){
	if (length==-1){
		char *tmp=new char[size-start];
		for (int i=0;i<size-start-1;++i) tmp[i]=my_str[i+start];
		tmp[size-start-1]='\0';
		return tmp;
	}
	if (start+length>size -1){
		cout<<"下标越界"<<endl;
		exit(1);
	}
	char *tmp=new char[length+1];
	for (int i=0;i<length;++i) tmp[i]=my_str[i+start];
	tmp[length]='\0';
	return tmp;
}
int String::find(const String &str){
	int len=strlen(str.my_str),i,j;
	if (len>size){
		cout<<"length error"<<endl;
		exit(1);
	}
	for (i=0;i<size-len+1;++i){
		bool flag=true;
		for (j=0;j<len;++j){
			if (my_str[i+j]!=str.my_str[j]){
				flag=false;
				break;
			}
		}
		if (flag) return i;
	}
	return -1;
}
int String::rfind(const String &str){
	int len=strlen(str.my_str),i,j;
	bool flag;
	if (len>size){
		cout<<"length error"<<endl;
		exit(1);
	}
	for (i=size-len+1;i>=0;--i){
		flag=true;
		for (j=0;j<len;++j){
			if (my_str[i+j]!=str.my_str[j]){
				flag=false;
				break;
			}
		}
		if (flag) return i;
	}
	return -1;
}
int String::find_first_of(const String &str){
	int len=strlen(str.my_str),i,j;
	bool flag;
	for (i=0;i<size;++i){
		flag=false;
		for (j=0;j<len;++j){
			if (my_str[i]==str.my_str[j]){
				flag=true;
				break;
			}
		}
		if (flag) return i;
	}
	return -1;
}
int String::find_not_first_of(const String &str){
	int len=strlen(str.my_str),i,j;
	bool flag;
	for (i=0;i<size;++i){
		flag=false;
		for (j=0;j<len;++j){
			if (my_str[i]==str.my_str[j]){
				flag=true;
				break;
			}
		}
		if (!flag) return i;
	}
	return -1;
}
char *String::erase(int start,int length){
	if (start+length>size -1){
		cout<<"下标越界"<<endl;
		exit(1);
	}
	char *tmp=new char[size-length+1];
	for (int i=0;i<start;++i) tmp[i]=my_str[i];
	for (int i=start+length;i<size;++i) tmp[i-length]=my_str[i];
	tmp[size-length]='\0';
	return tmp;
}
char *String::replace(int start,int length,const String &str){
	if (start+length>size -1){
		cout<<"下标越界"<<endl;
		exit(1);
	}
	int len=strlen(str.my_str),i;
	char *tmp=new char[size-length+len+1];
	for (i=0;i<start;++i) tmp[i]=my_str[i];
	for (i=0;i<len;++i) tmp[start+i]=str.my_str[i];
	for (i=0;i<size-length-start;++i) tmp[start+len+i]=my_str[i+length+start];
	tmp[size-length+len]='\0';
	return tmp;
}
char &String::operator[](int pos){
	if (pos<0||pos>=size){
		cout<<"下标越界"<<endl;
		exit(1);
	}
	return my_str[pos];
}
int String::find_last_of(const String &str){
	int len=strlen(str.my_str),i,j;
	bool flag;
	for (i=size-1;i>=0;--i){
		flag=false;
		for (j=0;j<len;++j){
			if (my_str[i]==str.my_str[j]){
				flag=true;
				break;
			}
		}
		if (flag) return i;
	}
	return -1;
}
int String::find_not_last_of(const String &str){
	int len=strlen(str.my_str),i,j;
	bool flag;
	for (i=size-1;i>=0;--i){
		flag=false;
		for (j=0;j<len;++j){
			if (my_str[i]==str.my_str[j]){
				flag=true;
				break;
			}
		}
		if (!flag) return i;
	}
	return -1;
}
int main(){
	String a="hello world",b="this is a pen",c,d;
	cout<<"请输入c,d"<<'\n';
	cin>>c>>d;
	cout<<"c,d为："<<c<<'\t'<<d<<'\n';
	cout<<a[6]<<'\n';
	cout<<a.find_last_of("taeiou")<<'\n';
	cout<<a.find_not_last_of("adflkj")<<'\n';
	cout<<((a==b)?true:false)<<'\n';
	cout<<b.replace(5,2,"was")<<'\n';
	cout<<a.find_first_of("aeiou")<<'\n';
	cout<<b.find_not_first_of("apen")<<'\n';
	cout<<a.erase(3,10)<<'\n';
	cout<<b.find("is")<<'\n';
	cout<<a+b<<'\n';
	c+=d;
	cout<<"c+d为:"<<c<<'\n';
	cout<<b.rfind("is")<<'\n';
	String e=b;
	cout<<"e为："<<e<<'\n';
	cout<<a.substr(7,5)<<'\n';
	cout<<a.substr(3)<<'\n';
	cout<<a.substr(14,24)<<'\n';
	return 0;
}