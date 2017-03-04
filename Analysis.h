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
/*标识符*/
#define NORMAL_ID				 0			//所有标识符
/*常数*/
#define CONST_NUM_INT    1		    //整型常数
#define CONST_NUM_REAL   2			//实型常数
#define CONST_CHAR       3			//字符常数
/*保留字*/
#define KEY_BOOL		16			//bool
#define KEY_BREAK       15			//break
#define KEY_CASE		14			//case
#define KEY_CATCH		17			//catch
#define KEY_CHAR        27			//char
#define KEY_CLASS		28			//class
#define	KEY_CONST		29			//const
#define KEY_DEFAULT     34         //default
#define KEY_DO	        30			//do
#define KEY_DOUBLE		19			//double
#define	KEY_ELSE		24			//else
#define	KEY_ENUM		32			//enum
#define KEY_EXTERN		33			//extern
#define KEY_FALSE       31			//false
#define KEY_FLOAT       44			//float
#define KEY_FOR				42			//for
#define	KEY_FRIEND			35			//friend
#define	KEY_GOTO			45			//goto
#define	KEY_IF				46			//if
#define	KEY_INLINE			47			//inline
#define KEY_INT				59			//int
#define	KEY_LONG			61			//long
#define	KEY_MAIN			73			//main
#define	KEY_NAMESPACE		69			//namespace
#define	KEY_NEW				7			//new
#define	KEY_OPERATOR		8			//operator
#define	KEY_PRIVATE			79			//pivate
#define KEY_PROTECTED		78			//protected
#define KEY_PUBLIC			77			//public
#define KEY_RETURN			18			//return
#define KEY_SHORT			36			//short
#define KEY_STRUCT			37			//struct
#define	KEY_SIZEOf			20			//sizeof
#define	KEY_STATIC			12			//static
#define	KEY_THROW			38			//throw
#define	KEY_SWITCH			21			//switch
#define	KEY_TEMPLATE		22			//template
#define	KEY_THIS			39			//this
#define	KEY_TRUE			23			//true
#define	KEY_TRY				40			//try
#define	KEY_TYPEDEF			25			//typedef
#define KEY_USING			26			//using
#define KEY_TYPENAME		41			//typename
#define KEY_UNION			43			//union
#define KEY_UNSIGNED		48			//unsigned
#define KEY_VIRTUAL			49			//virtual
#define KEY_VOID			50			//void
#define KEY_WHILE			51			//while	
/*运算符*/
#define OPER_LEFT_KUO			80			//(
#define	OPER_RIGHT_KUO			81			//)
#define	OPER_EQUAL				82			//=
#define OPER_DOU_EQUAL			83			//==
#define	OPER_NEQUAL				84			//!=					
#define	OPER_GT					85			//>
#define	OPER_GE					86			//>=
#define	OPER_LT					87			//<
#define	OPER_LE					88			//<=
#define	OPER_LEFT_LEFT			89			//<<
#define	OPER_RIGHT_RIGHT		90			//>>
#define	OPER_PLUS				91			//+
#define	OPER_MINUS				92			//-
#define	OPER_MUL				93			//*
#define	OPER_DIVIDE				94			// /
#define OPER_PLUS_PLUS			95			//++
#define	OPER_MINUS_MINUS		96			//--
#define	OPER_POINT_ARROW		97			//->
#define	OPER_AND				98			//&
#define	OPER_AND_AND			99			//&&
#define OPER_POINT				100			//.
#define OPER_LEFT_MID			101			//[
#define OPER_RIGHT_MID			102			//]
/*界符*/
#define DELIM_LEFT_BIG_KUO		103			//{
#define	DELIM_RIGHT_BIG_KUO		104			//}
#define	DELIM_FENHAO			105			//;

/*其他*/
#define ERROR					106			//error
/*哈希表长度*/
#define HASH_KEYS				80			//保留字	
using namespace std;

class Analysis
{
public:
	Analysis(char *filename);
	bool Load();						//初始化加载文件
	bool LoadFile(char* filename);		//加载源程序文件
	bool LoadKeys(char* filename);		//加载保留字文件
	void scanner();				    	//开始分析
	void output(int tmp,string tok);	//输出
	bool isDigital();					//判断此时是否是数字
	bool isTokenKey();					//判断此时是否是保留字
	bool isLetter();					//判断是否是字母
	void initToken();					//初始化token
	void getToken();					//将当前元素存放到token中，并且string迭代器指向下一个元素
	bool saveIdr();						//将出现的表示符存入文件

private:
	char *filename;						//文件名
	string keys[HASH_KEYS];				//保留字
	vector<string> Idr;					//标识符
	string file_text;				    //文件中的内容
	string::iterator itstr;				//string的迭代器
	string token;						//一个元素
	int NUM_FLAG;						//用于判断是整型数还是实数
	int ID_FLAG;						//用于判断是否是保留字
	int IS_DEF;							//标识符是否被定义
//	vector<string> kkeys;	
};

#endif