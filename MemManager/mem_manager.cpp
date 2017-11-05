#include "MemPage_t.h"
#include "MemManager_t.h"
#include "MemPool_t.h"
#include <iostream>
#include <cstring>
#include <stdio.h>

using namespace std;

enum UserChoice {EXIT = 0, SET_POSITION, WRITE_INT, READ_INT, WRITE_STRING, READ_STRING, GET_POSITION, CHANGE_DEFAULT_SIZE};

int Run();
void WriteString(MemManager_t& manager);
void ReadString(MemManager_t& manager);
void SetPosition(MemManager_t& manager);
void WriteInt(MemManager_t& manager);
void ReadInt(MemManager_t& manager);

int main()
{
	Run();
	
	return 0;
}

int Run()
{
	UserChoice choice = SET_POSITION;
	int c;
	MemPool_t pool;
	MemManager_t& manager = pool;
	
	while(choice != EXIT)
	{
		cout << "Choose option:" << endl << "1. Set position" << endl
										 << "2. Write int" << endl
										 << "3. Read int" << endl
										 << "4. Write string" << endl
										 << "5. Read string" << endl
										 << "6. Get current position" << endl
										 << "7. Set default page size" << endl
										 << "0. Exit" << endl
										 << endl << endl;
		cin >> c;
		choice = (UserChoice)c;
	
		switch(choice)
		{
			case SET_POSITION:
				SetPosition(manager);				
				break;
			case WRITE_INT:
				WriteInt(manager);
				break;
			case READ_INT:		
				ReadInt(manager);
				break;
			case WRITE_STRING:	
				WriteString(manager);
				break;
			case READ_STRING:
				ReadString(manager);
				break;
			case GET_POSITION:
				cout << manager.GetPos() << endl;
				break;
			case CHANGE_DEFAULT_SIZE:
				break;
			case EXIT:
				break;
			default:
				cout << "Incorrect choice" << endl;
				break;
		}
	}
	
	return 0;
}

void WriteString(MemManager_t& manager)
{
	std::string s;
	char cstr[128];
	cout << "Enter string..." << endl;
	getchar(); //??
	std::getline(std::cin, s);
	strcpy(cstr, s.c_str());
	manager.MemWrite(cstr, (size_t)s.length() + 1);
}

void ReadString(MemManager_t& manager)
{
	char str[128];
	int length;
	cout << "Enter string length..." << endl;
	cin >> length;	
	manager.MemRead(str, length);
	cout << str << endl;
}

void SetPosition(MemManager_t& manager)
{
	size_t pos;
	cout << "Enter position..." << endl;
	cin >> pos;
	cout << (manager.SetPos(pos) == MemManager_t::MEM_SUCCESS ? "Possition set" : "Failure!") << endl;
}

void WriteInt(MemManager_t& manager)
{
	int num;	
	cout << "Enter integer..." << endl;
	cin >> num;
	if(manager.MemWrite(&num, sizeof(int)) != sizeof(int))
	{
		cout << "Error occured!" << endl;
	}
	else
	{
		cout << "Done!" << endl;
	}
}

void ReadInt(MemManager_t& manager)
{
	int num;	
	if(manager.MemRead((void*) &num, sizeof(int)) != sizeof(int))
	{
		cout << "Error occured!" << endl;
	}
	else
	{
		cout << "Integer read: " << num << endl;
	}
}





























