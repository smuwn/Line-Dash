#pragma once

#include <Windows.h>
#include <assert.h>
#include <iostream>
#include <string.h>
#include <string>



enum optiuni {
	StartGame = 0,
	Credits = 1,
	Options = 2,
	Exit = 3
};

const COORD TopRight = { 80 / 2 - (sizeof("Start Game") / 2), 24 / 2 - 3 };
const COORD MiddleRight = { 80 / 2 - (sizeof("Credits & Updates") / 2), 24 / 2 - 2 };
const COORD MiddleRight1 = { 80 / 2 - (sizeof("Options") / 2),24 / 2 - 1 };
const COORD BottomRight = { (80 / 2 - (sizeof("Exit") / 2)), 24 / 2 };

class menu
{
public:

	static HANDLE hOutput;
	static HANDLE hInput;

private:
	static menu* _menu;
	menu() {};
	//Regula celor 3
	menu(menu&) {};
	menu& operator= (const menu&) { return *this;  };
	~menu() {};
public:
	static void Create();
	static void Destroy();
	static menu* GetInstance();

public:
	INPUT_RECORD irRecord;
	optiuni ShowMenu();
};

optiuni menu::ShowMenu()
{
	short lvalue;
	int i;
	optiuni OptOpt = static_cast<optiuni>(0);
	std::string szOpt[] = {
		"Start Game",
		"Credits & Updates",
		"Options",
		"Exit"
	};
	while (true)
	{
		for (i = 0; i < 4; i++)
			if (i == static_cast<int>(OptOpt))
			{
				if (i == 0)
					SetConsoleCursorPosition(hOutput, TopRight);
				else if (i == 1)
					SetConsoleCursorPosition(hOutput, MiddleRight);
				else if (i == 2)
					SetConsoleCursorPosition(hOutput, MiddleRight1);
				else
					SetConsoleCursorPosition(hOutput, BottomRight);
				SetConsoleTextAttribute(hOutput, 10);
				std::cout << szOpt[i] << '\n';
			}
			else
			{
				if (i == 0)
					SetConsoleCursorPosition(hOutput, TopRight);
				else if (i == 1)
					SetConsoleCursorPosition(hOutput, MiddleRight);
				else if (i == 2)
					SetConsoleCursorPosition(hOutput, MiddleRight1);
				else
					SetConsoleCursorPosition(hOutput, BottomRight); 
				SetConsoleTextAttribute(hOutput, 7);
				std::cout << szOpt[i]<<'\n';
			}
		while (true)
		{
			DWORD dwNumberOfEventsRead = 0;
			ReadConsoleInput(hInput, &irRecord, 1, &dwNumberOfEventsRead);
			if (irRecord.EventType == MOUSE_EVENT)
			{
				if (irRecord.Event.MouseEvent.dwMousePosition.X >= 80 / 2 - (sizeof("Start Game") / 2) &&
					irRecord.Event.MouseEvent.dwMousePosition.X <= 80 / 2 + (sizeof("Start Game") / 2) &&//First
					irRecord.Event.MouseEvent.dwMousePosition.Y == 24 / 2 - 3)
				{
					OptOpt = StartGame;
					if (irRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
						return OptOpt;
					break;
				}
				else if (irRecord.Event.MouseEvent.dwMousePosition.X >= 80 / 2 - (sizeof("Credits & Updates") / 2) &&
					irRecord.Event.MouseEvent.dwMousePosition.X <= 80 / 2 + (sizeof("Credits & Updates") / 2) &&
					irRecord.Event.MouseEvent.dwMousePosition.Y == 24 / 2 - 2)
				{
					OptOpt = Credits;
					if (irRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
						return OptOpt;
					break;
				}
				else if (irRecord.Event.MouseEvent.dwMousePosition.X >= 80 / 2 - (sizeof("Options") / 2) &&
					irRecord.Event.MouseEvent.dwMousePosition.X <= 80 / 2 + (sizeof("Options") / 2) &&
					irRecord.Event.MouseEvent.dwMousePosition.Y == 24 / 2 - 1)
				{
					OptOpt = Options;
					if (irRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
						return OptOpt;
					break;
				}
				else if (irRecord.Event.MouseEvent.dwMousePosition.X >= 80 / 2 - (sizeof("Exit") / 2) &&
					irRecord.Event.MouseEvent.dwMousePosition.X <= 80 / 2 + (sizeof("Exit") / 2) &&
					irRecord.Event.MouseEvent.dwMousePosition.Y == 24 / 2)
				{

					OptOpt = Exit;
					if (irRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
						return OptOpt;
					break;
				}
			}
			if (irRecord.EventType == KEY_EVENT)
			{
				if (irRecord.Event.KeyEvent.wVirtualKeyCode == VK_DOWN && irRecord.Event.KeyEvent.bKeyDown)
				{
					lvalue = static_cast<int>(OptOpt);
					if (lvalue + 1 >= 4)
						lvalue = -1;
					OptOpt = static_cast<optiuni>(lvalue + 1);
					break;
				}
				else if (irRecord.Event.KeyEvent.wVirtualKeyCode == VK_UP && irRecord.Event.KeyEvent.bKeyDown)
				{
					lvalue = static_cast<int>(OptOpt);
					if (lvalue - 1 < 0)
						lvalue = 4;
					OptOpt = static_cast<optiuni>(lvalue - 1);
					break;
				}
				if (irRecord.Event.KeyEvent.wVirtualKeyCode == VK_RETURN && irRecord.Event.KeyEvent.bKeyDown)
					return OptOpt;
				if (irRecord.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE && irRecord.Event.KeyEvent.bKeyDown)
					return Exit;
			}
		}
	}
}

menu* menu::_menu = nullptr;
HANDLE menu::hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE menu::hInput = GetStdHandle(STD_INPUT_HANDLE);

void menu::Create()
{
	_menu = new menu;
}

void menu::Destroy()
{
	delete _menu;
}

menu* menu::GetInstance()
{
	return _menu;
}
