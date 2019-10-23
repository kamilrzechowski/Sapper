#include "stdafx.h"
#include "time.h"
#include "iostream"
#include "string"
#include "conio.h"
#include <stdio.h>
#include "cstdlib"
#include "fstream"
#include "Shlwapi.h"
#include <vector>
#include <windows.h>
#include <chrono>
#include <thread>
#include "gameEngine.h"
#include "saveFragment.h"

using namespace std;

/*struct mySweeper{
int liczbaMinWOkolicy;
bool czyMina, zakryte, czyMinaOznaczona;
mySweeper();
};

mySweeper::mySweeper(){
czyMina = false;
zakryte = true;
czyMinaOznaczona = false;
liczbaMinWOkolicy = 0;
}*/

mySave::mySave(){
	next = NULL;
}

myStatistics::myStatistics(){
	next = NULL;
}

bool mySave(mySweeper **tab, int x, int y){
	string save;
	cout << "Enter the name of the file in which you want to save your progress: \n";
	cin >> save;
	bool udanyZapis = false;

	ofstream saveFile((".//Saves//" + save + ".txt").c_str());	// ((".//Saves//" + save + ".txt").c_str(), ios_base::app)
	if (!saveFile.good())
		return udanyZapis;
	if (saveFile.is_open()){
		saveFile << x << " " << y;
		for (int i = 0; i < x; i++){
			saveFile << endl;
			for (int j = 0; j < y; j++){
				saveFile << tab[i][j].liczbaMinWOkolicy << " " << tab[i][j].czyMina << " " <<
					tab[i][j].czyMinaOznaczona << " " << tab[i][j].zakryte << " ";
			}
		}
		udanyZapis = true;
	}
	saveFile.close();
	return udanyZapis;
}

void load(){
	HANDLE hFind;
	WIN32_FIND_DATA data;
	hFind = FindFirstFile(_T(".\\Saves\\*.txt"), &data);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			#ifdef UNICODE
			std::vector<char> buffer;
			int size = WideCharToMultiByte(CP_UTF8, 0, data.cFileName, -1, NULL, 0, NULL, NULL);
			if (size > 0) {
				buffer.resize(size);
				WideCharToMultiByte(CP_UTF8, 0, data.cFileName, -1, (LPSTR)(&buffer[0]), buffer.size(), NULL, NULL);
			}
			else {
				// error handling
			}
			cout << string(&buffer[0])<<endl;
			#else
			cout<<data.cFileName;
			#endif
		} while (FindNextFile(hFind, &data));
		FindClose(hFind);
	}


	/*string save = "ja";
	char buffer_1[] = ("Saves/" + save + ".txt").c_str();
	char *lpStr1;
	lpStr1 = buffer_1;
	PathFindFileName(lpStr1);*/
	/*vector<string> vfList;
	vfList.push_back("file1.txt");
	vfList.push_back("file2.txt");
	// keep pushing file names as long as you want

	vector<string>::iterator itr;
	for (itr = vfList.begin(); itr != vfList.end(); itr++)
	{
		// Do actions with each file.
		// Use itr->c_str() to get the string buffer
		// or *itr to get the actual C++ string object.
		itr->c_str();
	}*/
}

void loadFile(mySweeper **&tab, myTabSize &tabSize){
	string load;
	int OX = 0, OY = 0, dane, i = 0, j = 0;
	printf("\nPodaj nazwe gry do wczytania (bez .txt): ");
	cin >> load;

	ifstream laodF((".//Saves//" + load + ".txt").c_str());
	if (!laodF.good()){
		printf("\nTaki plik nie istnieje");
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		return;
	}
	if (laodF.is_open()){
		laodF >> OX >> OY;
		deleteTab(tab, tabSize.xSize);
		tabSize.xSize = OX;
		tabSize.ySize = OX;
		creatTab(tab, OX);
		int licznik = 0;
		while (licznik<(OX*OY)){
			licznik++;
			laodF >> dane;
			tab[i][j].liczbaMinWOkolicy = dane;
			laodF >> dane;
			tab[i][j].czyMina = (dane == 0) ? false : true;
			laodF >> dane;
			tab[i][j].czyMinaOznaczona = (dane == 0) ? false : true;
			laodF >> dane;
			tab[i][j].zakryte = (dane == 0) ? false : true;
			i++;
			if (i == OX){
				i = 0;
				j++;
			}
		}
	}

	printf("\n\nGra pomyslnie wczytana.");
	laodF.close();
}

int listSize(myStatistics *elem1)
{
	int n = 1;
	if (elem1 == NULL){
		return 0;
	}
	else{
		while (elem1->next != NULL){
			elem1 = elem1->next;
			n++;
		}
	}

	return n;
}

void sortList(myStatistics *&korzen)
{
	myStatistics *elem1 = korzen;
	myStatistics *elem3 = NULL;
	if (korzen == NULL)
		return;
	int n = listSize(korzen);
	do{
		elem1 = korzen;
		for (int i = 0; i < n - 1; i++){
			myStatistics *elem2 = elem1;
			if (elem2->punkty < elem1->next->punkty){
				if (elem2 == korzen){
					korzen = korzen->next;
					elem2->next = korzen->next;
					korzen->next = elem2;
				}
				else if (elem1->next->next == NULL){
					elem3->next = elem2->next;
					elem3->next->next = elem2;
					elem2->next = 0;
					elem1 = elem3->next;
				}
				else{
					elem3->next = elem2->next;
					elem2->next = elem3->next->next;
					elem3->next->next = elem2;
					elem1 = elem3->next;
				}
			}
			elem3 = elem1;
			elem1 = elem1->next;
		}
		n--;
	} while (n > 1);
}


