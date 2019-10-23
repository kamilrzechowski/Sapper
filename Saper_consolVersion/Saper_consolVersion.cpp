// Saper_consolVersion.cpp : Defines the entry point for the console application.
//
/*#ifndef ttt 
#define ttt
#endif*/

#include "stdafx.h"
#include "time.h"
#include "iostream"
#include "string"
#include "conio.h"
#include "stdio.h"
#include "cstdlib"
#include "windows.h"
#include "gameEngine.h"
#include "saveFragment.h"

using namespace std;

const int polozenieTabX = 30, polozenieTabY = 6;
int sizeOfTab = 0;

void gotoxy(int x, int y){

	COORD c;

	c.X = x - 1;

	c.Y = y - 1;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

}

void meniu()
{
	system("cls");			//czyœci ekran     
	system("Color 2A");		//pierwsza liczba t³o(b), druga pisak(c)
	gotoxy(1, 1);
	printf("F1-Nowa gra %c F2-Statystyki %c F3-Dodajwynik %c F4-Sprawdz wynik %c ESC-koniec", 179, 179, 179, 179);
	gotoxy(1, 2);
	printf("F5-Save game %c F6-Wczytaj gre", 179);
}
//========================================================
void printTab(mySweeper **tab, int x, int y){
	for (int i = 0; i < x; i++){
		for (int j = 0; j < y; j++){
			if (tab[i][j].czyMina){
				cout << "M" << " ";
			}
			else{
				cout << tab[i][j].liczbaMinWOkolicy << " ";
			}
		}
		cout << endl;
	}
}

void printTab2(mySweeper **tab, int x, int y){
	const unsigned char c = 219;
	int polozenieX = polozenieTabX, polozenieY = polozenieTabY;
	//cout << "   ";
	/*for (int i = 0; i < x; i++){
		if (i>9 && i % 2 == 0){
			gotoxy(polozenieX + 3 + i, polozenieY - 3);
		}
		else if (i > 9){
			gotoxy(polozenieX + 3 + i, polozenieY - 2);
		}
		else{
			gotoxy(polozenieX + 3 + i, polozenieY - 1);
		}
		cout << i + 1;
	}*/
	for (int i = 0; i < x; i++){
		if (i < 9){
			gotoxy(polozenieX + 3 + i, polozenieY - 1);
			cout << i + 1;
		}
		else{
			gotoxy(polozenieX + 3 + i, polozenieY - 2);
			cout << (int)((i + 1) / 10);
			gotoxy(polozenieX + 3 + i, polozenieY - 1);
			cout << (i + 1)%10;
		}
	}
	//printf("\n");
	gotoxy(polozenieX, polozenieY);
	for (int i = 0; i < x; i++){
		cout << i + 1 << ".";
		if (i < 9)
			cout << " ";
		for (int j = 0; j < y; j++){
			if (tab[i][j].zakryte){
				cout << c;
			}
			else if (tab[i][j].czyMinaOznaczona == true){
				cout << "B";
			}
			else if (tab[i][j].liczbaMinWOkolicy == 0){
				cout << " ";
			}
			else{
				cout << tab[i][j].liczbaMinWOkolicy;
			}
			//cout << " ";
		}
		//cout << endl;
		gotoxy(polozenieX, polozenieY + i + 1);
	}
}

void wyrysuj(mySweeper **tab, int x, int y){
	meniu();
	gotoxy(1, 3);
	//printTab(tab, x, y);
	printTab2(tab, x, y);
}

void getstrzal(mySweeper **tab, int xWidth, int yHeight){
	int x = -1, y = -1;
	int polozenieX = 1, polozenieY = polozenieTabY + xWidth + 2;
	char znak = 'a';
	gotoxy(polozenieX, polozenieY);
	do{
		cout << "Podaj wspolrzedne z zakresu 1-" << xWidth << "  i m - minna p - pustepole: " << endl;
		printf("\n\n");
		cout << "wiersz: ";
		cin >> x;
		cin.clear();
		cin.sync();
		cout << "kolumna: ";
		cin >> y;
		cin.clear();
		cin.sync();
		cout << "mina(m)/puste pole(p): ";
		cin >> znak;
		cin.clear();
		cin.sync();
	} while (!(x > 0 && x < xWidth + 1) || !(y>0 && y < yHeight + 1) || (znak != 'm' && znak != 'p'));

	if (znak == 'p'){
		x--;
		y--;
		if (tab[x][y].czyMina){
			system("Color 4B");
			printf("\n\nKoniec gry. Przegrales");

		}
		else if (!tab[x][y].zakryte){
			if (tab[x][y].czyMinaOznaczona){
				tab[x][y].czyMinaOznaczona = false;
				wyrysuj(tab, xWidth, yHeight);
			}
			else{
				system("cls");
				wyrysuj(tab, xWidth, yHeight);
				gotoxy(polozenieX, polozenieY + 2);
				cout << "to pole jest odkryte";
				getstrzal(tab, xWidth, yHeight);
				printf("\n\n");
			}
		}
		else{
			//tab[x][y].zakryte = false;
			odslonPola(tab, xWidth, yHeight, x, y, false);
			wyrysuj(tab, xWidth, yHeight);
		}
	}
	else{	//jak mina
		x--;
		y--;
		tab[x][y].czyMinaOznaczona = true;
		tab[x][y].zakryte = false;
		wyrysuj(tab, xWidth, yHeight);
	}
}

