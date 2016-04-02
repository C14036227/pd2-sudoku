#include<iostream>
#include<cstdlib>
#include<string>
using namespace std;

class Sudoku{
	public:
		Sudoku();
		//Sudoku(const int init_map[]);
		int checkSol();
		void giveQuestion();
		void readIn();
		void solve();
		void changeNum(int a, int b);
		void changeRow(int a, int b);
		void changeCol(int a, int b);
		void rotate(int n);
		void flip(int n);
		void transform();
		bool prejudge();
		bool preCheck(int posib[][9], int row[][9], int col[][9], int square[][9]);
		const static int SudokuSize = 81;
	private:
		int solmap[SudokuSize];
		int ANS[SudokuSize];
		void printout();
		int map[SudokuSize];
		void transpose();
		int element2;
		int indrow,indcol;
		int candiSol;
		bool checknoSol(int posib[][9],int row[][9], int col[][9], int square[][9]);
		bool invalid(int row[][9], int col[][9], int square[][9]);
		//int posib[81][9];
		//int row[9][9];
		//int col[9][9];
		//int square[9][9];
		void checker(int posib[][9], int row[][9], int col[][9], int square[][9]);
		void backtrace(int posib[][9],int row[][9],int col[][9],int square[][9],int scan);		






};
