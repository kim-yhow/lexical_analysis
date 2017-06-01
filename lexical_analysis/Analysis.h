#ifndef ANALY_H
#define ANALY_H
//因为在使用STL（C++标准模板库）的时候经常引发类似的错误，尤其是vector，map这类模板类，模板中套模板，一不小心就超长了。如果去掉这一句，会有警告
#pragma   warning (disable: 4786)
#include<vector>
#include<iostream>
#include<string>
#include<ctime>
#include <map>
#include <iomanip>
#include "Identitier.h"
#include "Funs.h"
/*标识符*/
#define		NORMAL_ID				 0			//所有标识符
/*常数*/
#define		CONST_NUM_INT    1		    //整型常数
#define		CONST_NUM_REAL   2			//实型常数
#define		CONST_CHAR       3			//字符常数
/*保留字*/
#define		KEY_BOOL		16			//bool
#define		KEY_BREAK       15			//break
#define		KEY_CASE		14			//case
#define		KEY_CATCH		17			//catch
#define		KEY_CHAR        27			//char
#define	    KEY_CLASS		28			//class
#define	    KEY_CONST		29			//const
#define		KEY_DEFAULT     34         //default
#define		KEY_DO	        30			//do
#define		KEY_DOUBLE		19			//double
#define		KEY_ELSE		24			//else
#define		KEY_ENUM		32			//enum
#define		KEY_EXTERN		33			//extern
#define		KEY_FALSE       31			//false
#define		KEY_FLOAT       44			//float
#define		KEY_FOR				42			//for
#define		KEY_FRIEND			35			//friend
#define		KEY_GOTO			45			//goto
#define		KEY_IF				46			//if
#define		KEY_INLINE			47			//inline
#define		KEY_INT				59			//int
#define		KEY_LONG			61			//long
#define		KEY_MAIN			73			//main
#define		KEY_NAMESPACE		69			//namespace
#define		KEY_NEW				7			//new
#define		KEY_OPERATOR		8			//operator
#define		KEY_PRIVATE			79			//pivate
#define		KEY_PROTECTED		78			//protected
#define		KEY_PUBLIC			77			//public
#define		KEY_RETURN			18			//return
#define		KEY_SHORT			36			//short
#define		KEY_STRUCT			37			//struct
#define		KEY_SIZEOf			20			//sizeof
#define		KEY_STATIC			12			//static
#define		KEY_THROW			38			//throw
#define		KEY_SWITCH			21			//switch
#define		KEY_TEMPLATE		22			//template
#define		KEY_THIS			39			//this
#define		KEY_TRUE			23			//true
#define		KEY_TRY				40			//try
#define		KEY_TYPEDEF			25			//typedef
#define		KEY_USING			26			//using
#define		KEY_TYPENAME		41			//typename
#define		KEY_UNION			43			//union
#define		KEY_UNSIGNED		48			//unsigned
#define		KEY_VIRTUAL			49			//virtual
#define		KEY_VOID			50			//void
#define		KEY_WHILE			51			//while	
/*运算符*/
#define		OPER_LEFT_KUO			80			//(
#define		OPER_RIGHT_KUO			81			//)
#define		OPER_EQUAL				82			//=
#define		OPER_DOU_EQUAL			83			//==
#define		OPER_NEQUAL				84			//!=					
#define		OPER_GT					85			//>
#define		OPER_GE					86			//>=
#define		OPER_LT					87			//<
#define		OPER_LE					88			//<=
#define		OPER_LEFT_LEFT			89			//<<
#define		OPER_RIGHT_RIGHT		90			//>>
#define		OPER_PLUS				91			//+
#define		OPER_MINUS				92			//-
#define		OPER_MUL				93			//*
#define		OPER_DIVIDE				94			// /
#define		OPER_PLUS_PLUS			95			//++
#define		OPER_MINUS_MINUS		96			//--
#define		OPER_POINT_ARROW		97			//->
#define		OPER_AND				98			//&
#define		OPER_AND_AND			99			//&&
#define		OPER_POINT				100			//.
#define		OPER_LEFT_MID			101			//[
#define		OPER_RIGHT_MID			102			//]
#define     OPER_DOU				103			//,
#define     OPER_SHUANG_YIN			104			//"
#define		OPER_DAN_YIN			105			//'
/*界符*/
#define		DELIM_LEFT_BIG_KUO		110			//{
#define		DELIM_RIGHT_BIG_KUO		111			//}
#define		DELIM_FENHAO			112			//;

/*哈希表长度*/
#define HASH_KEYS				80			//保留字	

/*其他*/
#define ERROR					404		//error
#define INCLUDE					120		//#include
#define VARIABLE				121			//变量
#define HEADFILE				122			//头文件		
#define STDFILE					123			//标准库


using namespace std;


class Analysis
{
public:
	Analysis(char *filename);
	bool Load();									//初始化加载文件
	bool LoadFile(char* filename);					//加载源程序文件
	bool LoadKeys(char* filename);					//加载保留字文件
	void scanner();									//开始分析
	void output(int tmp,string tok);				//输出
	void output(int tmp,Identitier idr);			//输出
	void output(int tmp,Fun fun);					//输出
	bool isDigital();								//判断此时是否是数字
	bool isTokenKey();							    //判断此时是否是保留字
	bool isLetter();								//判断是否是字母
	void initToken();							    //初始化token
	void getToken();								//将当前元素存放到token中，并且string迭代器指向下一个元素
	bool saveIdr();									//将出现的表示符存入文件
	void setIdentType();						    //设置一个标记，用于下一个判断下个标识符
	void setmfunName(string name);			    	//记录函数名
	void rmFunName();							    //除去函数名
	void SetHeadFlag(bool b);						//表示在头文件后面
	void setStdIdent();								//设置一些std定义的标识
	Identitier isIdent_ider();						//判断此时变量是否被定义
	Fun isIdent_fun();								//判断此时的函数是否是被定义的
	
	bool isFunction();							    //判断是否是函数
	bool IsFunset(string::iterator &tempIt);		//判断是否满足函数的要求

private:
	vector<Fun>::iterator mfun_index;			//函数指针，用于指向此时在哪个函数中
	char *mFilename;						//文件名
	string mKeys[HASH_KEYS];				//保留字
	string mFile_text;						//文件中的内容
	string::iterator mItstr;				//string的迭代器
	string mToken;							//一个元素
	bool mHead_FLAG;						//头文件标志
	bool mIsHaveStd;						//是否加了std
	int mNUM_FLAG;							//用于判断是整型数还是实数
	int mID_FLAG;							//用于判断是否是保留字
	vector<Identitier> mIdents;				//标识符容器
	vector<Fun> mfuns;						//存放函数
	int mIdentType;							//用于判断是否下个标识符的种类
	int mDelimFlag;							//计算大括号与小括号的匹配
	string mFunName;						//用于记录函数名
};



#endif