void deleteTab(mySweeper **&tab, int x){
	if (tab != NULL){
		for (int i = 0; i < x; i++){
			delete[] tab[i];
		}
		delete[] tab;
		tab = NULL;
	}
}

void myStart(){
	gotoxy(1, 2);
	printf("Wybierz poziom trudnosci: \n\n 1 - Latwy \n 2 - Sredni \n 3 - Trudny");
	int liczba;
	system("Color 2A");
	printf("\n\nPodaj numer poziomu trudnosci: ");
	do{
		cin >> liczba;
		cin.clear();
		cin.sync();
	} while (liczba < 1 || liczba >3);
	
	switch (liczba){
		case 1:
			sizeOfTab = 10;
			break;
		case 2:
			sizeOfTab = 20;
			break;
		case 3:
			sizeOfTab = 30;
			break;

		default:
			break;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	mySweeper **tab;
	myTabSize tabSize;
	myStatistics *korzen = NULL;
	srand((unsigned int)time(NULL));
	myStart();
	tabSize.xSize = sizeOfTab;
	tabSize.ySize = sizeOfTab;
	creatTab(tab,sizeOfTab);
	fillTab(tab, tabSize.xSize, tabSize.ySize);

	int miejsceWRankingu = 0, zdobytePunkty = 0;
	
	wyrysuj(tab, tabSize.xSize, tabSize.ySize);
	char zn = 0;
	while (zn != 27)
	{
		zn = _getch();
		switch (zn)
		{
			case 59:
				//reset(tab, tabSize.xSize, tabSize.ySize);
				//wyrysuj(tab, tabSize.xSize, tabSize.ySize);
				deleteTab(tab, tabSize.xSize);
				system("cls");
				myStart();
				tabSize.xSize = sizeOfTab;
				tabSize.ySize = sizeOfTab;
				creatTab(tab, sizeOfTab);
				fillTab(tab, tabSize.xSize, tabSize.ySize);

				wyrysuj(tab, tabSize.xSize, tabSize.ySize);
				break;
			case 60:
				meniu();
				printf("\n\nStatystyki\n");
				loadStats(korzen);
				showStats(korzen);
				zdobytePunkty = obliczWynik(tabSize.xSize, tabSize.ySize, (int)((tabSize.xSize*tabSize.ySize) / 10));
				printf("\n\nNacisnij F7 aby wrocic.");
				break;
			case 61:
				getstrzal(tab, tabSize.xSize, tabSize.ySize);
				break;
			case 62:
				if (sprawdzWynik(tab, tabSize.xSize, tabSize.ySize)){
					printf("\n\nWygrana!\n");
					zdobytePunkty = obliczWynik(tabSize.xSize, tabSize.ySize, (int)((tabSize.xSize*tabSize.ySize) / 10));
					miejsceWRankingu = sprawdzMiejsceWRankingu(korzen, zdobytePunkty);
					printf("/nZdobyte punkty: %i", zdobytePunkty);
					if (miejsceWRankingu > 10){
						printf("\nMiejsce poza ramkingiem.");
					}
					else{
						saveStats(korzen, miejsceWRankingu, zdobytePunkty);
						showStats(korzen);
					}
					loadStats(korzen);
				}
				break;
			case 63:
				system("cls");
				printf("Podaj nazwe zapisu: \n\n");
				if (mySave(tab, tabSize.xSize, tabSize.ySize)){
					printf("\n\nZapis udany");
				}
				else{
					printf("\n\nNie udalo siê zapisaæ");
				}
				printf("\n\nNacisnij F7 aby wrocic.");
				/*char znak = 0;
				while (znak != 27){
					znak = _getch();
				}*/
				//wyrysuj(tab, tabSize.xSize, tabSize.ySize);
				break;
			case 64:
				system("cls");
				printf("Zapisane gry:\n\n");
				load();
				//printf("\nPodaj nazwe gry do wczytania: ");
				loadFile(tab, tabSize);
				wyrysuj(tab, tabSize.xSize, tabSize.ySize);
				break;
			case 65:
				wyrysuj(tab, tabSize.xSize, tabSize.ySize);
				break;
		}
	}

	deleteTab(tab, tabSize.xSize);
	deleteList(korzen);
	return 0;
}

