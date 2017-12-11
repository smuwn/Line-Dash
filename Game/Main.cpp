#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <ctime>
#include <conio.h>
#include <fstream>
#include <string>
#include <string.h>


#include "variabile.h"
#include "GMM.h"
#include "game.h"
#include "options.h"
#include "menu.h"
#include "Credits.h"

#pragma comment(lib, "winmm.lib")



int main()
{
	static long long int  hi_score = 0;
	SetConsoleTitle("Line Dash");
	srand((unsigned int)time(NULL));
	_Nume = "Jucator";
	optiuni meniu;
	menu::Create();
	while (true)
	{
		meniu = (menu::GetInstance()->ShowMenu());
		if (meniu == StartGame)
		{
			long long int score = 0;
			UINT i = 78;
			bool bLived = false;
			system("CLS");
			UINT Rand = rand() % 20 + 1;
			Game::Create();
			Game::Jucator *jucator = new Game::Jucator;
			jucator->_PositionOnConsole = Default;
			jucator->HP = 3;
			jucator->_nume = _Nume;
			Game::GetInstance()->DrawGrid();
			Game::GetInstance()->DrawPlayer(jucator, true);
			while (true)
			{
				if (GetAsyncKeyState(VK_ESCAPE))
				{
					GMM::Create();
					GMM::options optiuni;
					optiuni = GMM::GetInstance()->ShowMenu();
					if (optiuni == GMM::Continue)
					{
						system("CLS");
						Game::GetInstance()->DrawGrid();
						Game::GetInstance()->DrawPlayer(jucator, true);
					}
					else if (optiuni == GMM::Exit)
					{
						system("CLS");
						break;
					}
					GMM::Destroy();
				}
				if (i < 1)
				{
					Rand = rand() % 20 + 2;
					i = 78;
					bLived = false;
				}
				Game::GetInstance()->DrawMoveLine(Rand, i--);
				Game::GetInstance()->MovePlayer(jucator);
				if (jucator->_PositionOnConsole.Y == Rand && i == 5)
				{
					char a[256];
					score++;
					if (score > hi_score)
						hi_score = score;
					sprintf(a, "Ai primit un punct. Acum ai %lld puncte.\t  Cel mai mare scor este %lld.", score, hi_score);
					Game::GetInstance()->ShowMessage(a, { 0,24 });
				}
				if (jucator->_PositionOnConsole.Y != Rand && i >= 5 && i <= 5 + strlen(jucator->_nume))
				{
					if (!bLived)
					{
						jucator->HP--;
						bLived = true;
					}
					if (jucator->HP == 0)
					{
						GameOver();
						system("CLS");
						break;
					}
				}
			}
		}
		else if (meniu == Credits)
		{
			while (true)
			{
				DWORD dwEventsRead;
				INPUT_RECORD irRecord;
				PutCreditsOnScreen();
				PutUpdatesOnScreen();
				while (true)
				{
					ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &irRecord, 1, &dwEventsRead);
					if (irRecord.EventType == KEY_EVENT)
						if (irRecord.Event.KeyEvent.bKeyDown && irRecord.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
							break;
				}
				system("CLS");
				break;
			}
		}
		else if (meniu == Options)
		{
			setari set;
			options::options::Create();
			try
			{
				set = options::options::GetInstance()->ShowMenu();
			}
			catch (char *)
			{
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,24 });
				std::cout << "Nu ai introdus un nume corect. Mai incearca o data.";
				Sleep(2000);
			}
			if (set == setari::Resetare)
			{
				hi_score = 0;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,24 });
				std::cout << "Setarile au avut loc. Bafta la joc!";
				Sleep(2000);
			}
			system("CLS");
			options::options::Destroy();
		}
		else if (meniu == Exit)
		{
			Game::Destroy();
			menu::Destroy();
			return 0;
		}
	}
}

