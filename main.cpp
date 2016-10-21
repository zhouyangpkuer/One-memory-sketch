#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include "cmsketch.h"
#include "csketch.h"
#include "cusketch.h"
#include "cmlsketch.h"

using namespace std;

ifstream fin;
ofstream fout;
string item;
set<string> items;

int main()
{
	set.clear();
	fin.open("", ios::in);
	CMSketch cmsketch(1 << 14, 8, 1, 3);
	while(fin >> item)
	{
		items.insert(item);
		int times;
		fin >> times;
		for(int i = 0; i < times; i++)
		{
			cmsketch.Insert(item.c_str());
		}
	}
	fout.open("", ios::out);
	set<string>::iterator it;
	for(it = items.begin(); it != items.end(); it ++)
	{
		fout << *it << '\t' << cmsketch.Query(it->c_str());
	}
	fin.close();
	fout.close();

	set.clear();
	fin.open("", ios::in);
	CSketch csketch(1 << 14, 8, 1, 3);
	while(fin >> item)
	{
		items.insert(item);
		int times;
		fin >> times;
		for(int i = 0; i < times; i++)
		{
			csketch.Insert(item.c_str());
		}
	}
	fout.open("", ios::out);
	set<string>::iterator it;
	for(it = items.begin(); it != items.end(); it ++)
	{
		fout << *it << '\t' << csketch.Query(it->c_str());
	}
	fin.close();
	fout.close();

	set.clear();
	fin.open("", ios::in);
	CUSketch cusketch(1 << 14, 8, 1, 3);
	while(fin >> item)
	{
		items.insert(item);
		int times;
		fin >> times;
		for(int i = 0; i < times; i++)
		{
			cusketch.Insert(item.c_str());
		}
	}
	fout.open("", ios::out);
	set<string>::iterator it;
	for(it = items.begin(); it != items.end(); it ++)
	{
		fout << *it << '\t' << cusketch.Query(it->c_str());
	}
	fin.close();
	fout.close();

	set.clear();
	fin.open("", ios::in);
	CMLSketch cmlsketch(1 << 14, 8, 1, 3);
	while(fin >> item)
	{
		items.insert(item);
		int times;
		fin >> times;
		for(int i = 0; i < times; i++)
		{
			cmlsketch.Insert(item.c_str());
		}
	}
	fout.open("", ios::out);
	set<string>::iterator it;
	for(it = items.begin(); it != items.end(); it ++)
	{
		fout << *it << '\t' << cmlsketch.Query(it->c_str());
	}
	fin.close();
	fout.close();

	return 0;
}