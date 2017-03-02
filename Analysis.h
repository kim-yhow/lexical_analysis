#ifndef ANALY_H
#define ANALY_H
//因为在使用STL（C++标准模板库）的时候经常引发类似的错误，尤其是vector，map这类模板类，模板中套模板，一不小心就超长了。如果去掉这一句，会有警告
#pragma   warning (disable: 4786)
#include<vector>
#include<iostream>
#include<string>
#include <map>
#include <iomanip>
/*标识符*/
#define NORMAL_ID				 0			//所有标识符
/*常数*/
#define CONST_NUM_INT    1		    //整型常数
#define CONST_NUM_REAL   2			//实型常数
#define CONST_CHAR       3			//字符常数
/*保留字*/
#define KEY_BOOL		4			//bool
#define KEY_BREAK       5			//break
#define KEY_CASE		6			//case
#define KEY_CATCH		7			//catch
#define KEY_CHAR        8			//char
#define KEY_CLASS		9			//class
#define	KEY_CONST		10			//const
#define KEY_DEFAULT     11         //default
#define KEY_DO	        12			//do
#define KEY_DOUBLE		13			//double
#define	KEY_ELSE		14			//else
#define	KEY_ENUM		15			//enum
#define KEY_EXTERN		16			//extern
#define KEY_FALSE       17			//false
#define KEY_FLOAT       18			//float
#define KEY_FOR				19			//for
#define	KEY_FRIEND			20			//friend
#define	KEY_GOTO			21			//goto
#define	KEY_IF				22			//if
#define	KEY_INLINE			23			//inline
#define KEY_INT				24			//int
#define	KEY_LONG			25			//long
#define	KEY_MAIN			26			//main
#define	KEY_NAMESPACE		27			//namespace
#define	KEY_NEW				28			//new
#define	KEY_OPERATOR		29			//operator
#define	KEY_PRIVATE			30			//pivate
#define KEY_PROTECTED		31			//protected
#define KEY_PUBLIC			32			//public
#define KEY_RETURN			33			//return
#define KEY_SHORT			34			//short
#define KEY_STRUCT			35			//struct
#define	KEY_SIZEOf			36			//sizeof
#define	KEY_STATIC			37			//static
#define	KEY_THROW			38			//throw
#define	KEY_SWITCH			39			//switch
#define	KEY_TEMPLATE		40			//template
#define	KEY_THIS			41			//this
#define	KEY_TRUE			42			//true
#define	KEY_TRY				43			//try
#define	KEY_TYPEDEF			44			//typedef
#define KEY_USING			45			//using
#define KEY_TYPENAME		46			//typename
#define KEY_UNION			47			//union
#define KEY_UNSIGNED		48			//unsigned
#define KEY_VIRTUAL			49			//virtual
#define KEY_VOID			50			//void
#define KEY_WHILE			51			//while	
#define KEY_INCLUDE			52			//#include
/*运算符*/
#define OPER_LEFT_KUO			53			//(
#define	OPER_RIGHT_KUO			54			//)
#define	OPER_EQUAL				55			//=
#define OPER_DOU_EQUAL			56			//==
#define	OPER_NEQUAL				57			//!=					
#define	OPER_GT					58			//>
#define	OPER_GE					59			//>=
#define	OPER_LT					60			//<
#define	OPER_LE					61			//<=
#define	OPER_LEFT_LEFT			62			//<<
#define	OPER_RIGHT_RIGHT		63			//>>
#define	OPER_PLUS				64			//+
#define	OPER_MINUS				65			//-
#define	OPER_MUL				66			//*
#define	OPER_DIVIDE				67			// /
#define OPER_PLUS_PLUS			68			//++
#define	OPER_MINUS_MINUS		69			//--
#define	OPER_POINT_ARROW		70			//->
#define	OPER_AND				71			//&
#define	OPER_AND_AND			72			//&&
#define OPER_POINT				73			//.
#define OPER_LEFT_MID			74			//[
#define OPER_RIGHT_MID			75			//]
/*界符*/
#define DELIM_LEFT_BIG_KUO		76			//{
#define	DELIM_RIGHT_BIG_KUO		77			//}
#define	DELIM_FENHAO			78			//;

/*其他*/
#define ERROR					79			//error`



using namespace std;


class Analysis
{
public:
	Analysis(char *filename);
	bool Load();						//初始化加载文件
	bool LoadFile(char* filename);		//加载源程序文件
	bool LoadKeys(char* filename);		//加载保留字文件
	bool LoadOpera(char* filename);		//加载运算符文件
	bool LoadDelim(char* filename);		//加载界符文件
	void scanner();				    	//开始分析
	void output(int tmp,string tok);				//输出
	bool isOpera();						//判断此时是否为运算符
	bool isDelim();						//判断此时是否是界符
	bool isDigital();					//判断此时是否是数字
	bool isTokenKey();				//判断此时是否是保留字
	bool isLetter();				//判断是否是字母
//	bool isSpace();					//判断是否是空格
	void initToken();			//初始化token
	void getToken();				//将当前元素存放到token中，并且string迭代器指向下一个元素

private:
	char *filename;					//文件名
	vector<string> keys;			//保留字
	vector<string> opera;			//运算符
	vector<string> delim;		//界符
	string file_text;			//文件中的内容
	string::iterator itstr;		//string的迭代器
	string token;				//一个元素
	int NUM_FLAG;				//用于判断是整型数还是实数
	int ID_FLAG;				//用于判断是否是保留字
};


#endif
