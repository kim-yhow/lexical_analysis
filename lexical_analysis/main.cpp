#include<iostream>
#include<string>
#include"Analysis.h"

using namespace std;

void main()
{
	clock_t start,finish;  
    start=clock();  
	Analysis Compiler("Z_test.txt");
	Compiler.scanner();
	finish=clock();
	cout<<"运行时间："<<finish-start<<endl;
}
