#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<cstdio>
#include<ctime>
#include"a.h"

using namespace std;

class Sudoku
{
	public:
		void giveQuestion();
		void readIn();
		void solve();
		void changeNum(int a, int b);
		void changeRow(int a, int b);
		void changeCol(int a, int b);
		void rotate(int n);
		void flip(int n);
		void transform();

	private:
		int map[81];
		void sudu(char a[9][9], element b[9][9], int i, int j);
		void ele(char a[9][9], element b[9][9]);
		int checkRow(char a[9][9], char x, int i);
		int checkColumn(char a[9][9], char x, int j);
		int checkBlock(char a[9][9], char x, int i, int j);
		void change();
		const static int count = 0;
		const static int ans = 0;
};
