#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>
#include <windows.h>
#include "map.h"
using namespace std;

class Animal{
protected:
	double fat = 1;
public:
	int posX{};
	int posY{};
	int getPosX() const;
	int getPosY() const;
	void setPos(int x, int y, char n);
	void setFat(double f);
	bool isEndOfMap(int x, int y) const;
	bool isMapFull() const;

	void addFat();
};

class Rabbit : public Animal {
public:
	Rabbit();
	void move();
	void dieRabbit();
	void doReproduction(int x, int y);
};

class Wolf : public Animal {
public:
	Wolf();
	int closeRabbitPos() const;
	void doReproduction(int x, int y);
	void move();
	void dieWolf();

	void subFat();
};

class SheWolf : public Animal {
public:
	SheWolf();
	int closeRabbitPos() const;
	void move();
	void dieSheWolf();

	void subFat();
};
