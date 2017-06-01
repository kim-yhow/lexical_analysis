#ifndef FUN_H
#define FUN_H
#include<string>
#include<vector>
#include"Identitier.h"
using namespace std;

struct Fun
{
	string name;
	vector<Identitier> funidenty;
	Fun (){}
	Fun(string Na):name(Na)
	{}
};
#endif