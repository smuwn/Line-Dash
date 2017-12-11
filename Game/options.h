#pragma once
#include "variabile.h"


#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>

namespace options{
	enum setari {
		Greutate = 0,
		Nume = 1,
		Resetare = 2,
		Exit = 3
	};
	class options
	{
	private:
		options() { };
		//Regula celor 3
		options(const options&) { };
		~options() { };
		options& operator = (options&) { return *this; };
	private:
		static HANDLE hInPut, hOutPut;
		static options* _opt;
	public://Singletone
		static void Create();
		static void Destroy();
		static options* GetInstance();
	public:
		setari ShowMenu();
	};

}

using options::setari;

options::options* options::options::_opt = nullptr;
HANDLE options::options::hInPut = GetStdHandle(STD_INPUT_HANDLE);
HANDLE options::options::hOutPut = GetStdHandle(STD_OUTPUT_HANDLE);

setari options::options::ShowMenu()
{
	system("CLS");
	short i, lvalue, rvalue = -1;
	char *temp = new char[8];
	DWORD dwNOR = 0;
	INPUT_RECORD irRecord;
	setari set = Greutate;
	std::string optiuni[] = {
		"Difficulty",
		"Set name",
		"Reset High-Score"
	};
	while (true)
	{
		system("CLS");
		for (i = 0; i < 3; i++)
			if (i == set)
			{
				if (i == 0)
					SetConsoleCursorPosition(hOutPut, { 19, 9 });
				else if (i == 1)
					SetConsoleCursorPosition(hOutPut, { 19, 10 });
				else if (i == 2)
					SetConsoleCursorPosition(hOutPut, { 19, 11 });
				SetConsoleTextAttribute(hOutPut, 10);
				if (i == 0)
				{
					std::cout << optiuni[0];
					if (rvalue == -1)
					{
						SetConsoleTextAttribute(hOutPut, 7);
						std::cout << "\tEasy(30)\tMedium(20)\tHard(15)";
					}
					else if (rvalue == 0)
					{
						SetConsoleTextAttribute(hOutPut, 10);
						std::cout << "\tEasy(30)";
						SetConsoleTextAttribute(hOutPut, 7);
						std::cout << "\tMedium(20)\tHard(15)";
					}
					else if (rvalue == 1)
					{
						SetConsoleTextAttribute(hOutPut, 7);
						std::cout << "\tEasy(30)";
						SetConsoleTextAttribute(hOutPut, 10);
						std::cout << "\tMedium(20)";
						SetConsoleTextAttribute(hOutPut, 7);
						std::cout << "\tHard(15)";
					}
					else if (rvalue == 2)
					{
						SetConsoleTextAttribute(hOutPut, 7);
						std::cout << "\tEasy(30)\tMedium(20)";
						SetConsoleTextAttribute(hOutPut, 10);
						std::cout << "\tHard(15)";
					}
				}
				else
				{
					std::cout << optiuni[i];
				}
			}
			else
			{
				if (i == 0)
					SetConsoleCursorPosition(hOutPut, { 19, 9 });
				else if (i == 1)
					SetConsoleCursorPosition(hOutPut, { 19, 10 });
				else if (i == 2)
					SetConsoleCursorPosition(hOutPut, { 19, 11 });
				SetConsoleTextAttribute(hOutPut, 7);
				std::cout << optiuni[i];
			}
		while (true)
		{
			ReadConsoleInput(hInPut, &irRecord, 1, &dwNOR);
			if (irRecord.EventType == KEY_EVENT)
			{
				if (irRecord.Event.KeyEvent.bKeyDown && irRecord.Event.KeyEvent.wVirtualKeyCode == VK_LEFT && set == Greutate)
				{
					if (rvalue - 1 < 0)
						rvalue = 3;
					--rvalue;
					break;
				}
				else if (irRecord.Event.KeyEvent.bKeyDown && irRecord.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT && set == Greutate)
				{
					if (rvalue + 1 > 2)
						rvalue = -1;
					++rvalue;
					break;
				}
				if (irRecord.Event.KeyEvent.bKeyDown && irRecord.Event.KeyEvent.wVirtualKeyCode == VK_DOWN)
				{
					lvalue = static_cast<short>(set);
					if (lvalue + 1 > 2)
						lvalue = -1;
					set = static_cast<setari>(lvalue + 1);
					break;
				}
				else if (irRecord.Event.KeyEvent.bKeyDown && irRecord.Event.KeyEvent.wVirtualKeyCode == VK_UP)
				{
					lvalue = static_cast<short>(set);
					if (lvalue - 1 < 0)
						lvalue = 3;
					set = static_cast<setari>(lvalue - 1);
					break;
				}
				if (irRecord.Event.KeyEvent.wVirtualKeyCode == VK_RETURN && irRecord.Event.KeyEvent.bKeyDown && set == Greutate && rvalue != -1)
				{
					if (rvalue == 0)
						wSleepTime = 30;
					else if (rvalue == 1)
						wSleepTime = 20;
					else if (rvalue == 2)
						wSleepTime = 15;
					SetConsoleCursorPosition(hOutPut, { 0,24 });
					std::cout << "Setarile au avut loc. Bafta la joc!";
					Sleep(2000);
					break;
				}
				if (irRecord.Event.KeyEvent.wVirtualKeyCode == VK_RETURN && irRecord.Event.KeyEvent.bKeyDown && set == Nume)
				{
					SetConsoleCursorPosition(hOutPut, { 0,23 });
					std::cout << "Introduceti un nume format din MAXIM 7 litere";
					SetConsoleCursorPosition(hOutPut, { 31,10 });
					std::cin >> temp;
					if (strlen(temp) > 0 && strlen(temp) <= 7)
						_Nume = temp;
					else
						throw("Invalid name");
					SetConsoleCursorPosition(hOutPut, { 0,24 });
					SetConsoleTextAttribute(hOutPut, 10);
					std::cout << "Setarile au avut loc. Bafta la joc!";
					Sleep(2000);
					break;
				}
				if (irRecord.Event.KeyEvent.wVirtualKeyCode == VK_RETURN && irRecord.Event.KeyEvent.bKeyDown && set != Greutate)
					return set;
				if (irRecord.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE && irRecord.Event.KeyEvent.bKeyDown)
					return Exit;
			}
		}
	}
}

void options::options::Create()
{
	_opt = new options;
}

void options::options::Destroy()
{
	delete _opt;
}

options::options* options::options::GetInstance()
{
	return _opt;
}