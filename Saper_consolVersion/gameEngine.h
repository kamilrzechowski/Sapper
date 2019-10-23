using namespace std;

#ifndef GAME_ENGINE
	#define GAME_ENGINE

	struct mySweeper{
		int liczbaMinWOkolicy;
		bool czyMina, zakryte, czyMinaOznaczona;
		mySweeper();
	};

	struct myTabSize{
		int xSize, ySize;
	};

	myTabSize creatTab(mySweeper **&tab, int rozmiar);

	int losuj(int zakres_pocz, int zakres_kon);

	int ileMinDoOkola(mySweeper **tab, int xWidth, int yHeight, int x, int y);

	void odslonPola(mySweeper **tab, int xWidth, int yHeight, int x, int y, bool odkrytoLiczbe);

	void fillTab(mySweeper **tab, int x, int y);

	bool sprawdzWynik(mySweeper **tab, int x, int y);

	void reset(mySweeper **&tab, int x, int y);

	int obliczWynik(int x, int y, int ileBomb);

#endif