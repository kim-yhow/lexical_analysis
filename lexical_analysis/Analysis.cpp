#include <iostream>
#include <fstream>
#pragma   warning (disable: 4786)
#include <vector>
#include "Analysis.h"
using namespace std;

//���캯��
Analysis::Analysis(char *filename)
{
	Fun ma("ȫ��");
	LoadFile(filename);
	//���ر������ļ�
	LoadKeys("Z_keys.txt");
	mItstr=mFile_text.begin();
	mNUM_FLAG=CONST_NUM_INT;		//��ʼ��
	mID_FLAG=NORMAL_ID;
	mHead_FLAG=false;
	mIsHaveStd=false;
	mIdentType=-1;
	mFunName="";
	mDelimFlag=0;
	mfuns.push_back(ma);
	mfun_index=mfuns.begin();
}
//��ʼ��mToken
void Analysis::initToken()
{
	mToken="";
}

//����ǰԪ�ؼ���mToken�У�����ָ������
void Analysis::getToken()
{
	if(mItstr==mFile_text.end())
	{
		cout<<"����\' ���� \" ��ƥ�䣡��"<<endl;
		exit(0);
	}
	mToken+=*mItstr;
	mItstr++;
}

//�����ļ�
bool Analysis::LoadFile(char* filename)
{
	ifstream file(filename);
	string temp="";
	if(!file.is_open())
	{
		cout<<"���棺�޷���"<<filename<<"�ļ�����ȷ���ļ��Ƿ���ڣ�"<<endl;
		exit(1);
		return false;
	}
	while(!file.eof())
	{
		getline(file,temp);
		mFile_text+=temp+"\n";
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
	string::iterator lt;	
	while(!file.eof())
	{
		file>>temp;
		lt=temp.end()-1;
		hash=((temp[0]-'a')*5+(*lt-'a'))%80;	
		while(mKeys[hash].compare("")!=0)	//����ϣ���в�Ϊ�գ���������ֵ
		{
			hash++;
		}
		mKeys[hash]=temp;
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
 if(mToken[0]>='A' && mToken[0]<='Z' || mToken[0]>='a' && mToken[0]<='z')
	{
	string::iterator lt=mToken.end()-1;
	int hskey=0;
	hskey=((mToken[0]-'a')*5+(*lt-'a'))%80;		//��ϣ�㷨
	
	while(mKeys[hskey].compare("")!=0 && hskey<80)
	{
		if(mKeys[hskey].compare(mToken)==0 )	
		{
			mID_FLAG=hskey;
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
			if(mToken.compare(*iter)==0)
			{
				mID_FLAG=i;
				return true;
			}
			i++;
		if(i>53)
		{
			cout<<"�Ƿ�����������!! ��鿴mKeys.txt�ļ����Ƿ��к���δ����ı�����!"<<endl;
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
	 if(*mItstr>='0' && *mItstr<='9' )
	 {
		 return true;
	 }
 return false;
}


//�ж��Ƿ�����ĸ
bool Analysis::isLetter()
{
	if(*mItstr>='A' && *mItstr<='Z' || *mItstr>='a' && *mItstr<='z')
		return true;
	else
		return false;
}


//�����ʶ��
bool Analysis::saveIdr()
{
	ofstream file;
	file.open("Z_idr.txt");
	if(!file.is_open())
	{
		cout<<"���棺�޷���Z_idr.txt�ļ���"<<endl;
		return false;
	}
	for(vector<Identitier>::iterator lt=mIdents.begin();lt<mIdents.end();lt++)
	{
		file<<lt->ID_Value<<"\t"<<lt->ID_FunName<<"\t"<<lt->ID_Type<<endl;	
	}
	file.close();
	return true;
}



/*
*��������ΪһЩ������������ʹ�øú�����
*������Ӧ�����͡�
*������ǻ����������ͣ�����Ϊ-1
*/
void Analysis::setIdentType()
{
	if(mID_FLAG==KEY_BOOL ||mID_FLAG==KEY_INT  ||mID_FLAG==KEY_FLOAT  ||mID_FLAG==KEY_DOUBLE 
			||mID_FLAG==KEY_CHAR || mID_FLAG==KEY_SHORT || mID_FLAG==KEY_CLASS || mID_FLAG==KEY_LONG 
			|| mID_FLAG==KEY_UNSIGNED || mID_FLAG==KEY_VOID)
	{
		mIdentType=mID_FLAG;
	}
	else{
		mIdentType=-1;
		// �п����Ǻ����������Խ��б���
		//setmfunName(mToken);
	}
}

//���ú�������
void Analysis::setmfunName(string name)
{
	Fun tempFun(name);
	mFunName=name;
	mfuns.push_back(tempFun);
	mfun_index=mfuns.end()-1;
}
//ȥ����ŵĺ�����
void Analysis::rmFunName()
{
	mFunName="";
}

bool Analysis::IsFunset(string::iterator &tempIt)
{

	if(*tempIt=='>' || *tempIt==';' || *tempIt=='<' || *tempIt=='+' || *tempIt=='/')
		{
			return false;
	  }
	if(*tempIt=='-' )
		if(*(++tempIt)!='>')
		{
			return false;
		}
			return true;
}
//�жϱ�ʶ���Ƿ��Ǻ������
bool Analysis::isFunction()
{
	int flag=0;
	string::iterator tempItstr=mItstr;
	while(IsFunset(tempItstr)&& tempItstr!=mFile_text.end())
	{
		if(*tempItstr=='(')
		{
			//�����Ժ�Ĵ������
			if(flag!=OPER_LEFT_KUO)
			{
				flag=OPER_LEFT_KUO;
			}
/*			else
			{

				return false;
			}*/

		}
	  else if(*tempItstr==')')
		{
			if(flag==OPER_LEFT_KUO)
			{
				flag=OPER_RIGHT_KUO;
			}
			else
			{
				return false;
			}
		}

	  else if(*tempItstr=='{')
		{
			if(flag==OPER_RIGHT_KUO)
			{
				flag=DELIM_LEFT_BIG_KUO;
				return true;
			}
			else
			{
				return false;
			}
		}
		tempItstr++;
	}
	return false;
}
//�����include����ı�ʶ��������Ϊtrue
void Analysis::SetHeadFlag(bool b)
{
	mHead_FLAG=b;
}
//���
void Analysis::output(int tmp,string tok="��")
{		
	
	if(tmp!=INCLUDE && tmp!=OPER_LT &&tmp!=OPER_SHUANG_YIN)
	{
		SetHeadFlag(false);
	}
	if(tok.compare("")==0)
		return;
	cout<<mToken<<"\t\t\t"; 
	if(tmp==ERROR)
	{	
		cout<<"<"<<tmp<<","<<mToken<<tok<<">"<<endl;
	}
	else if(tok.compare("��")==0)
		 cout<<"<"<<tmp<<","<<tok<<">"<<endl;
	else cout<<"<"<<tmp<<","<<tok<<"Ϊ����>"<<endl;
}

void Analysis::output(int tmp,Identitier idr)
{
	SetHeadFlag(false);
	cout<<mToken<<"\t\t\t"; 
	if(idr.mHEAD_FLAG)
	{
		cout<<"<"<<tmp<<","<<idr.ID_Value<<"��ͷ�ļ�>"<<endl;
	}
	else 
	{
		if(mIdentType!=-1)
		{
		 cout<<"<"<<tmp<<",����"<<idr.ID_Value<<" | "<<idr.ID_FunName<<"��������"<<" | "<<idr.ID_Type<<"����>"<<endl;
		}
		else
		 cout<<"<"<<tmp<<",ʹ��"<<idr.ID_Value<<" | "<<idr.ID_FunName<<"��������"<<" | "<<idr.ID_Type<<"����>"<<endl;
	}


}
//�������fun
void Analysis::output(int tmp,Fun fun)
{
	cout<<mToken<<"\t\t\t"; 
	if(mIdentType!=-1)
	{
		cout<<"<"<<tmp<<",����"<<fun.name<<"����>"<<endl;
	}
	else
		cout<<"<"<<tmp<<",ʹ��"<<fun.name<<"����>"<<endl;
}

//�жϴ�ʱ�����Ƿ񱻶���
Identitier Analysis::isIdent_ider()
{
	Identitier ID_temp("");
	for(vector<Identitier>::iterator itr=(mfun_index->funidenty).begin();
														itr<(mfun_index->funidenty).end();itr++)
	{
		if((itr->ID_Value).compare(mToken)==0)
		{			
			return *itr;;
		}
	}
	vector<Fun>::iterator lt=mfuns.begin();
	for(vector<Identitier>::iterator itr=(lt->funidenty).begin();
															itr<(lt->funidenty).end();itr++)
	{
		if((itr->ID_Value).compare(mToken)==0)
		{			
			return *itr;;
		}
	}
	return ID_temp;
}


//�жϴ�ʱ�ĺ����Ƿ��Ǳ������
Fun Analysis::isIdent_fun()
{
	Fun Fun_temp("");
	for(vector<Fun>::iterator itr=mfuns.begin();itr<mfuns.end();itr++)
	{
		if((itr->name).compare(mToken)==0)
		{			
			return *itr;
		}
	}
	return Fun_temp;
}

//����һЩstd����ı�ʶ
void Analysis::setStdIdent()
{
	ifstream file("std.txt");
	string temp="";
	if(!file.is_open())
	{
		cout<<"���棺�޷���std.txt�ļ�����ȷ���ļ��Ƿ���ڣ�"<<endl;
		exit(1);
		return ;
	}
	while(!file.eof())
	{
		getline(file,temp);
		Identitier ident(temp,"std��׼��","ȫ��",mHead_FLAG);	
		mIdents.push_back(ident);
		vector<Fun>::iterator t=mfuns.begin();
		(t->funidenty).push_back(ident);
	}
	return ;

}

//��ʼ����
void Analysis::scanner()
{	
	//string �ĵ������������ļ��ж����Ԫ�ض��������з���
	mItstr=mFile_text.begin();
	//�����Դ����δ����֮ǰ��һֱ����ѭ��
	while(mItstr!=mFile_text.end())
	{
		//��ʼ��mToken
		initToken();
	//�ж��Ƿ��Ǳ�ʶ��
	if(isLetter() || *mItstr=='_' || *mItstr =='#')
	{  
		initToken();
		getToken();
		mID_FLAG=NORMAL_ID;
	    while(isLetter() || *mItstr=='_' || isDigital())
		{
			getToken();
		}
		//������
		if(mToken.compare("#include")==0)
		{
			//setIdentType();
			mID_FLAG=INCLUDE;
			SetHeadFlag(true);
			output(mID_FLAG);		
		}
		//�Ƿ��Ǳ�����
		else 
			if(isTokenKey())
			{
				//�����ֶ���ı������ͣ�Ϊ����ı�����׼��
				setIdentType();
				output(mID_FLAG);
				if(mID_FLAG==KEY_MAIN && isFunction())
				{
					setmfunName(mToken);
				}
			}
			else
			{	
				if(isFunction())
				{
					//����fun��,���Ҵ���vector��
					setmfunName(mToken);
					output(mID_FLAG,*mfun_index);
					//���ö������Ч
					setIdentType();			
				}
				else{
					//�����������
					if(mIdentType!=-1 || mHead_FLAG)
					{
						Identitier ident(mToken,mKeys[mIdentType==-1?0:mIdentType],mfun_index->name,mHead_FLAG);
						mIdents.push_back(ident);
						(mfun_index->funidenty).push_back(ident);					
						output(mID_FLAG,ident);
						//���ö������Ч
						setIdentType();					
					}
					else
					{
						//�жϴ�ʱ�ı����Ƿ񱻶���
						Identitier Id_temp=isIdent_ider();	
						if((Id_temp.ID_FunName).compare("")!=0)
						{
							output(mID_FLAG,Id_temp);
							continue;
						}
						Fun Fun_temp=isIdent_fun();
						if((Fun_temp.name).compare("")!=0)
						{
							output(mID_FLAG,Fun_temp);
							continue;
						}
						else {
							if (!mIsHaveStd && mToken.compare("std")==0  )
							{
								mIsHaveStd=true;
								setStdIdent();
								output(STDFILE);
							}
							else 
								output(ERROR,"δ�������");
						}
					}														
				}
		}	
	}
	//�ж��Ƿ��ǳ���
	else{ 
	if(isDigital() || *mItstr=='\"' || *mItstr == '\'')			
	{
		 mNUM_FLAG=CONST_NUM_INT;		//��ʼΪ������
		 if(*mItstr=='\"' )
		 {
			initToken();				//��"��������
			getToken();		
			output(OPER_SHUANG_YIN);
			initToken();	

			 while(*mItstr!='\"')		//���¸���������" ��һֱ���ַ�����
			 {
				getToken();
			 }
		     mNUM_FLAG=CONST_CHAR;
			 //�����Include��ǰ�棬�������ͷ�ļ�
			 if(mHead_FLAG)
			{
				Identitier ident(mToken,mKeys[mIdentType==-1?0:mIdentType],mfun_index->name,mHead_FLAG);
				mIdents.push_back(ident);
			    (mfun_index->funidenty).push_back(ident);
				output(mNUM_FLAG,ident);	

			 }
			initToken();				//��"��������
			getToken();		
			output(OPER_SHUANG_YIN);
			initToken();	
		 }

		 else if( *mItstr == '\'')
		 {
			initToken();				//��'��������
			getToken();		
			output(OPER_DAN_YIN);
		
			initToken();
			 while(*mItstr!='\'')
			 {
				getToken();
			 }
			 mNUM_FLAG=CONST_CHAR;
			 output(mNUM_FLAG,mToken);	

			initToken();				//��'��������
			getToken();		
			output(OPER_DAN_YIN);
		 }
		 else
		 {
		 while(isDigital() || (*mItstr=='.' && mNUM_FLAG==CONST_NUM_INT))			//�����յ��ַ�һֱ�����֣�������ص���״̬
		 { 
			if(*mItstr=='.')
			{
				mNUM_FLAG=CONST_NUM_REAL;
			}
			initToken();
			getToken();
		}
		 output(mNUM_FLAG,mToken);	
		 }
	 }
	 
	//�ж��Ƿ��������
	else 
	{
	switch(*mItstr)
	{
	case ',':
		initToken();
		getToken();
		output(OPER_DOU);
		break;
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
		if(*mItstr=='=')
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
		if(*mItstr=='=')
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
		if(*mItstr=='=')
		{
			getToken();
			output(OPER_GE);
		}
		else if(*mItstr=='>'){
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
		if(*mItstr=='=')
		{
			getToken();
			output(OPER_LE);
		}
		else if(*mItstr=='<'){
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
		if(*mItstr=='+')
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
		if(*mItstr=='-')
		{
			getToken();
			output(OPER_MINUS_MINUS);
		}
			else if(*mItstr=='>'){
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
		if(*mItstr=='&')
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
		mDelimFlag++;
		output(DELIM_LEFT_BIG_KUO);
		break;
	case '}':
		initToken();
		getToken();
		mDelimFlag--;
		if(mDelimFlag<0)
		{
			if(mFunName.compare("")==0)
			{
				output(ERROR,"��main����������Ų�ƥ��");
				exit(1);
			}
			else
			{
				output(ERROR,mFunName+"�ڴ����Ų�ƥ��");
				exit(1);
			}
		}
		if(mDelimFlag==0)
		{
			rmFunName();
			//�ں����ⲿ�����Իص�ȫ�ֱ���
			mfun_index=mfuns.begin();
		}
		output(DELIM_RIGHT_BIG_KUO);break;
	case ';':
		initToken();
		getToken();		
		output(DELIM_FENHAO);break;

	default :
		output(ERROR,mToken);mItstr++;
		break;
	}
	}	
}	
}
if(!saveIdr())
{
	exit(1);
}			
}