#include <iostream>
#include "AStar.h"
#include <windows.h>

void ShowMap(vector<vector<int>>map);

int main()
{ 
	vector<vector<int>> map{
		vector<int> {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5},
		vector<int> {5,2,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,5},
		vector<int> {5,1,0,0,1,0,1,0,1,0,0,1,0,0,0,0,0,1,0,1,1,5},
		vector<int> {5,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,5},
		vector<int> {5,0,1,1,1,0,0,1,0,1,0,1,0,1,1,0,1,1,0,0,0,5},
		vector<int> {5,1,0,0,1,0,0,1,0,1,0,1,1,1,1,0,1,0,0,1,3,5},
		vector<int> {5,1,1,1,1,0,1,1,1,1,1,1,0,0,1,0,1,1,1,1,0,5},
		vector<int> {5,1,0,0,1,0,1,0,0,1,0,1,1,1,1,0,1,0,0,1,0,5},
		vector<int> {5,0,1,1,1,0,1,1,1,1,0,1,0,0,1,1,1,1,1,1,0,5},
		vector<int> {5,1,1,0,0,0,0,0,1,1,1,1,0,1,1,1,0,0,0,1,0,5},
		vector<int> {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5},
	};

	vector<int> noStep{0,5};

	AStar p;
	vector<Node> a = p.Search(map, noStep, vector<int>{1, 1}, 3);

	for (int i = 1; i < a.size()-1; ++i)
		map[a[i].y][a[i].x] = 8;

	ShowMap(map);
}

void ShowMap(vector<vector<int>>map) {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 7);

	for (int i = 0; i < map.size(); ++i) {
		for (int j = 0; j < map[i].size(); ++j) {
			switch (map[i][j]) {
			case 0: { SetConsoleTextAttribute(hConsole, 1);   cout << " "; }break;
			case 1: { SetConsoleTextAttribute(hConsole, 112); cout << " "; }break;
			case 2: { SetConsoleTextAttribute(hConsole, 64);  cout << " "; }break;
			case 3: { SetConsoleTextAttribute(hConsole, 32);  cout << " "; }break;
			case 5: { SetConsoleTextAttribute(hConsole, 16);  cout << " "; }break;
			case 8: { SetConsoleTextAttribute(hConsole, 112); cout << "+"; }break;
			}
		
			SetConsoleTextAttribute(hConsole, 7);
		}
		cout << endl;
	}
}