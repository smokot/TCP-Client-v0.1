#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include "ctime"
#include "string"
#include "map"
#include "list"
#include "cstdlib"
#include "forward_list"
#include "fstream"
#include "conio.h"
#include "vector"
#include "memory"
#include "thread"
#include "stack"
#include "chrono"

using namespace std;


void SPISOKTEM()
{
	while (true)
	{
		string tema, answer;
		ofstream file("C:\\Users\\SMOKOT\\Desktop\\turing\\C++\\knowledgesC++.txt", ios::app);
		cout << "Тема: "; getline(cin, tema); cout << "Выучено?: "; getline(cin, answer);
		file << "Тема: " << tema << " Выучено?: " << answer << endl;
		cout << "-----------------------------------------------------" << endl;
		file.close();
	}
}

void StrToChar(string &_x,char(&_y)[256])
{
	for (int i = 0; i < _x.size(); i++)
	{
		_y[i] = _x[i];
	}
}
void systemdo(string &_x)
{
	char _y[256]=" ";
	for (int i = 0; i < _x.size(); i++)
	{
		_y[i] = _x[i];
	}
	system(_y);
}













//////////////////////////////////////////////////////////////////////////////////////////////////////////

int _tmain(int argc, char * argv[])
{
	





	_getch();



}
//////////////////////////////////////////////////////////////////////////////////////////////////////////