myStatistics* addElem(myStatistics *&korzen, string name, string surname, int ilePunktow)
{
	myStatistics *elem1 = korzen;
	if (korzen == NULL){
		korzen = new myStatistics;
		elem1 = korzen;
	}
	else{
		while (elem1->next != NULL){
			elem1 = elem1->next;
		}
		elem1->next = new myStatistics;
		elem1 = elem1->next;
	}
	elem1->playerName = name;
	elem1->playerSurename = surname;
	elem1->punkty = ilePunktow;

	return elem1;
}

void clearList(myStatistics *&korzen)
{
	if (korzen != NULL){
		myStatistics *elem1 = korzen->next;
		while (elem1 != NULL){
			myStatistics *elem2 = elem1;
			elem1 = elem1->next;
			delete elem2;
		}
		korzen = NULL;
	}
}

void loadStats(myStatistics *&korzen){
	int ilePunktow = 0;
	string imie, nazwisko; 
	myStatistics *elem1 = korzen;
	ifstream laodStatistics(((string)(".//Statistics//Statystyki.txt")).c_str());

	if (!laodStatistics.good()){
		return;
	}
	if (laodStatistics.is_open()){
		clearList(korzen);
		while (laodStatistics >> imie >> nazwisko >> ilePunktow){
			addElem(korzen, imie, nazwisko, ilePunktow);
		}
		sortList(korzen);
	}

	laodStatistics.close();
}

void showStats(myStatistics *elem1){
	int i = 0;

	/*if (elem1 != NULL){
		i++;
		printf("\n");
		cout << i << ". " << elem1->playerName << " " << elem1->playerSurename << " - " << elem1->punkty << "p";
		printf("\n");
	}
	while (elem1->next != NULL){
		i++;
		cout << i << ". " << elem1->playerName << " " << elem1->playerSurename << " - " << elem1->punkty << "p";
		printf("\n");
		elem1 = elem1->next;
	}*/
	if (elem1 != NULL){
		do{
			i++;
			cout << i << ". " << elem1->playerName << " " << elem1->playerSurename << " - " << elem1->punkty << "p";
			printf("\n");
			elem1 = elem1->next;
		} while (elem1 != NULL);
	}
}

void deleteList(myStatistics *&korzen)
{
	while (korzen != NULL){
		myStatistics *elem2 = korzen;
		korzen = korzen->next;
		delete elem2;
	}
}

int sprawdzMiejsceWRankingu(myStatistics *korzen, int wynik){
	int miejsce = 11, i =1;
	myStatistics *elem1 = korzen;

	while (wynik < elem1->punkty && elem1->next != NULL){
		elem1 = elem1->next;
		i++;
	}
	if (wynik > elem1->punkty || i <11){
		miejsce = i;
	}

	return miejsce;
}

bool saveStats(myStatistics *korzen, int miejsceWRankingu, int punkty){
	string imie, nazwisko;
	cout << "Podaj nazwê gracza:";
	cin >> imie;
	cout << "Podaj przydomek gracza:";
	cin >> nazwisko;
	bool udanyZapis = false;
	myStatistics *elem1 = korzen;

	if (korzen != NULL){
		int i = 1;
		while (miejsceWRankingu != i || elem1->next != NULL){
			i++;
			elem1 = elem1->next;
		}
		elem1->playerName = imie;
		elem1->playerSurename = nazwisko;
		elem1->punkty = punkty;
	}

	ofstream saveStats(((string)(".//Statistics//Statystyki.txt")).c_str());
	if (!saveStats.good())
		return udanyZapis;
	if (saveStats.is_open()){
		elem1 = korzen;
		if (korzen != NULL){
			while (elem1->next != NULL){
				saveStats << elem1->playerName << " " << elem1->playerSurename << " " << elem1->punkty << endl;
				elem1 = elem1->next;
			}
			saveStats << elem1->playerName << " " << elem1->playerSurename << " " << elem1->punkty << endl;
		}

		udanyZapis = true;
	}
	saveStats.close();
	return udanyZapis;
}



/*bool mySave(mySweeper **tab, int x, int y){
	string save;
	cout << "Enter the name of the file in which you want to save your progress: \n";
	cin >> save;
	bool udanyZapis = false;

	ofstream saveFile((".//Saves//" + save + ".txt").c_str(), ios_base::app);
	if (!saveFile.good())
		return udanyZapis;
	if (saveFile.is_open()){
		saveFile << endl << save;
		for (int i = 0; i < x; i++){
			saveFile << endl;
			for (int j = 0; j < y; j++){
				saveFile << tab[i][j].liczbaMinWOkolicy << " " << tab[i][j].czyMina << " " <<
					tab[i][j].czyMinaOznaczona << " " << tab[i][j].zakryte;
			}
		}
		saveFile << "*" << endl;
		udanyZapis = true;
	}
	saveFile.close();
	return udanyZapis;
	}*/