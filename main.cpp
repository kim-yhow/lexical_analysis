#include<iostream>
#include<string>
#include"Analysis.h"

using namespace std;
/*
*
*简单词法分析器
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
	cout<<"运行时间："<<finish-start<<endl;

}
