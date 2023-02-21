#include "map.h"

extern vector<Rabbit> Rabbits;
extern vector<Wolf> Wolves;
extern vector<SheWolf> SheWolves;
extern int fence;

char map[m][m];
float grass[m][m];

void checkN() {
	// m - rozmiar mapy (z ogrodzeniem)
	if (m < 1) {
		cout << "Za maly rozmiar mapy! \n";
		system("pause");
	}
}


void createMap() {
	checkN();

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			if (i == 0)
				map[i][j] = char(177);
			else if (i == m - 1)
				map[i][j] = char(177);
			else if (i == fence && j != 0 && j != m - 1)
				map[i][j] = char(196);
			else if (j == 0)
				map[i][j] = char(177);
			else if (j == m - 1)
				map[i][j] = char(177);
			else
				map[i][j] = ' ';
		}
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			grass[i][j] = 1;
		}
	}
}

void showMap() {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			cout << map[i][j];
		}
		cout << '\n';
	}
}

void play() {
	int i = 1;
	while (true) {
		system("cls");

		// Warunek koñcz¹cy grê
		if (Wolves.size() == 0 && Rabbits.size() == 0 && SheWolves.size() == 0) {
			cout << "Populacja wyginela po: " << i << " ruchach!";
			system("pause");
			break;
		}
		if (Rabbits.size() >= map_area && SheWolves.size() == 0 && Wolves.size() == 0) {
			cout << "Kroliki przejely wyspe! ";
			system("pause");
			break;
		}
		else if (fence != (m - 1) && Rabbits.size() >= (map_area - 20) && SheWolves.size() == 0 && Wolves.size() == 0) {
			cout << "Kroliki przejely wyspe! ";
			system("pause");
			break;
		}
		if (SheWolves.size() + Wolves.size() >= map_area) {
			cout << "Wyspa zapelniona! ";
			system("pause");
			break;
		}

		showMap();

		cout << "Liczba krolikow = ";
		cout << Rabbits.size() << endl;;

		cout << "Liczba wilkow = ";
		cout << Wolves.size() << endl;;

		cout << "Liczba wilczyc = ";
		cout << SheWolves.size() << endl;;

		// Ruch wilczyc
		for (int j = 0; j < SheWolves.size(); j++) {
			SheWolves[j].move();
		}
		// Ruch wilków
		for (int j = 0; j < Wolves.size(); j++) {
			Wolves[j].move();
		}
		// Usuwanie królików, które zjad³y wilki wczeœniej
		for (int j = 0; j < Rabbits.size(); j++) {
			Rabbits[j].dieRabbit();
		}
		// Ruch królików
		for (int j = 0; j < Rabbits.size(); j++) {
			Rabbits[j].move();
		}
		// Trawa roœnie
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < m; j++) {
				grass[i][j] += 0.1;
			}
		}

		Sleep(50);
		i += 1;
	}
}
