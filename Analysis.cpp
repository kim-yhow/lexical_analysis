#include <iostream>
#include <fstream>
#pragma   warning (disable: 4786)
#include <vector>
#include "Analysis.h"
using namespace std;

//���캯��
Analysis::Analysis(char *filename)
{
	LoadFile(filename);
	LoadKeys("keys.txt");
	itstr=file_text.begin();
	NUM_FLAG=CONST_NUM_INT;		//��ʼ��
	ID_FLAG=NORMAL_ID;
	IS_DEF=0;
}
//��ʼ��token
void Analysis::initToken()
{
	token="";
}

//����ǰԪ�ؼ���token�У�����ָ������
void Analysis::getToken()
{
	if(itstr==file_text.end())
	{
		cout<<"����\' ���� \" ��ƥ�䣡��"<<endl;
		exit(0);
	}
	token+=*itstr;
	itstr++;
}

//�����ļ�
bool Analysis::LoadFile(char* filename)
{
	ifstream file(filename);
	string temp="";
	if(!file.is_open())
	{
		cout<<"���棺�޷���Ŀ���ļ�����ȷ���ļ��Ƿ���ڣ�"<<endl;
		exit(1);
		return false;
	}
	while(!file.eof())
	{
		getline(file,temp);
		file_text+=temp+"\n";
	}
	return true;
}

//���ر������ļ�
bool Analysis::LoadKeys(char* filename)
{
	int hash=0;					//��ϣ����
	ifstream file(filename);
	if(!file.is_open())
	{
		cout<<"���棺�޷��򿪱������ļ�����ȷ���ļ��Ƿ���ڣ�"<<endl;
		exit(1);
		return false;
	}
	string temp="";
	int i=1;
	string::iterator lt;	
	while(!file.eof())
	{
		
		file>>temp;
		lt=temp.end()-1;
		hash=((temp[0]-'a')*5+(*lt-'a'))%80;
		while(keys[hash].compare("")!=0)	//����ϣ���в�Ϊ�գ���������ֵ
		{
			hash++;
		}
		keys[hash]=temp;
		i++;
	}
	
	/*
while(!file.eof())
	{
		getline(file,temp);
		kkeys.push_back(temp);
	}*/
	return true;
	
}

//�ж��Ƿ��Ǳ�����
bool Analysis::isTokenKey()
{

	if(token[0]>='A' && token[0]<='Z' || token[0]>='a' && token[0]<='z')
	{
	string::iterator lt;
	lt=token.end()-1;
	int hskey=0;
	hskey=((token[0]-'a')*5+(*lt-'a'))%80;
	
	while(keys[hskey].compare("")!=0 && hskey<80)
	{
		if(keys[hskey].compare(token)==0 )	
		{
			ID_FLAG=hskey;
			return true;
		}
		hskey++;
	}
	}
	return false;

/*
	clock_t start,finish;  
    start=clock();
int i=4;
 for(vector<string>::iterator iter=kkeys.begin();iter!=kkeys.end();iter++)
	{
			if(token.compare(*iter)==0)
			{
				ID_FLAG=i;
				return true;
			}
			i++;
		if(i>53)
		{
			cout<<"�Ƿ�����������!! ��鿴keys.txt�ļ����Ƿ��к���δ����ı�����!"<<endl;
			exit(1);
		}
	}
 return false;
		finish=clock();
	cout<<"isTokenKey����ʱ�䣺"<<finish-start<<endl;*/


}

//�ж��Ƿ�����
bool Analysis::isDigital()
{
	 if(*itstr>='0' && *itstr<='9' )
	 {
		 return true;
	 }
 return false;
}


//�ж��Ƿ�����ĸ
bool Analysis::isLetter()
{
	if(*itstr>='A' && *itstr<='Z' || *itstr>='a' && *itstr<='z')
		return true;
	else
		return false;
}

//���
void Analysis::output(int tmp,string tok="��")
{	
	if(tok.compare("")==0)
		return;
	cout<<token<<"\t\t\t"; 
	if(tmp==ERROR)
	{	
		cout<<"<"<<tmp<<","<<tok<<">"<<endl;
	}
	else if(tok.compare("��")==0)
		cout<<"<"<<tmp<<","<<tok<<">"<<endl;
	else 
		cout<<"<"<<tmp<<","<<"ָ��"<<tok<<"�ķ��ű����ָ��>"<<endl;
}


//�����ʶ��
bool Analysis::saveIdr()
{
	ofstream file;
	file.open("idr.txt");
	if(!file.is_open())
	{
		cout<<"���棺�޷����ļ���"<<endl;
		exit(1);
		return false;
	}
	for(vector<string>::iterator lt=Idr.begin();lt<Idr.end();lt++)
	{
		if(!IS_DEF)
			file<<*lt<<"δ����"<<endl;
	}
	file.close();
	return true;
}





