#include <iostream>
#include <cmath>
#include "map.h"
using namespace std;

vector<Rabbit> Rabbits;
vector<Wolf> Wolves;
vector<SheWolf> SheWolves;
int fence;

void main() {
	srand(time(NULL));
	
	bool isFence = false;
	while (isFence == false) {
		cout << "Pozycja ogrodzenia: (1 -  "; cout << n << ") (jesli brak to wpisz " << n + 1 << "): ";
		cin >> fence;
		if (fence > 0 && fence <= n)
			isFence = true;
		else if (fence == n + 1) {
			break;
		}
		system("cls");
	}

	createMap();
	showMap();

	int r, w, s;

	cout << "Wpisz ilosc krolikow = "; cin >> r;
	cout << "Wpisz ilosc wilkow = "; cin >> w;
	cout << "Wpisz ilosc wilczyc = "; cin >> s;

	if (r < 0 || w < 0 || s < 0) {
		cout << "Liczba zwierzakow musi byc dodatnia! \n";
		system("pause");
	}
	else if (r + w + s > map_area) {
		cout << "Liczba zwierzakow musi wynosic maksymalnie " << map_area << "! \n";
		system("pause");
	}
	else if (isFence == true && w + s > (fence-1) * n) {
		cout << "Liczba wilkow i wilczyc musi wynosic maksymalnie " << (fence - 1) * n << "! \n";
		system("pause");
	}
	else if (isFence == true && r > (n - fence) * n) {
		cout << "Liczba krolikow musi wynosic maksymalnie " << (n - fence) * n << "! \n";
		system("pause");
	}

	else {
		for (int i = 0; i < r; i++) {
			Rabbit rabbit;
			Rabbits.push_back(rabbit);
		}
		for (int i = 0; i < w; i++) {
			Wolf wolf;
			Wolves.push_back(wolf);
		}
		for (int i = 0; i < s; i++) {
			SheWolf shewolf;
			SheWolves.push_back(shewolf);
		}
	}

	play();

};