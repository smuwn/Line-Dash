#pragma once

#include <iostream>
#include <assert.h>
#include <string>
#include <string.h>
#include <windows.h>

#define BLOCK 219

WORD wSleepTime = 30;
char *_Nume;
//Si tea doua :D
//tu ar trebui sa ma inveti pe mine ma ;P
const COORD Default = { 5, 13 };
const COORD Coords = { 50, 23 };

class Game {
private:
	static Game* _game;
	Game() {};
	//Regula celor 3
	Game(Game&) {};
	~Game() {};
	Game& operator=(const Game&) { return *this; };
public: //Singletone
	static HANDLE hInPut;
	static HANDLE hOutPut;
	static void Create();
	static void Destroy();
	static Game* GetInstance();

public:
	INPUT_RECORD irRecord;

	struct Jucator {
		COORD _PositionOnConsole;
		short HP;
		char* _nume;
	};

	void ShowCoords(COORD, Jucator*&);
	void ShowMessage(char*,COORD);
	void DeleteMessage(short);
	void DrawMoveLine(short, short);
	void DeleteLine(short, short);
	void PutPixel(short X, short Y, short character, WORD dwStyle);
	void DrawPlayer(const Jucator* const&, bool);
	void MovePlayer(Jucator*&);
	void DrawGrid();
};

void Game::ShowMessage(char* message,COORD Message)
{
	assert(Message.Y > 22 && Message.Y <= 24);
	SetConsoleTextAttribute(hOutPut, 14);
	SetConsoleCursorPosition(hOutPut, Message);
	std::cout << message;
}

void Game::DeleteMessage(short Y)
{
	assert(Y > 22 && Y <= 24);
	SetConsoleCursorPosition(hOutPut, { 0,Y });
	for (int i = 0; i < 80; i++)
		std::cout << ' ';
}

void Game::ShowCoords(COORD coordonate, Game::Jucator*& jucator)
{
	SetConsoleTextAttribute(hOutPut, 15);
	int i = 0;;
	SetConsoleCursorPosition(hOutPut, Coords);
	for (; i < 20; i++)
		std::cout << ' ';
	SetConsoleCursorPosition(hOutPut, Coords);
	std::cout <<"HP = "<<jucator->HP <<"  X = " << coordonate.X << "  Y = " << coordonate.Y - 1 << "\\";
}

Game* Game::_game = nullptr;

HANDLE Game::hInPut = GetStdHandle(STD_INPUT_HANDLE);
HANDLE Game::hOutPut = GetStdHandle(STD_OUTPUT_HANDLE);

void Game::DeleteLine(short free, short X)
{
	int i = 1;
	for (; i < 22; i++)
		if (i != free)
			PutPixel(X, i, 0,NULL);
}

void Game::DrawMoveLine(short free, short X)
{
	int i = 1;
	for (; i < 22; i++)
	{
		if (i != free)
			PutPixel(X, i, 219,NULL);
	}
	Sleep(wSleepTime);
	DeleteLine(free, X);
}

void Game::Create()
{
	_game = new Game;
}

void Game::Destroy()
{
	delete _game;
}

Game* Game::GetInstance()
{
	return _game;
}

void Game::PutPixel(short X, short Y, short character,WORD wStyle)
{
	assert(character >= 0 && character < 256);
	if (wStyle == NULL)
		wStyle = 15;
	SetConsoleTextAttribute(hOutPut, wStyle);
	COORD a = { X, Y };
	SetConsoleCursorPosition(hOutPut, a);
	std::cout << (char)character;
}

void Game::DrawGrid()
{
	int i = 0;
	for (; i < 80; i++)
	{
		PutPixel(i, 0, BLOCK, 6);
		PutPixel(i, 22, BLOCK, 6);
	}
	for (i = 1; i < 22; i++)
	{
		PutPixel(0, i, BLOCK, 6);
		PutPixel(79, i, BLOCK, 6);
	}
}

void Game::DrawPlayer(const Jucator* const& jucator, bool draw)
{
	unsigned int i=0;
	if (draw)
	{
		SetConsoleTextAttribute(hOutPut, 11);
		SetConsoleCursorPosition(hOutPut, jucator->_PositionOnConsole);
		std::cout << jucator->_nume;
		return;
	}
	SetConsoleCursorPosition(hOutPut, jucator->_PositionOnConsole);
	for (; i++ < strlen(jucator->_nume);)
		std::cout << ' ';
}

void Game::MovePlayer(Jucator*& jucator)
{
	if (GetAsyncKeyState(VK_DOWN))
		if (jucator->_PositionOnConsole.Y < 21)
		{
			DrawPlayer(jucator, false);
			jucator->_PositionOnConsole.Y++;
			DrawPlayer(jucator, true);
		}
	if (GetAsyncKeyState(VK_UP))
		if (jucator->_PositionOnConsole.Y > 1)
		{
			DrawPlayer(jucator, false);
			jucator->_PositionOnConsole.Y--;
			DrawPlayer(jucator, true);
		}
	ShowCoords(jucator->_PositionOnConsole,jucator);
}
