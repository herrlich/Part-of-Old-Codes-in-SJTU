//��������harmony.cpp
//���ã�����ȥ�����дʻ㣨��г��������
#include <iostream>
#include <cstring>
using namespace std;
int string_length,punctuation_num,useless_num,sensitive_num,type[500]={0},real_length,*declined_str_addr,*sensitive_length,count=0;
//string_lengthΪ�û�������������ַ������ȣ�punctuation_numΪ����ı����ŵ���Ŀ��useless_numΪ����������ַ�����Ŀ��sensitive_numΪ��������дʻ���
//type[500]�����������������ַ����еĲ�ͬ�ַ���0ΪĬ��ֵ��1Ϊ��㣬2Ϊ�����ַ��Ϳո�3Ϊ��д��ĸ�����֣�4ΪСд��ĸ��Ϊ�˽���ת���ɴ�д�Ƚϣ�
//real_lengthΪ������ַ�����ʵ�ʳ���
//declined_str_addrΪָ��ȥ���������ַ��ġ��������Ԫ����ԭ����string��ʼ���������еĵ�ַ��ָ�룬����declined_str_addr[1]=9��ʾ����������ĵ�2��Ԫ��ԭ����string��ʼ����ĵ�9��Ԫ��
//sensitive_length��ָ��һ���ɲ�ͬ�����дʻ���ַ�����������ɵ�һλ�����ָ��
//count���������������ַ����е��ַ�����

char *simplified_str,ultimate_string[500];
//simplified_str��ָ�򻯼����ַ�����ָ��
//ultimate_string[500]�����Ҫ����ĺ�г������飨�Ҿ���500��Ӧ���Ѿ����ˣ�Ҫ���û������ۿ��Ի���5000000��������

bool go_on=true;//go_on�������ж�������������Ӷ���;���ص�bool�ͱ���

//����Ϊ��������
void judge_undefined(char string[],char punctuation[],char useless[]);
void transform(int type[],char string[]);
int calculate(int n,char string[]);
void eliminate(char *sensitive[],int sensitive_length[],char string[]);

int main(){
	int i,t;//i��tΪ���������׵ı���
	
	char string[500],punctuation[50],useless[50],**sensitive;
	//string[500]���������û�������ַ���������Ӳ����뿴�������Ŵ�
	//punctuation[50]Ϊ��������ı����ŵ����飬useless[50]ͬ�������ôʻ�
	//sensitive��һ��ָ�������ɸ����дʻ���ɵĶ�ά�����ָ��
	//��ʵ�Ҿ�����Щ������̿��Զ���һ��initial�����ģ�����main�͸����ˣ���������������

	cout<<"�������ַ�������:"<<endl;
	cin>>string_length;
	cout<<"�������ַ���(������"<<string_length<<"���ַ�):\n";
	cin.ignore();//�˺����������ǰһ�����з�'\n',�������һ�������������
	cin.getline(string,500);
	real_length=strlen(string);
	if (real_length>string_length) {cout<<"���벻����Ҫ��\n";return 0;}//���벻��Ҫ��ʱֱ�ӷ���
	cout<<"�����������(���ż��޿ո񣬻س���ʾ����):\n";
	cin>>punctuation;
	punctuation_num=strlen(punctuation);
	cout<<"���������÷���:\n";
	cin>>useless;
	useless_num=strlen(useless);
	cout<<"������Ҫ����г�����дʻ����:\n";
	cin>>sensitive_num;
	sensitive=new char *[sensitive_num];//���������Ķ�̬�ռ������
	sensitive_length=new int[sensitive_num];
	for (i=0;i<sensitive_num;++i) sensitive[i]=new char [50];
	cout<<"������Ҫ����г�ĵ����дʻ�:\n";
	for (i=0;i<sensitive_num;++i){
		cin>>sensitive[i];
		sensitive_length[i]=calculate(50,sensitive[i]);//��ÿһ�����дʻ�ĳ��ȴ�������
	}
	for (i=0;i<sensitive_num;++i){
		for (t=0;t<sensitive_length[i];++t){
			if (sensitive[i][t]>='a'&&sensitive[i][t]<='z'){
				sensitive[i][t]=sensitive[i][t]-32;//�����������ַ����������е�Сд��ĸת��Ϊ��д��ĸ
			}
		}
	}
	judge_undefined(string,punctuation,useless);
	if (!go_on) return 0;//���벻��Ҫ��ʱֱ�ӷ���
	transform(type,string);
	eliminate(sensitive,sensitive_length,string);
	for (i=0;i<sensitive_num;++i) delete [] sensitive[i];//���ն�̬�ռ�
	delete [] sensitive;
	delete [] simplified_str;
	delete [] declined_str_addr;
	return 0;
}

