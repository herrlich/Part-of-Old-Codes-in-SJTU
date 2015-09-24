#include <iostream>
#include <cstring>
using namespace std;
class String{
	friend String operator+(const String &s1,const String &s2);
	friend ostream & operator<<(ostream &os,const String &obj);
private:
	char *data;
public:
	String(const char *str=NULL) {
		if (str==NULL){
			data=new char[1];
			data='\0';
		}
		else {
			data=new char [strlen(str)+1];
			strcpy(data,str);
		}
	}
	String (const String &other){
		data=new char [strlen(other.data)+1];
		strcpy(data,other.data);
	}
	String operator=(const String &str) {
		if (this==&str) return *this;
		delete [] data;
		data=new char[strlen(str.data)+1];
		strcpy(data,str.data);
		return data;
	}
	String operator()(int start,int length){
		String temp;
		temp.data=new char[length+1];
		for (int i=0;i<length;++i) temp.data[i]=data[start+i];
		temp.data[length]='\0';
		return temp;
	}
	~String(){delete [] data;}
};
String operator+(const String &s1,const String &s2){
	String temp;
	temp.data=new char[strlen(s1.data)+strlen(s2.data)+1];
	strcpy(temp.data,s1.data);
	strcat(temp.data,s2.data);
	return temp;
}
ostream & operator<<(ostream &os,const String &obj) {cout<<obj.data<<endl;return os;}
int main(){
	String r1,r2="qwert";
	String r3=r2,r4;
	cout<<r3;
	r4=r3+r2;
	cout<<r4;
	r1=r2(1,2);
	cout<<r1;
	return 0;
}