void Analysis::scanner()
{	
	//string �ĵ������������ļ��ж����Ԫ�ض��������з���
	itstr=file_text.begin();
	//�����Դ����δ����֮ǰ��һֱ����ѭ��
	while(itstr!=file_text.end())
	{
		initToken();				//��ʼ��token
		//�ж��Ƿ��ǳ���
	 if(isDigital() || *itstr=='\"' || *itstr == '\'')			
	{
		 NUM_FLAG=CONST_NUM_INT;		//��ʼΪ������
		 if(*itstr=='\"' )
		 {
			 getToken();
			 while(*itstr!='\"')
			 {
				getToken();
			 }
			getToken();
			 NUM_FLAG=CONST_CHAR;
		 }
		 else if( *itstr == '\'')
		 {
			getToken();
			 while(*itstr!='\'')
			 {
				getToken();
			 }
			 getToken();
			 NUM_FLAG=CONST_CHAR;
		 }
		 while(isDigital() || (*itstr=='.' && NUM_FLAG==CONST_NUM_INT))			//�����յ��ַ�һֱ�����֣�������ص���״̬
		 { 
			if(*itstr=='.')
			{
				NUM_FLAG=CONST_NUM_REAL;
			}
			getToken();
		}
		 output(NUM_FLAG,token);	
	 }
	 
	//�ж��Ƿ��Ǳ�ʶ��
	else if(isLetter() || *itstr=='_' || *itstr =='#')
	{  
		initToken();
		getToken();
		ID_FLAG=NORMAL_ID;
	    while(isLetter() || *itstr=='_' || isDigital())
		{
			getToken();
		}
		if(isTokenKey())
		{
			output(ID_FLAG);
		}
		else
		{	Idr.push_back(token);
			output(ID_FLAG,token);	}	
	}

	//�ж��Ƿ��������
	else
	{
	switch(*itstr)
	{
	case '(': 
		initToken();
		getToken();
		output(OPER_LEFT_KUO);
		break;
	case ')':	
		initToken();
		getToken();
		output(OPER_RIGHT_KUO);
		break;
	
	case '=':
		initToken();
		getToken();
		if(*itstr=='=')
		{
			getToken();
			output(OPER_DOU_EQUAL);
		}
		else {
			output(OPER_EQUAL);
		}
		break;

	case '!':
		initToken();
		getToken();
		if(*itstr=='=')
		{
			getToken();
			output(OPER_NEQUAL);
		}
		else {
			output(ERROR);
		}
		break;

	case '>':		
		initToken();
		getToken();			
		if(*itstr=='=')
		{
			getToken();
			output(OPER_GE);
		}
		else if(*itstr=='>'){
			getToken();
			output(OPER_RIGHT_RIGHT);
		}
		else {
			output(OPER_GT);
		}
		break;
	case '.':
		initToken();
		getToken();		
		output(OPER_POINT);
		break;
	case '<':		
		initToken();
		getToken();			
		if(*itstr=='=')
		{
			getToken();
			output(OPER_LE);
		}
		else if(*itstr=='<'){
			getToken();
			output(OPER_LEFT_LEFT);
		}
		else {
			output(OPER_LT);
		}
		break;
	case '+':		
		initToken();
		getToken();			
		if(*itstr=='+')
		{
			getToken();
			output(OPER_PLUS_PLUS);
		}

			else {
			output(OPER_PLUS);
		}
		break;
	case '-':		
		initToken();
		getToken();			
		if(*itstr=='-')
		{
			getToken();
			output(OPER_MINUS_MINUS);
		}
			else if(*itstr=='>'){
			getToken();
			output(OPER_POINT_ARROW);
		}
			else {
			output(OPER_MINUS);
		}
		break;
	case '*':
		initToken();
		getToken();		
		output(OPER_MUL);break;
	case '[':
		initToken();
		getToken();		
		output(OPER_LEFT_MID);break;
	case ']':
		initToken();
		getToken();		
		output(OPER_RIGHT_MID);break;
	case '/':
		initToken();
		getToken();		
		output(OPER_DIVIDE);break;
	case '&':
		initToken();
		getToken();			
		if(*itstr=='&')
		{
			getToken();
			output(OPER_AND_AND);
		}
		else {
			output(OPER_AND);
		}
		break;
	case '{':
		initToken();
		getToken();		
		output(DELIM_LEFT_BIG_KUO);
		break;
	case '}':
		initToken();
		getToken();		
		output(DELIM_RIGHT_BIG_KUO);break;
	case ';':
		initToken();
		getToken();		
		output(DELIM_FENHAO);break;
	default :
		output(ERROR,token);itstr++;
		break;
	}
	}	
}	
saveIdr();

			
}