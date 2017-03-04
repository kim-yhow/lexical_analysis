#include <iostream>
#include <fstream>
#pragma   warning (disable: 4786)
#include <vector>
#include "Analysis.h"
using namespace std;

//构造函数
Analysis::Analysis(char *filename)
{
	LoadFile(filename);
	LoadKeys("keys.txt");
	itstr=file_text.begin();
	NUM_FLAG=CONST_NUM_INT;		//初始化
	ID_FLAG=NORMAL_ID;
	IS_DEF=0;
}
//初始化token
void Analysis::initToken()
{
	token="";
}

//将当前元素加入token中，并且指针下移
void Analysis::getToken()
{
	if(itstr==file_text.end())
	{
		cout<<"错误：\' 或者 \" 不匹配！！"<<endl;
		exit(0);
	}
	token+=*itstr;
	itstr++;
}

//加载文件
bool Analysis::LoadFile(char* filename)
{
	ifstream file(filename);
	string temp="";
	if(!file.is_open())
	{
		cout<<"警告：无法打开目标文件，请确认文件是否存在！"<<endl;
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
	int i=1;
	string::iterator lt;	
	while(!file.eof())
	{
		
		file>>temp;
		lt=temp.end()-1;
		hash=((temp[0]-'a')*5+(*lt-'a'))%80;
		while(keys[hash].compare("")!=0)	//当哈希表中不为空，即表中有值
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

//判断是否是保留字
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
			cout<<"非法新增保留字!! 请查看keys.txt文件中是否有宏中未定义的保留字!"<<endl;
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
	 if(*itstr>='0' && *itstr<='9' )
	 {
		 return true;
	 }
 return false;
}


//判断是否是字母
bool Analysis::isLetter()
{
	if(*itstr>='A' && *itstr<='Z' || *itstr>='a' && *itstr<='z')
		return true;
	else
		return false;
}

//输出
void Analysis::output(int tmp,string tok="—")
{	
	if(tok.compare("")==0)
		return;
	cout<<token<<"\t\t\t"; 
	if(tmp==ERROR)
	{	
		cout<<"<"<<tmp<<","<<tok<<">"<<endl;
	}
	else if(tok.compare("—")==0)
		cout<<"<"<<tmp<<","<<tok<<">"<<endl;
	else 
		cout<<"<"<<tmp<<","<<"指向"<<tok<<"的符号表项的指针>"<<endl;
}


//保存标识符
bool Analysis::saveIdr()
{
	ofstream file;
	file.open("idr.txt");
	if(!file.is_open())
	{
		cout<<"警告：无法打开文件！"<<endl;
		exit(1);
		return false;
	}
	for(vector<string>::iterator lt=Idr.begin();lt<Idr.end();lt++)
	{
		if(!IS_DEF)
			file<<*lt<<"未定义"<<endl;
	}
	file.close();
	return true;
}





void Analysis::scanner()
{	
	//string 的迭代器，将从文件中读入的元素读出来进行分析
	itstr=file_text.begin();
	//输入的源程序未结束之前，一直进行循环
	while(itstr!=file_text.end())
	{
		initToken();				//初始化token
		//判断是否是常数
	 if(isDigital() || *itstr=='\"' || *itstr == '\'')			
	{
		 NUM_FLAG=CONST_NUM_INT;		//初始为整型数
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
		 while(isDigital() || (*itstr=='.' && NUM_FLAG==CONST_NUM_INT))			//当接收的字符一直是数字，则继续回到本状态
		 { 
			if(*itstr=='.')
			{
				NUM_FLAG=CONST_NUM_REAL;
			}
			getToken();
		}
		 output(NUM_FLAG,token);	
	 }
	 
	//判断是否是标识符
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

	//判断是否是运算符
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