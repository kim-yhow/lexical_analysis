#ifndef IDEN_H
#define IDEN_H
#include<string>
using namespace std;


struct Identitier
{
	string ID_Value;	//��ʶ��ֵ
	string ID_Type;		//��ʾ��ʶ������ ��int ��
	string ID_FunName;  //���ں�����,ȫ����Ϊȫ�ֱ���
	bool mHEAD_FLAG;	//�Ƿ���ͷ�ļ�

	Identitier()		
	{}
	
	Identitier(string idva):ID_Value(idva)
	{}
	
	Identitier(string idVa,string id_type,string funname,bool mH_F)
		:ID_Value(idVa),ID_Type(id_type),ID_FunName(funname),mHEAD_FLAG(mH_F)
	{}
};


#endif