//��������judge_undefined
//�÷���judge_undefined(char string[],char punctuation[],char useless[])��
//���ã��˺��������ж��Ƿ��ж�������ķ��ţ�ͬʱ��ÿ���ַ��Ĳ�ͬ���͸���Щ�ַ�һ����ţ��Ӷ����ڴ�Сд��ת���������ַ��ں����ȥ����
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
		if (string[i]==' ') type[i]=2;//�˴�������ɹ�type[i]==2���������˺þô�����
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
			cout<<"���벻����Ҫ��\n";
			go_on=false;
			break;
		}
	}
}

//��������transform
//�÷���transform(int type[],char string[])
//���ã��˺��������õ�һ��ȥ���������ַ������ַ�������
void transform(int type[],char string[]){
	int i,total=0;
	for (i=0;i<real_length;++i){
		if (type[i]==2) continue;
		else ++total;//�˴�������ȷ�صõ����ж��ٸ���Ч���ַ���Ϊ�����붯̬�ռ䷽�㣩
	}
	simplified_str=new char[total+1];//��Ϊ�ַ������Ϊ'\0'������Ҫ��һλ
	declined_str_addr=new int[total];
	for (i=0;i<real_length;++i){
		if (type[i]==2) continue;//����ǿո�������ôʻ�����ӵ�
		else{
			declined_str_addr[count]=i;//��count��Ϊ���������ÿһλ��λ�ñ���
			if (type[i]==4){
				simplified_str[count]=string[i]-32;//��Сд��ĸת��Ϊ��д��ĸ���棨�Ҿ�ϲ����д��ĸ��
			}
			else simplified_str[count]=string[i];//����ֱ������
			++count;
		}
	}
	simplified_str[count]='\0';//���Ҫ���ַ��������'\0'
}

//��������calculate
//�÷���calculate(int n,char string[])
//���ã��������дʻ㳤��
int calculate(int n,char string[])
{
	int k=0;//���ס�����
	for(int j=0;j<n;++j){
		if(string[j]=='\0')break;//����������־��ֹͣ
		++k;
	}
	return k;
}

//������:eliminate
//�÷���eliminate(char *sensitive[],int sensitive_length[],char string[])
//���ã��˺���������гҪ��г�������ַ�����ͬʱ�����г����ַ���
void eliminate(char *sensitive[],int sensitive_length[],char string[]){
	int i,j,*final_judge;//i��j�������ס�����
	//final_judge��������һ���жϻ������ַ������Ƿ��������ַ��������飬��Ӧ��λ�ñ��1���У���0��û�У�
	final_judge=new int[count];
	for (i=0;i<count;++i) {final_judge[i]=0;}
	for (i=0;i<sensitive_num;++i){   //��ÿһ�����дʻ㿪ʼ
		for (j=0;j<=count-sensitive_length[i];++j){    //�����ַ��ܵ�����Զ����
			if (strncmp(simplified_str+j,sensitive[i],sensitive_length[i])==0&&final_judge[j]==0){
				//��strncmp�����Ƚ����Ϊsensitive_length[i]���ַ����Ƿ���ͬ������ͬ��δ����������Ա��
				final_judge[j]=1;
				final_judge[j+sensitive_length[i]-1]=1;//ֻ��ǿ�ͷ�ͽ�β
			}
		}
	}
	int *mark;//mark���������ʼ���������ж���Щ�ַ������С�����
	mark=new int[real_length];
	for (i=0;i<real_length;++i){
		mark[i]=0;
	}//��ʼ��Ϊ0,������0��ʾ�����С�����
	for (j=0;j<count;++j){
		if (final_judge[j]==1){
			mark[declined_str_addr[j]]=1;//�Ի���ѡ�����ַ����������ǣ������ж��Ƿ������
		}
	}
	int temp=0;//temp��Ϊ��ʱ�ļ���������ɵ��ַ������ȵı���
	i=0;//������������˭
	while (i<real_length){    //������while��㣬��Ϊ������Ծʽ�ص���i
		if (mark[i]==0){    //�����¿�ʼ���Ϊ0��ֱ���յ�
			ultimate_string[temp]=string[i];
			++temp;
			++i;
		}
		if (mark[i]==1){    //������Ϊ1��������1��ʼ������һ��1�Ĺ����е���������ȫ������г��������û�õġ�������
			for (j=i+1;j<real_length;++j){
				if (mark[j]==1) break;
			}
			i=j+1;//�ٴ���һ����ʼ����
		}
	}
	ultimate_string[temp]='\0';//������'\0'
	cout<<"��г��:"<<endl;
	cout<<ultimate_string<<endl;
	delete [] final_judge;//���ն�̬�ռ�
	delete [] mark;
}