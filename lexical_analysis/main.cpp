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
	cout<<"����ʱ�䣺"<<finish-start<<endl;
}
