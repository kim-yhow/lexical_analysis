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
	LoadOpera("opera.txt");
	LoadDelim("delim.txt");
	itstr=file_text.begin();
	NUM_FLAG=CONST_NUM_INT;		//初始化
	ID_FLAG=NORMAL_ID;



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
	ifstream file(filename);
	if(!file.is_open())
	{
		cout<<"警告：无法打开保留字文件，请确认文件是否存在！"<<endl;
		exit(1);
		return false;
	}
	string temp="";
	while(!file.eof())
	{
		getline(file,temp);
		keys.push_back(temp);
	}
	return true;
}

//加载运算符文件
bool Analysis::LoadOpera(char* filename)
{
	ifstream file(filename);
	if(!file.is_open())
	{
		cout<<"警告：无法打开运算符字文件，请确认文件是否存在！"<<endl;
		exit(1);
		return false;
	}
	string temp="";
	while(!file.eof())
	{
		getline(file,temp);
		opera.push_back(temp);
	}
	return true;
}



//加载界符符文件
bool Analysis::LoadDelim(char* filename)
{
	ifstream file(filename);
	if(!file.is_open())
	{
		cout<<"警告：无法打开运算符字文件，请确认文件是否存在！"<<endl;
		exit(1);
		return false;
	}
	string temp="";
	while(!file.eof())
	{
		getline(file,temp);
		delim.push_back(temp);
	}
	return true;
}

//判断是否是保留字
bool Analysis::isTokenKey()
{
	int i=4;
 for(vector<string>::iterator iter=keys.begin();iter!=keys.end();iter++)
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
}

//判断是否是界符
bool Analysis::isDelim()
{
	/*
	*成员变量string::iterator itstr迭代器得到的值为char ，所以比较此时值是否为界符时，需要将
	*vector<string>:: iterator iter迭代器 每个元素的首元素进行比较，即string类的 首元素就是char了
	*这样就可以进行比较
	*/
 for(vector<string>::iterator iter=delim.begin();iter!=delim.end();iter++)
	{
			if((*iter)[0]==*itstr)
			{
				return true;
			}
	}
 return false;
}

//判断是否是运算符
bool Analysis::isOpera()
{
	//同上
	 for(vector<string>::iterator iter=delim.begin();iter!=delim.end();iter++)
	{
		if((*iter)[0]==*itstr)
			{
				return true;
			}
	}
 return false;
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
/*
//判断是否是空格
bool Analysis::isSpace()
{
	if(*itstr==' ')
		return true;
	return false;
}*/

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
		{output(ID_FLAG,token);	}	
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

				
}

