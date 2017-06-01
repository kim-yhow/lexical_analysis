#ifndef ANALY_H
#define ANALY_H
//��Ϊ��ʹ��STL��C++��׼ģ��⣩��ʱ�򾭳��������ƵĴ���������vector��map����ģ���࣬ģ������ģ�壬һ��С�ľͳ����ˡ����ȥ����һ�䣬���о���
#pragma   warning (disable: 4786)
#include<vector>
#include<iostream>
#include<string>
#include<ctime>
#include <map>
#include <iomanip>
#include "Identitier.h"
#include "Funs.h"
/*��ʶ��*/
#define		NORMAL_ID				 0			//���б�ʶ��
/*����*/
#define		CONST_NUM_INT    1		    //���ͳ���
#define		CONST_NUM_REAL   2			//ʵ�ͳ���
#define		CONST_CHAR       3			//�ַ�����
/*������*/
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
/*�����*/
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
/*���*/
#define		DELIM_LEFT_BIG_KUO		110			//{
#define		DELIM_RIGHT_BIG_KUO		111			//}
#define		DELIM_FENHAO			112			//;

/*��ϣ����*/
#define HASH_KEYS				80			//������	

/*����*/
#define ERROR					404		//error
#define INCLUDE					120		//#include
#define VARIABLE				121			//����
#define HEADFILE				122			//ͷ�ļ�		
#define STDFILE					123			//��׼��


using namespace std;


class Analysis
{
public:
	Analysis(char *filename);
	bool Load();									//��ʼ�������ļ�
	bool LoadFile(char* filename);					//����Դ�����ļ�
	bool LoadKeys(char* filename);					//���ر������ļ�
	void scanner();									//��ʼ����
	void output(int tmp,string tok);				//���
	void output(int tmp,Identitier idr);			//���
	void output(int tmp,Fun fun);					//���
	bool isDigital();								//�жϴ�ʱ�Ƿ�������
	bool isTokenKey();							    //�жϴ�ʱ�Ƿ��Ǳ�����
	bool isLetter();								//�ж��Ƿ�����ĸ
	void initToken();							    //��ʼ��token
	void getToken();								//����ǰԪ�ش�ŵ�token�У�����string������ָ����һ��Ԫ��
	bool saveIdr();									//�����ֵı�ʾ�������ļ�
	void setIdentType();						    //����һ����ǣ�������һ���ж��¸���ʶ��
	void setmfunName(string name);			    	//��¼������
	void rmFunName();							    //��ȥ������
	void SetHeadFlag(bool b);						//��ʾ��ͷ�ļ�����
	void setStdIdent();								//����һЩstd����ı�ʶ
	Identitier isIdent_ider();						//�жϴ�ʱ�����Ƿ񱻶���
	Fun isIdent_fun();								//�жϴ�ʱ�ĺ����Ƿ��Ǳ������
	
	bool isFunction();							    //�ж��Ƿ��Ǻ���
	bool IsFunset(string::iterator &tempIt);		//�ж��Ƿ����㺯����Ҫ��

private:
	vector<Fun>::iterator mfun_index;			//����ָ�룬����ָ���ʱ���ĸ�������
	char *mFilename;						//�ļ���
	string mKeys[HASH_KEYS];				//������
	string mFile_text;						//�ļ��е�����
	string::iterator mItstr;				//string�ĵ�����
	string mToken;							//һ��Ԫ��
	bool mHead_FLAG;						//ͷ�ļ���־
	bool mIsHaveStd;						//�Ƿ����std
	int mNUM_FLAG;							//�����ж�������������ʵ��
	int mID_FLAG;							//�����ж��Ƿ��Ǳ�����
	vector<Identitier> mIdents;				//��ʶ������
	vector<Fun> mfuns;						//��ź���
	int mIdentType;							//�����ж��Ƿ��¸���ʶ��������
	int mDelimFlag;							//�����������С���ŵ�ƥ��
	string mFunName;						//���ڼ�¼������
};



#endif