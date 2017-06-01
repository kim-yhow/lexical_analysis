#include <iostream>
#include <fstream>
#pragma   warning (disable: 4786)
#include <vector>
#include "Analysis.h"
using namespace std;

//构造函数
Analysis::Analysis(char *filename)
{
	Fun ma("全局");
	LoadFile(filename);
	//加载保留字文件
	LoadKeys("Z_keys.txt");
	mItstr=mFile_text.begin();
	mNUM_FLAG=CONST_NUM_INT;		//初始化
	mID_FLAG=NORMAL_ID;
	mHead_FLAG=false;
	mIsHaveStd=false;
	mIdentType=-1;
	mFunName="";
	mDelimFlag=0;
	mfuns.push_back(ma);
	mfun_index=mfuns.begin();
}
//初始化mToken
void Analysis::initToken()
{
	mToken="";
}

//将当前元素加入mToken中，并且指针下移
void Analysis::getToken()
{
	if(mItstr==mFile_text.end())
	{
		cout<<"错误：\' 或者 \" 不匹配！！"<<endl;
		exit(0);
	}
	mToken+=*mItstr;
	mItstr++;
}

//加载文件
bool Analysis::LoadFile(char* filename)
{
	ifstream file(filename);
	string temp="";
	if(!file.is_open())
	{
		cout<<"警告：无法打开"<<filename<<"文件，请确认文件是否存在！"<<endl;
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

//加载保留字文件
bool Analysis::LoadKeys(char* filename)
{
	int hash=0;					//哈希参数
	ifstream file(filename);
	if(!file.is_open())
	{
		cout<<"警告：无法打开保留字文件，请确认文件是否存在！"<<endl;
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
		while(mKeys[hash].compare("")!=0)	//当哈希表中不为空，即表中有值
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

//判断是否是保留字
bool Analysis::isTokenKey()
{	
 if(mToken[0]>='A' && mToken[0]<='Z' || mToken[0]>='a' && mToken[0]<='z')
	{
	string::iterator lt=mToken.end()-1;
	int hskey=0;
	hskey=((mToken[0]-'a')*5+(*lt-'a'))%80;		//哈希算法
	
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
			cout<<"非法新增保留字!! 请查看mKeys.txt文件中是否有宏中未定义的保留字!"<<endl;
			exit(1);
		}
	}
 return false;
		finish=clock();
	cout<<"isTokenKey运行时间："<<finish-start<<endl;*/

}

//判断是否数字
bool Analysis::isDigital()
{
	 if(*mItstr>='0' && *mItstr<='9' )
	 {
		 return true;
	 }
 return false;
}


//判断是否是字母
bool Analysis::isLetter()
{
	if(*mItstr>='A' && *mItstr<='Z' || *mItstr>='a' && *mItstr<='z')
		return true;
	else
		return false;
}


//保存标识符
bool Analysis::saveIdr()
{
	ofstream file;
	file.open("Z_idr.txt");
	if(!file.is_open())
	{
		cout<<"警告：无法打开Z_idr.txt文件！"<<endl;
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
*当保留字为一些基本数据类型使用该函数，
*设置相应的类型。
*如果不是基本数据类型，则设为-1
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
		// 有可能是函数名，所以进行保存
		//setmfunName(mToken);
	}
}

//设置函数名称
void Analysis::setmfunName(string name)
{
	Fun tempFun(name);
	mFunName=name;
	mfuns.push_back(tempFun);
	mfun_index=mfuns.end()-1;
}
//去掉存放的函数名
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
//判断标识符是否是函数入口
bool Analysis::isFunction()
{
	int flag=0;
	string::iterator tempItstr=mItstr;
	while(IsFunset(tempItstr)&& tempItstr!=mFile_text.end())
	{
		if(*tempItstr=='(')
		{
			//用于以后的错误检验
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
//如果是include后面的标识符则设置为true
void Analysis::SetHeadFlag(bool b)
{
	mHead_FLAG=b;
}
//输出
void Analysis::output(int tmp,string tok="—")
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
	else if(tok.compare("—")==0)
		 cout<<"<"<<tmp<<","<<tok<<">"<<endl;
	else cout<<"<"<<tmp<<","<<tok<<"为常数>"<<endl;
}

void Analysis::output(int tmp,Identitier idr)
{
	SetHeadFlag(false);
	cout<<mToken<<"\t\t\t"; 
	if(idr.mHEAD_FLAG)
	{
		cout<<"<"<<tmp<<","<<idr.ID_Value<<"是头文件>"<<endl;
	}
	else 
	{
		if(mIdentType!=-1)
		{
		 cout<<"<"<<tmp<<",申明"<<idr.ID_Value<<" | "<<idr.ID_FunName<<"函数变量"<<" | "<<idr.ID_Type<<"类型>"<<endl;
		}
		else
		 cout<<"<"<<tmp<<",使用"<<idr.ID_Value<<" | "<<idr.ID_FunName<<"函数变量"<<" | "<<idr.ID_Type<<"类型>"<<endl;
	}


}
//输出函数fun
void Analysis::output(int tmp,Fun fun)
{
	cout<<mToken<<"\t\t\t"; 
	if(mIdentType!=-1)
	{
		cout<<"<"<<tmp<<",申明"<<fun.name<<"函数>"<<endl;
	}
	else
		cout<<"<"<<tmp<<",使用"<<fun.name<<"函数>"<<endl;
}

//判断此时变量是否被定义
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


//判断此时的函数是否是被定义的
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

//设置一些std定义的标识
void Analysis::setStdIdent()
{
	ifstream file("std.txt");
	string temp="";
	if(!file.is_open())
	{
		cout<<"警告：无法打开std.txt文件，请确认文件是否存在！"<<endl;
		exit(1);
		return ;
	}
	while(!file.eof())
	{
		getline(file,temp);
		Identitier ident(temp,"std标准库","全局",mHead_FLAG);	
		mIdents.push_back(ident);
		vector<Fun>::iterator t=mfuns.begin();
		(t->funidenty).push_back(ident);
	}
	return ;

}

//开始分析
void Analysis::scanner()
{	
	//string 的迭代器，将从文件中读入的元素读出来进行分析
	mItstr=mFile_text.begin();
	//输入的源程序未结束之前，一直进行循环
	while(mItstr!=mFile_text.end())
	{
		//初始化mToken
		initToken();
	//判断是否是标识符
	if(isLetter() || *mItstr=='_' || *mItstr =='#')
	{  
		initToken();
		getToken();
		mID_FLAG=NORMAL_ID;
	    while(isLetter() || *mItstr=='_' || isDigital())
		{
			getToken();
		}
		//保留字
		if(mToken.compare("#include")==0)
		{
			//setIdentType();
			mID_FLAG=INCLUDE;
			SetHeadFlag(true);
			output(mID_FLAG);		
		}
		//是否是保留字
		else 
			if(isTokenKey())
			{
				//保留字定义的变量类型，为定义的变量做准备
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
					//保留fun名,并且存入vector中
					setmfunName(mToken);
					output(mID_FLAG,*mfun_index);
					//设置定义符无效
					setIdentType();			
				}
				else{
					//如果是有申明
					if(mIdentType!=-1 || mHead_FLAG)
					{
						Identitier ident(mToken,mKeys[mIdentType==-1?0:mIdentType],mfun_index->name,mHead_FLAG);
						mIdents.push_back(ident);
						(mfun_index->funidenty).push_back(ident);					
						output(mID_FLAG,ident);
						//设置定义符无效
						setIdentType();					
					}
					else
					{
						//判断此时的变量是否被定义
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
								output(ERROR,"未定义变量");
						}
					}														
				}
		}	
	}
	//判断是否是常数
	else{ 
	if(isDigital() || *mItstr=='\"' || *mItstr == '\'')			
	{
		 mNUM_FLAG=CONST_NUM_INT;		//初始为整型数
		 if(*mItstr=='\"' )
		 {
			initToken();				//将"分析出来
			getToken();		
			output(OPER_SHUANG_YIN);
			initToken();	

			 while(*mItstr!='\"')		//当下个变量不是" 怎一直是字符常量
			 {
				getToken();
			 }
		     mNUM_FLAG=CONST_CHAR;
			 //如果有Include在前面，则可能是头文件
			 if(mHead_FLAG)
			{
				Identitier ident(mToken,mKeys[mIdentType==-1?0:mIdentType],mfun_index->name,mHead_FLAG);
				mIdents.push_back(ident);
			    (mfun_index->funidenty).push_back(ident);
				output(mNUM_FLAG,ident);	

			 }
			initToken();				//将"分析出来
			getToken();		
			output(OPER_SHUANG_YIN);
			initToken();	
		 }

		 else if( *mItstr == '\'')
		 {
			initToken();				//将'分析出来
			getToken();		
			output(OPER_DAN_YIN);
		
			initToken();
			 while(*mItstr!='\'')
			 {
				getToken();
			 }
			 mNUM_FLAG=CONST_CHAR;
			 output(mNUM_FLAG,mToken);	

			initToken();				//将'分析出来
			getToken();		
			output(OPER_DAN_YIN);
		 }
		 else
		 {
		 while(isDigital() || (*mItstr=='.' && mNUM_FLAG==CONST_NUM_INT))			//当接收的字符一直是数字，则继续回到本状态
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
	 
	//判断是否是运算符
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
				output(ERROR,"在main函数外大括号不匹配");
				exit(1);
			}
			else
			{
				output(ERROR,mFunName+"内大括号不匹配");
				exit(1);
			}
		}
		if(mDelimFlag==0)
		{
			rmFunName();
			//在函数外部，所以回到全局变量
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