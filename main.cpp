#include<iostream>
#include<string>
#include"Analysis.h"

using namespace std;
/*
*
*�򵥴ʷ�������
*@kim_yhow
*
 */
void main()
{
	clock_t start,finish;  
    start=clock();  
	Analysis Compiler("test.txt");
	Compiler.scanner();
	finish=clock();
	cout<<"����ʱ�䣺"<<finish-start<<endl;

}
