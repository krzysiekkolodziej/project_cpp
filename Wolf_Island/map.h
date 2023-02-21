#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "animal.h"
using namespace std;

const int n = 20;			// rozmiar mapy (bez ogrodzenia)
const int m = n + 2;		// rozmiar mapy (z ogrodzeniem)
const int map_area = n * n;	// pole mapy bez ogrodzenia
extern char map[m][m];		// tablica mapy
extern float grass[m][m];	// tablica trawy
void createMap();
void showMap();
void play();