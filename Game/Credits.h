#pragma once
#include <iostream>

void GameOver()
{
	system("CLS");
	HANDLE hOutPut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOutPut, 12);
	SetConsoleCursorPosition(hOutPut, { 80 / 2 - sizeof("Game over!") / 2, 12 });
	std::cout << "Game over!\n";
	SetConsoleCursorPosition(hOutPut, { 80 / 2 - sizeof("Press any key to continue . . .") / 2, 13 });
	system("PAUSE");
}

void PutUpdatesOnScreen()
{
	HANDLE hOutPut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOutPut, 11 | BACKGROUND_RED);
	SetConsoleCursorPosition(hOutPut, { (79 / 2) - (sizeof("~~~~~~~~~~~~~Updates~~~~~~~~~~~~~") / 2), 5 });
	std::cout << "~~~~~~~~~~~~~Updates~~~~~~~~~~~~~";
	SetConsoleCursorPosition(hOutPut, { (79 / 2) - (sizeof("Update 0.1 - Alfa version") / 2), 6 });
	std::cout << "Update 0.1 - Alfa version\n";
	SetConsoleTextAttribute(hOutPut, 10);
	std::cout << "\t- A fost creeat motorul jocului - Line Dash\n"
		<< "\t- A fost adaugat un meniu, meniul contine:\n"
		<< "\t\t\t- Start Game\n"
		<< "\t\t\t- Credits\n"
		<< "\t\t\t- Exit\n";
	SetConsoleTextAttribute(hOutPut, 11 | BACKGROUND_RED);
	SetConsoleCursorPosition(hOutPut, { (79 / 2) - (sizeof("Update 0.2 - Alfa version") / 2), 12 });
	std::cout << "Update 0.2 - Alfa version\n";
	SetConsoleTextAttribute(hOutPut, 10);
	std::cout << "\t- A fost modificast meniul:\n"
		<< "\t\t\t- acum veti putea sa selectati cu mouse-ul\n"
		<< "\t\t\t- veti putea alege cu click stanga\n"
		<< "\t- Sectiunii \"Credits\" a fost adaugat \"Updates\"\n"
		<< "\t- Au fost adaugate cateva culori jocului\n"
		<< "\t- Codul a fost putin optimizat\n";
	SetConsoleTextAttribute(hOutPut, 11 | BACKGROUND_RED);
	SetConsoleCursorPosition(hOutPut, { (79 / 2) - (sizeof("Update 0.2 - Alfa version") / 2), 19 });
	std::cout << "Update 0.3 - Beta version\n";
	SetConsoleTextAttribute(hOutPut, 10);
	std::cout << "\t- A fost adaugat un ecran pentru fiecare data cand pierzi\n"
		<< "\t- Au fost rezolvate majoritatea bugurilor\n"
		<< "\t- A fost refacut submeniul \"Options\""
		<< "\t- A fost rezolvat un bug major\n"
		<< "\t- A fost adaugat un sunet de fundal\n"
		<< "\t- A fost adaugata o noua optiune meniului: \"Options\"";
	//Adaug playlist
}

void PutCreditsOnScreen()
{ 
	system("CLS");
	std::cout << "Application developed on 02.09.2015 by \"cDorsu\".\n\n\t\t\tCode has about 820 lines of code.";
}