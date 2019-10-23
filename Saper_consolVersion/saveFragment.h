using namespace std;

#ifndef SAVE_FRAGMENT
	#define SAVE_FRAGMENT
	
	struct mySave{
		mySave *next;
		string saveName;
		mySweeper **tab;
		mySave();
	};

	struct myStatistics{
		myStatistics *next;
		string playerName;
		string playerSurename;
		int punkty;
		myStatistics();
	};

	bool mySave(mySweeper **tab, int x, int y);
	
	void load();

	void loadFile(mySweeper **&tab, myTabSize &tabSize);

	void deleteTab(mySweeper **&tab, int x);

	void loadStats(myStatistics *&korzen);

	void showStats(myStatistics *elem1);

	void deleteList(myStatistics *&korzen);

	int sprawdzMiejsceWRankingu(myStatistics *korzen, int wynik);

	bool saveStats(myStatistics *korzen, int miejsceWRankingu, int punkty);

#endif