#include "stdafx.h"
#include "time.h"
#include "iostream"
#include "string"
#include "conio.h"
#include <stdio.h>
#include "cstdlib"
#include "windows.h"
#include "gameEngine.h"
#include <cassert>

using namespace std;

mySweeper::mySweeper(){
	czyMina = false;
	zakryte = true;
	czyMinaOznaczona = false;
	liczbaMinWOkolicy = 0;
}

/*struct mySave{
mySave *next;
string saveName;
mySweeper **tab;
mySave();
};

mySave::mySave(){
next = NULL;
}*/
//=============================================================

myTabSize creatTab(mySweeper **&tab, int rozmiar){
	myTabSize XY;

	tab = new mySweeper*[rozmiar];
	for (int i = 0; i < rozmiar; i++){
		tab[i] = new mySweeper[rozmiar];
	}
	XY.xSize = rozmiar;
	XY.ySize = rozmiar;

	/*switch (poziomTrudnosci){
	case 1:
	XY.xSize = XY.ySize = 10;
	tab = new mySweeper*[10];
	for (int i = 0; i < 10; i++){
	tab[i] = new mySweeper[10];
	}
	break;
	case 2:
	XY.xSize = XY.ySize = 20;
	tab = new mySweeper*[20];
	for (int i = 0; i < 20; i++){
	tab[i] = new mySweeper[20];
	}
	break;
	case 3:
	XY.xSize = XY.ySize = 30;
	tab = new mySweeper*[30];
	for (int i = 0; i < 30; i++){
	tab[i] = new mySweeper[30];
	}
	break;

	default:
	break;
	}*/

	return XY;
}

int losuj(int zakres_pocz, int zakres_kon){
	return zakres_pocz + rand() % (zakres_kon - zakres_pocz);
}

int ileMinDoOkola(mySweeper **tab, int xWidth, int yHeight, int x, int y){
	int ileMin = 0;
	for (int i = x - 1; i <= x + 1; i++){
		for (int j = y - 1; j <= y + 1; j++){
			if (!(i == x && j == y)){
				if (i >= 0 && i < xWidth && j >= 0 && j < yHeight){
					if (tab[i][j].czyMina)
						ileMin++;
				}
			}
		}
	}

	return ileMin;
}

void odslonPola(mySweeper **tab, int xWidth, int yHeight, int x, int y, bool odkrytoLiczbe){
	if (x >= 0 && x<xWidth && y >= 0 && y<yHeight && !odkrytoLiczbe){
		if (tab[x][y].zakryte){
			tab[x][y].zakryte = false;
			if (tab[x][y].liczbaMinWOkolicy > 0)
				odkrytoLiczbe = true;
			odslonPola(tab, xWidth, yHeight, x, y - 1, odkrytoLiczbe);
			odslonPola(tab, xWidth, yHeight, x, y + 1, odkrytoLiczbe);
			odslonPola(tab, xWidth, yHeight, x - 1, y, odkrytoLiczbe);
			odslonPola(tab, xWidth, yHeight, x + 1, y, odkrytoLiczbe);

			odslonPola(tab, xWidth, yHeight, x-1, y - 1, odkrytoLiczbe);
			odslonPola(tab, xWidth, yHeight, x+1, y + 1, odkrytoLiczbe);
			odslonPola(tab, xWidth, yHeight, x - 1, y+1, odkrytoLiczbe);
			odslonPola(tab, xWidth, yHeight, x + 1, y-1, odkrytoLiczbe);
		}
	}
}

void fillTab(mySweeper **tab, int x, int y){
	int liczbaBomb = (int)((x*y) / 10);
	int xTab, yTab;
	int poleNumer;

	for (int i = 0; i < liczbaBomb; i++){
		xTab = losuj(0, x);
		yTab = losuj(0, y);
		poleNumer = losuj(0, y*x - i);

		int wiersz = 0, kolumna = 0, licznik = 0;
		while (licznik<poleNumer){
			if (kolumna == y){
				kolumna = 0;
				wiersz++;
			}
			if (!tab[wiersz][kolumna].czyMina){
				licznik++;
			}
			kolumna++;
		}
		kolumna--;
		tab[wiersz][kolumna].czyMina = true;

		/*if (tab[xTab][yTab].czyMina){
		//i--;
		bool minaWstawiona = false;
		for (int i = 0; i < x; i++){
		for (int j = 0; j < y; j++){
		if (!tab[i][j].czyMina && !minaWstawiona){
		tab[i][j].czyMina = true;
		minaWstawiona = true;
		}
		}
		}
		}
		else{
		tab[xTab][yTab].czyMina = true;
		}*/
	}

	for (int i = 0; i < x; i++){
		for (int j = 0; j < y; j++){
			tab[i][j].liczbaMinWOkolicy = ileMinDoOkola(tab, x, y, i, j);
		}
	}
}

bool sprawdzWynik(mySweeper **tab, int x, int y){
	bool wygrana = true;
	for (int i = 0; i < x; i++){
		for (int j = 0; j < y; j++){
			if (tab[i][j].zakryte)
				wygrana = false;
			if (!tab[i][j].czyMina && tab[i][j].czyMinaOznaczona){
				wygrana = false;
			}
		}
	}

	return wygrana;
}

void reset(mySweeper **&tab, int x, int y){
	for (int i = 0; i < x; i++){
		for (int j = 0; j < y; j++){
			tab[i][j].zakryte = true;
			tab[i][j].czyMina = false;
			tab[i][j].czyMinaOznaczona = false;
			tab[i][j].liczbaMinWOkolicy = 0;
		}
	}
	fillTab(tab, x, y);
}

int obliczWynik(int x, int y, int ileBomb){
	int wynik = (int)(((double)ileBomb / (x*y))*1000);

	return wynik;
}