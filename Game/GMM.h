#pragma once

#include <Windows.h>
#include <iostream>
#include <string>
#include <string.h>


class GMM
{
private:
	static GMM* _instance;
	static HANDLE hOutPut;
	static HANDLE hInPut;

private:
	GMM() { };
	//Regula celor 3
	GMM(GMM&) { };
	GMM& operator = (GMM&) { };
	~GMM() { };

public:
	enum options {
		Continue = 0,
		Exit = 1
	};

public:
	static void Create();
	static void Destroy();
	static GMM* GetInstance();

public:
	options ShowMenu();
};

GMM* GMM::_instance = nullptr;
HANDLE GMM::hOutPut = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE GMM::hInPut = GetStdHandle(STD_INPUT_HANDLE);

GMM::options GMM::ShowMenu()
{
	system("CLS");
	int i;
	short lvalue;
	options opt = Continue;
	DWORD dwNOR;
	INPUT_RECORD irRecord;
	std::string str[] = {
		"Continue",
		"Exit"
	};
	while (true)
	{
		for (i = 0; i < 2; i++)
		{
			if (i==opt)
			{
				if (i == 0)
					SetConsoleCursorPosition(hOutPut, { 80 / 2 - sizeof("Continue") / 2,24 / 2 - 1 });
				else
					SetConsoleCursorPosition(hOutPut, { 80 / 2 - sizeof("Exit") / 2,24 / 2 });
				SetConsoleTextAttribute(hOutPut, 10);
				std::cout << str[i]<<'\n';
			}
			else
			{
				if (i == 0)
					SetConsoleCursorPosition(hOutPut, { 80 / 2 - sizeof("Continue") / 2,24 / 2 - 1 });
				else
					SetConsoleCursorPosition(hOutPut, { 80 / 2 - sizeof("Exit") / 2,24 / 2 });
				SetConsoleTextAttribute(hOutPut, 7);
				std::cout << str[i] << '\n';
			}
		}
		while (true)
		{
			ReadConsoleInput(hInPut, &irRecord, 1, &dwNOR);
			if (irRecord.EventType == KEY_EVENT)
			{
				if (irRecord.Event.KeyEvent.wVirtualKeyCode == VK_UP && irRecord.Event.KeyEvent.bKeyDown)
				{
					lvalue = static_cast<short>(opt);
					if (lvalue - 1 < 0)
						lvalue = 2;
					opt = static_cast<options>(lvalue - 1);
					break;
				}
				else if (irRecord.Event.KeyEvent.wVirtualKeyCode == VK_DOWN && irRecord.Event.KeyEvent.bKeyDown)
				{
					lvalue = static_cast<short>(opt);
					if (lvalue + 1 > 1)
						lvalue = -1;
					opt = static_cast<options>(lvalue + 1);
					break;
				}
				if (irRecord.Event.KeyEvent.wVirtualKeyCode == VK_RETURN && irRecord.Event.KeyEvent.bKeyDown)
					return opt;
			}
		}
	}
}


void GMM::Create()
{
	_instance = new GMM;
}

void GMM::Destroy()
{
	delete _instance;
}

GMM* GMM::GetInstance()
{
	return _instance;
}

