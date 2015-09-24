//此程序可以识别诸如000123和-098等弱质性的输入……
//中途意外发现几个地方不能在函数内部的栈申请数组，要用new在堆上申请数组……
#include <iostream>
#include <cstring>
using namespace std;
class high_prec{
	friend istream& operator>>(istream &in,high_prec &obj);
	friend ostream& operator<<(ostream &os,high_prec &obj);
	friend high_prec operator+(high_prec &num1,high_prec &num2);
	friend high_prec operator-(high_prec &num1,high_prec &num2);
	friend high_prec operator*(high_prec &num1,high_prec &num2);
	friend high_prec operator/(high_prec &num1,high_prec &num2);
private:
	char array[10000];
	long int len;
	bool positive;
public:
	high_prec(char str[]="0");
	high_prec(const high_prec &num);
	high_prec &operator=(const high_prec &num);
	high_prec operator^(int num);
	bool operator>=(const high_prec &num);
	bool operator<=(const high_prec &num);
	bool operator==(const high_prec &num);
	bool operator>(const high_prec &num);
	bool operator<(const high_prec &num);
};
high_prec::high_prec(char str[]){
	if (str[0]=='-') positive=false;
	else positive=true;
	len=strlen(str);
	if (positive==false){
		len-=1;
		for (int i=0;i<len;++i) array[i]=str[i+1];
	}
	else for (int i=0;i<len;++i) array[i]=str[i];
}
high_prec::high_prec(const high_prec &num){
	positive=num.positive;
	len=num.len;
	for (int i=0;i<len;++i) array[i]=num.array[i];
}
high_prec &high_prec::operator=(const high_prec &num){
	if (this==&num) return *this;
	len=num.len;
	positive=num.positive;
	for (int i=0;i<len;++i) array[i]=num.array[i];
	return *this;
}
bool high_prec::operator<(const high_prec &num){
	if (positive==true&&num.positive==false) return false;
	if (positive==false&&num.positive==true) return true;
	if (positive==true&&num.positive==true){
		if (len<num.len) return true;
		if (len==num.len){
			for (int i=0;i<len;++i){
				if (array[i]>num.array[i]) return false;
				if (array[i]<num.array[i]) return true;
			}
		}
		return false;
	}
	if (positive==false&&num.positive==false){
		if (len<num.len) return false;
		if (len==num.len){
			for (int i=0;i<len;++i){
				if (array[i]>num.array[i]) return true;
				if (array[i]<num.array[i]) return false;
			}
			return false;
		}
		return true;
	}
	return true;
}
bool high_prec::operator>(const high_prec &num){
	if (positive==true&&num.positive==false) return true;
	if (positive==false&&num.positive==true) return false;
	if (positive==true&&num.positive==true){
		if (len>num.len) return true;
		if (len==num.len){
			for (int i=0;i<len;++i){
				if (array[i]>num.array[i]) return true;
				if (array[i]<num.array[i]) return false;
			}
		}
		return false;
	}
	if (positive==false&&num.positive==false){
		if (len<num.len) return true;
		if (len==num.len){
			for (int i=0;i<len;++i){
				if (array[i]>num.array[i]) return false;
				if (array[i]<num.array[i]) return true;
			}
		}
		return false;
	}
	return true;
}
bool high_prec::operator==(const high_prec &num){
	if (positive!=num.positive) return false;
	if (len!=num.len) return false;
	for (int i=0;i<len;++i){
		if (array[i]!=num.array[i]) return false;
	}
	return true;
}
bool high_prec::operator>=(const high_prec &num){
	if (positive==true&&num.positive==false) return true;
	if (positive==false&&num.positive==true) return false;
	if (positive==true&&num.positive==true){
		if (len<num.len) return false;
		if (len==num.len){
			for (int i=0;i<len;++i){
				if (array[i]>num.array[i]) return true;
				if (array[i]<num.array[i]) return false;
			}
		}
		return true;
	}
	if (positive==false&&num.positive==false){
		if (len<num.len) return true;
		if (len==num.len){
			for (int i=0;i<len;++i){
				if (array[i]>num.array[i]) return false;
				if (array[i]<num.array[i]) return true;
			}
			return true;
		}
		return false;
	}
	return true;
}
bool high_prec::operator<=(const high_prec &num){
	if (positive==true&&num.positive==false) return false;
	if (positive==false&&num.positive==true) return true;
	if (positive==true&&num.positive==true){
		if (len<num.len) return true;
		if (len==num.len){
			for (int i=0;i<len;++i){
				if (array[i]>num.array[i]) return false;
				if (array[i]<num.array[i]) return true;
			}
			return true;
		}
		return false;
	}
	if (positive==false&&num.positive==false){
		if (len<num.len) return false;
		if (len==num.len){
			for (int i=0;i<len;++i){
				if (array[i]>num.array[i]) return true;
				if (array[i]<num.array[i]) return false;
			}
		}
		return true;
	}
	return true;
}
istream& operator>>(istream &in,high_prec &obj){
	char tmp[10000];
	in>>tmp;
	if (tmp[0]=='-') obj.positive=false;
	else obj.positive=true;
	obj.len=strlen(tmp);
	if (obj.positive==true){
		for (int i=0;i<obj.len;++i) obj.array[i]=tmp[i];
	}
	else{
		obj.len-=1;
		for (int i=0;i<obj.len;++i) obj.array[i]=tmp[i+1];
	}
	return in;
}
ostream& operator<<(ostream &os,high_prec &obj){
	if (obj.positive==false) os<<'-';
	for (int i=0;i<obj.len;++i) os<<obj.array[i];
	return os;
}
high_prec operator+(high_prec &num1,high_prec &num2){
	int *c=new int[10000],*d=new int[10000];
	for (long int i=0;i<10000;++i){
		c[i]=0;
		d[i]=0;
	}
    int i=0,lena,lenb,min,max,j=0;
	high_prec result;
	lena=num1.len; 
	lenb=num2.len;
    min=(lena<lenb)?lena:lenb; 
    max=(lena>lenb)?lena:lenb;
	if (num1.positive==num2.positive){
		result.positive=num1.positive;
		for (i=0;i<min;++i){ 
			c[max-i-1]=(num1.array[lena-i-1]-'0')+(num2.array[lenb-i-1]-'0');
		}
		if (lena==max){ 
			for (i=0;i<max-min;++i){ 
				c[i]=num1.array[i]-'0'; 
			} 
		} 
		if (lenb==max){ 
			for (i=0;i<max-min;++i){ 
				c[i]=num2.array[i]-'0'; 
			} 
		} 
		for (i=0;i<max;++i){ 
			d[max-i]=(c[max-i-1]%10+c[max-i]/10+j)%10; 
			if (c[max-i-1]%10+c[max-i]/10+j>=10) j=1; 
			else j=0; 
		}
		d[0]=(j+c[0]/10)%10;
		int t=0;
		while(d[t]==0&&t<max) ++t;
		if (t==max){
			result.array[0]='0';
			result.len=1;
			result.positive=true;
		}
		for (i=t;i<max+1;++i) result.array[i-t]=d[i]+'0';
		if (max>t) result.len=max+1-t;
	}
	else{
		int condi=0;
		if (num1.positive==true){
			num2.positive=true;
			if (num1>=num2){
				result.positive=true;
				condi=1;
			}
			else result.positive=false;
			num2.positive=false;
		}
		else{
			num1.positive=true;
			if (num1>num2){
				result.positive=false;
				condi=1;
			}
			else result.positive=true;
			num1.positive=false;
		}
		if (condi==1){
			for (i=0;i<min;++i){
				c[max-i-1]=c[max-i-1]+(num1.array[lena-i-1]-'0')-(num2.array[lenb-i-1]-'0');
				if (c[max-i-1]<0){
					c[max-i-1]+=10;
					c[max-i-2]-=1;
				}
			}
			for (i=0;i<max-min;++i){
				c[i]=c[i]+num1.array[i]-'0';
				if (c[i]<0){
					c[i]+=10;
					c[i-1]-=1;
				}
			}
		}
		else{
			for (i=0;i<min;++i){
				c[max-i-1]=c[max-i-1]+(num2.array[lenb-i-1]-'0')-(num1.array[lena-i-1]-'0');
				if (c[max-i-1]<0){
					c[max-i-1]+=10;
					c[max-i-2]-=1;
				}
			}
			for (i=0;i<max-min;++i){
				c[i]=c[i]+num2.array[i]-'0';
				if (c[i]<0){
					c[i]+=10;
					c[i-1]-=1;
				}
			}
		}
		int t=0;
		while(c[t]==0&&t<max) ++t;
		if (t==max){
			result.array[0]='0';
			result.len=1;
			result.positive=true;
		}
		for (i=t;i<max;++i) result.array[i-t]=c[i]+'0';
		if (max>t) result.len=max-t;
	}
	delete [] c;
	delete [] d;
    return result; 
}
high_prec operator*(high_prec &num1,high_prec &num2){
	int *c=new int[10000],*d=new int[10000];
	for (long int i=0;i<10000;++i){
		c[i]=0;
		d[i]=0;
	}
	int i=0,lena,lenb,j=0,k=0;
	lena=num1.len;
	lenb=num2.len;
	high_prec result;
	if ((num1.len==1&&num1.array[0]=='0')||(num2.len==1&&num2.array[0]=='0')){
		result.positive=true;
		result.len=1;
		result.array[i]='0';
		delete [] c;
		delete [] d;
		return result;
	}
	if (num1.positive==num2.positive) result.positive=true;
	else result.positive=false;
	for (i=0;i<lena;++i){
		for (j=0;j<lenb;++j){
			c[i+j+1]+=(num1.array[i]-'0')*(num2.array[j]-'0');
		}
	}
	for (i=0;i<lena+lenb;++i){
		d[lena+lenb-1-i]=(c[lena+lenb-i-1]%10+c[lena+lenb-i]/10+k)%10;
		if (c[lena+lenb-i-1]%10+c[lena+lenb-i]/10+k>=10) k=(c[lena+lenb-i-1]%10+c[lena+lenb-i]/10+k)/10;
		else k=0;
	}
	int t=0;
	while(d[t]==0&&t<lena+lenb) ++t;
	if (t==lena+lenb){
		result.array[0]='0';
		result.len=1;
		result.positive=true;
	}
	for (i=t;i<lena+lenb;++i) result.array[i-t]=d[i]+'0';
	if (lena+lenb>t) result.len=lena+lenb-t;
	delete [] c;
	delete [] d;
	return result;
}
high_prec operator-(high_prec &num1,high_prec &num2){
	int *c=new int[10000],*d=new int[10000];
	for (long int i=0;i<10000;++i){
		c[i]=0;
		d[i]=0;
	}
    int i=0,lena,lenb,min,max,j=0;
	high_prec result;
	lena=num1.len; 
	lenb=num2.len;
    min=(lena<lenb)?lena:lenb; 
    max=(lena>lenb)?lena:lenb;
	if ((num1.positive==true&&num2.positive==false)||(num1.positive==false&&num2.positive==true)){
		if (num1.positive==true&&num2.positive==false) result.positive=true;
		else result.positive=false;
		for (i=0;i<min;++i){ 
			c[max-i-1]=(num1.array[lena-i-1]-'0')+(num2.array[lenb-i-1]-'0');
		}
		if (lena==max){ 
			for (i=0;i<max-min;++i){ 
				c[i]=num1.array[i]-'0';
			} 
		} 
		if (lenb==max){ 
			for (i=0;i<max-min;++i){ 
				c[i]=num2.array[i]-'0'; 
			} 
		} 
		for (i=0;i<max;++i){ 
			d[max-i]=(c[max-i-1]%10+c[max-i]/10+j)%10; 
			if (c[max-i-1]%10+c[max-i]/10+j>=10) j=1; 
			else j=0; 
		}
		d[0]=(j+c[0]/10)%10;
		int t=0;
		while(c[t]==0&&t<max) ++t;
		if (t==max){
			result.array[0]='0';
			result.len=1;
			result.positive=true;
		}
		for (i=t;i<max;++i) result.array[i-t]=c[i]+'0';
		if (max>t) result.len=max-t;
	}
	else{
		int condi=0;
		if (num1.positive==true){
			if (num1>=num2){
				result.positive=true;
				condi=1;
			}
			else result.positive=false;
		}
		else{
			num1.positive=true;
			num2.positive=true;
			if (num1>num2){
				result.positive=false;
				condi=1;
			}
			else result.positive=true;
			num1.positive=false;
			num2.positive=false;
		}
		if (condi==1){
			for (i=0;i<min;++i){
				c[max-i-1]=c[max-i-1]+(num1.array[lena-i-1]-'0')-(num2.array[lenb-i-1]-'0');
				if (c[max-i-1]<0){
					c[max-i-1]+=10;
					c[max-i-2]-=1;
				}
			}
			for (i=0;i<max-min;++i){
				c[i]=c[i]+num1.array[i]-'0';
				if (c[i]<0){
					c[i]+=10;
					c[i-1]-=1;
				}
			}
		}
		else{
			for (i=0;i<min;++i){
				c[max-i-1]=c[max-i-1]+(num2.array[lenb-i-1]-'0')-(num1.array[lena-i-1]-'0');
				if (c[max-i-1]<0){
					c[max-i-1]+=10;
					c[max-i-2]-=1;
				}
			}
			for (i=0;i<max-min;++i){
				c[i]=c[i]+num2.array[i]-'0';
				if (c[i]<0){
					c[i]+=10;
					c[i-1]-=1;
				}
			}
		}
		int t=0;
		while(c[t]==0&&t<max) ++t;
		if (t==max){
			result.array[0]='0';
			result.len=1;
			result.positive=true;
		}
		for (i=t;i<max;++i) result.array[i-t]=c[i]+'0';
		if (max>t) result.len=max-t;
	}
	delete [] c;
	delete [] d;
    return result; 
}
high_prec operator/(high_prec &num1,high_prec &num2){
    int i=0,lena,lenb,j=0,time=0,k,temp;
	high_prec result;
    bool stop=true,turn=true;
	int t1=0,t2=0;
	while (num1.array[t1]=='0'&&t1<num1.len) ++t1;
	if (t1==num1.len){
		result.positive=true;
		result.len=1;
		result.array[0]='0';
	}
	lena=num1.len-t1;
	while (num2.array[t2]=='0'&&t2<num2.len) ++t2;
	if (t2==num2.len){
		cout<<"除数不能为零"<<endl;
		exit(1);
	}
	lenb=num2.len-t2;
	if (num1.positive==num2.positive) result.positive=true;
	else result.positive=false;
	if (lena<lenb){
		result.len=1;
		result.positive=true;
		result.array[0]='0';
        return result; 
    }
	int *c=new int[10000],*d=new int[10000],*e=new int[10000],*f=new int[10000],*g=new int[10000];
	for (int i=0;i<10000;++i){
		c[i]=0;d[i]=0;e[i]=0;f[i]=0;g[i]=0;
	}
	for (i=t1;i<num1.len;++i) d[i-t1]=num1.array[i]-'0'; 
	for (i=t2;i<num2.len;++i) e[i-t2]=num2.array[i]-'0';
	for (k=lenb-1;k<lena;++k){
		time=0;
		do{ 
			stop=true;
			turn=true; 
			j=0;
			temp=10000;
			for (i=0;i<10000;++i) g[i]=0;
			for (i=0;i<lenb;++i){
				g[i+k-lenb+1]=e[i];
			}
			for (i=0;i<=k;++i){  
				c[i]=d[i]-g[i];  
			}
			for (i=0;i<=k;++i){
				if (c[i]!=0){
					temp=i;
					break;
				}
			}
			if (c[temp]>0){
				stop=false;
			}
			for (i=0;i<=k;++i){ 
				if (c[i]!=0) turn=false;
			}
			if (turn){
				for (i=0;i<=k;++i){
					d[i]=c[i];
				}
			}
			if (!stop){
				for (i=0;i<k+1;++i){ 
					d[k-i]=(c[k-i]+10-j)%10; 
					if (c[k-i]-j<0) j=1; 
					else j=0; 
				}
			}
			++time;
		}while (!stop);
		if (turn) ++time;
		f[k]=time;
	}

	int t=0;
	while(f[lenb-1]==1&&t<lena-lenb+1) ++t;
	if (t==lena-lenb+1){
		result.array[0]='0';
		result.len=1;
		result.positive=true;
	}
	for (k=lenb-1+t;k<lena;++k) result.array[k-lenb+1]=f[k]-1+'0';
	if (lena-lenb+1>t) result.len=lena-lenb+1-t;
	delete [] c;
	delete [] d;
	delete [] f;
	delete [] g;
	delete [] e;
	return result;  
}
high_prec high_prec:: operator^(int num){//个人认为如果乘方要用到高精度的范围，那么恐怕100000位也不一定够
	high_prec result;
	result.positive=true;
	result.len=1;
	result.array[0]='1';
	cout<<"aaaa"<<endl;
	cout<<num<<'\t'<<len<<'\t'<<array[0]<<endl;
	if (num==0&&len==1&&array[0]=='0'){
		cout<<"没有数学意义"<<endl;
		exit(1);
	}
	if (num<0){
		result.positive=true;
		result.len=1;
		result.array[0]='0';
	}
	for (int i=0;i<num;++i) result=result*(*this);
	return result;
}
int main(){
	high_prec a,b,c;
	cin>>a>>b;
	c=a^0;
	cout<<c<<endl;
	c=a+b;
	cout<<c<<endl;
	c=a-b;
	cout<<c<<endl;
	c=a*b;
	cout<<c<<endl;
	c=a/b;
	cout<<c<<endl;
	cout<<(a==b)<<endl;
	cout<<(a>=b)<<endl;
	cout<<(a<b)<<endl;
	return 0;
}