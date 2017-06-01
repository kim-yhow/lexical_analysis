#ifndef IDEN_H
#define IDEN_H
#include<string>
using namespace std;


struct Identitier
{
	string ID_Value;	//标识符值
	string ID_Type;		//表示标识符类型 如int 等
	string ID_FunName;  //所在函数名,全局则为全局变量
	bool mHEAD_FLAG;	//是否是头文件

	Identitier()		
	{}
	
	Identitier(string idva):ID_Value(idva)
	{}
	
	Identitier(string idVa,string id_type,string funname,bool mH_F)
		:ID_Value(idVa),ID_Type(id_type),ID_FunName(funname),mHEAD_FLAG(mH_F)
	{}
};


#endif