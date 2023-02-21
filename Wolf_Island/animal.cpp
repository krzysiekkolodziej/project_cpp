#include "animal.h"

extern vector<Rabbit> Rabbits;
extern vector<Wolf> Wolves;
extern vector<SheWolf> SheWolves;
extern int fence;

int Animal::getPosX() const {
	return posX;
}

int Animal::getPosY() const {
	return posY;
}

void Animal::setPos(int x, int y, char n) {
	// Nowa pozycja zwierzaka
	map[x][y] = n;
	// Aktualna pozycja zwierzaka zostaje polem pustym
	map[posX][posY] = ' ';
	// Zaaktualizuj pozycje zwierzaka
	posX = x;
	posY = y;
}

void Animal::setFat(double f){
	fat = f;
}

bool Animal::isEndOfMap(int x, int y) const{
	if (map[x][y] == char(177)) {
		return true;
	}
	else return false;
}

bool Animal::isMapFull() const{
	if (Rabbits.size() + Wolves.size() + SheWolves.size() > map_area) {
		return true;
	}
	else return false;
}

void Animal::addFat() {
	// Zapelnienie t³uszczu, zwierzê mo¿e mieæ maksymalnie 1 jednostkê t³uszczu
	fat = 1;
}

Rabbit::Rabbit(){
	// m - oznacza rozmiar mapy (bez ogrodzenia)

	posX = rand() % (m - 1) + 1;
	posY = rand() % (m - 1) + 1;
	if (map[posX][posY] == ' ') {
		map[posX][posY] = 'R';
	}
	else {
		while (map[posX][posY] != ' ') {
			posX = rand() % (m - 1) + 1;
			posY = rand() % (m - 1) + 1;
		}
		map[posX][posY] = 'R';
	}
}

void Rabbit::dieRabbit(){
	int x = getPosX();
	int y = getPosY();

	for (int i = 0; i < Rabbits.size(); i++) {
		if (Rabbits[i].getPosX() == x && Rabbits[i].getPosY() == y && map[x][y] != 'R') {
			Rabbits.erase(Rabbits.begin() + i);
		}
	}
	for (int i = 0; i < Rabbits.size(); i++) {
		if (Rabbits[i].getPosX() == x && Rabbits[i].getPosY() == y && map[x][y] == 'R' && grass[x][y] <= 0) {
			Rabbits.erase(Rabbits.begin() + i);
			map[x][y] = ' ';
		}
	}
}

void Rabbit::move() {
	// Wylosuj kierunek
	int d = rand() % 8 + 1;
	// Pobierz aktualna pozycje zwierzaka
	int x = getPosX();
	int y = getPosY();

	if (d == 1 && map[x - 1][y - 1] == ' ') {
		setPos(x - 1, y - 1, 'R');
		doReproduction(x, y);
	}
	else if (d == 2 && map[x - 1][y] == ' ') {
		setPos(x - 1, y, 'R');
		doReproduction(x, y);
	}
	else if (d == 3 && map[x - 1][y + 1] == ' ') {
		setPos(x - 1, y + 1, 'R');
		doReproduction(x, y);
	}
	else if (d == 4 && map[x][y + 1] == ' ') {
		setPos(x, y + 1, 'R');
		doReproduction(x, y);
	}
	else if (d == 5 && map[x + 1][y + 1] == ' ') {
		setPos(x + 1, y + 1, 'R');
		doReproduction(x, y);
	}
	else if (d == 6 && map[x + 1][y] == ' ') {
		setPos(x + 1, y, 'R');
		doReproduction(x, y);
	}
	else if (d == 7 && map[x + 1][y - 1] == ' ') {
		setPos(x + 1, y - 1, 'R');
		doReproduction(x, y);
	}
	else if (d == 8 && map[x][y - 1] == ' ') {
		setPos(x, y - 1, 'R');
		doReproduction(x, y);
	}

	if (d == 1 && map[x - 1][y - 1] == char(196)) {
		if (map[x - 2][y - 2] == ' ') {
			setPos(x - 2, y - 2, 'R');
			doReproduction(x, y);
		}	
	}
	else if (d == 2 && map[x - 1][y] == char(196)) {
		if (map[x - 2][y] == ' ') {
			setPos(x - 2, y, 'R');
			doReproduction(x, y);
		}
	}
	else if (d == 3 && map[x - 1][y + 1] == char(196)) {
		if (map[x - 2][y + 2] == ' ') {
			setPos(x - 2, y + 2, 'R');
			doReproduction(x, y);
		}
	}
	else if (d == 4 && map[x][y + 1] == char(196)) {
		if (map[x][y + 2] == ' ') {
			setPos(x, y + 2, 'R');
			doReproduction(x, y);
		}
	}
	else if (d == 5 && map[x + 1][y + 1] == char(196)) {
		if (map[x + 2][y + 2] == ' '){
			setPos(x + 2, y + 2, 'R');
			doReproduction(x, y);
		}
	}
	else if (d == 6 && map[x + 1][y] == char(196)) {
		if (map[x + 2][y] == ' ') {
			setPos(x + 2, y, 'R');
			doReproduction(x, y);
		}
	}
	else if (d == 7 && map[x + 1][y - 1] == char(196)) {
		if (map[x + 2][y - 2] == ' ') {
			setPos(x + 2, y - 2, 'R');
			doReproduction(x, y);
		}
	}
	else if (d == 8 && map[x][y - 1] == char(196)) {
		if (map[x][y - 2] == ' ') {
			setPos(x, y - 2, 'R');
			doReproduction(x, y);
		}
	}
}

void Rabbit::doReproduction(int x, int y){
	if (isMapFull() == false) {
		int n = rand() % 5 + 1;
		if (n == 1) {
			size_t r = Rabbits.size();
			Rabbits.push_back(Rabbit());
			Rabbits[r].setPos(x, y, 'R');
		}
		else
			// jeœli sie poruszasz to zjadasz trawê
			if (grass[x][y] >= 0.5)
				grass[x][y] -= 0.5;
			// jeœli nie ma trawy to umierasz
			else dieRabbit();
	}
}

Wolf::Wolf() {
	// n - oznacza rozmiar mapy (z ogrodzeniem)
	posX = rand() % (fence - 1) + 1;
	posY = rand() % (m - 1) + 1;
	if (map[posX][posY] == ' ') {
		map[posX][posY] = 'W';
	}
	else {
		while (map[posX][posY] != ' ') {
			posX = rand() % (fence - 1) + 1;
			posY = rand() % (m - 1) + 1;
		}
		map[posX][posY] = 'W';
	}
}

void Wolf::dieWolf(){
	int x = getPosX();
	int y = getPosY();

	for (int i = 0; i < Wolves.size(); i++) {
		if (Wolves[i].getPosX() == x && Wolves[i].getPosY() == y) {
			Wolves.erase(Wolves.begin() + i);
			map[x][y] = ' ';
		}
	}
}

int Wolf::closeRabbitPos() const{
	int x = getPosX();
	int y = getPosY();

	if (map[x - 1][y - 1] == 'R') return 1;
	else if (map[x - 1][y] == 'R') return 2;
	else if (map[x - 1][y + 1] == 'R') return 3;
	else if (map[x][y + 1] == 'R') return 4;
	else if (map[x + 1][y + 1] == 'R') return 5;
	else if (map[x + 1][y] == 'R') return 6;
	else if (map[x + 1][y - 1] == 'R') return 7;
	else if (map[x][y - 1] == 'R') return 8;
	else return 0;
}

void Wolf::doReproduction(int x, int y){
	size_t w = Wolves.size();
	size_t s = SheWolves.size();
	
	// Rozmnazaj sie tylko, jak nie jestes wyg³odzony i mapa nie jest pe³na
	if (isMapFull() == false && fat > 0.5) {
		int n = rand() % 2 + 1;
		if (n == 1) {
			if (map[x - 1][y - 1] == ' ') {
				// Dodaj potomka do wektora obiektów
				Wolves.push_back(Wolf());
				// Potomek ma mniej t³uszczu od rodzica
				Wolves[w].setFat(0.5);
				// Przenosi go na puste pole w poblizu rodzica
				Wolves[w].setPos(x - 1, y - 1, 'W');
			}
			else if (map[x - 1][y] == ' ') {
				Wolves.push_back(Wolf());
				Wolves[w].setFat(0.5);
				Wolves[w].setPos(x - 1, y, 'W');
			}
			else if (map[x - 1][y + 1] == ' ') {
				Wolves.push_back(Wolf());
				Wolves[w].setFat(0.5);
				Wolves[w].setPos(x - 1, y + 1, 'W');
			}
			else if (map[x][y + 1] == ' ') {
				Wolves.push_back(Wolf());
				Wolves[w].setFat(0.5);
				Wolves[w].setPos(x, y + 1, 'W');
			}
			else if (map[x + 1][y + 1] == ' ') {
				Wolves.push_back(Wolf());
				Wolves[w].setFat(0.5);
				Wolves[w].setPos(x + 1, y + 1, 'W');
			}
			else if (map[x + 1][y] == ' ') {
				Wolves.push_back(Wolf());
				Wolves[w].setFat(0.5);
				Wolves[w].setPos(x + 1, y, 'W');
			}
			else if (map[x + 1][y - 1] == ' ') {
				Wolves.push_back(Wolf());
				Wolves[w].setFat(0.5);
				Wolves[w].setPos(x + 1, y - 1, 'W');
			}
			else if (map[x][y - 1] == ' ') {
				Wolves.push_back(Wolf());
				Wolves[w].setFat(0.5);
				Wolves[w].setPos(x, y - 1, 'W');
			}
			else {
				// Jeœli nie ma wolnego pola w pobli¿u rodzica to siê nie rozmna¿aj
				subFat();
			}
		}
		else if (n == 2) {
			// Przenosi go na puste pole w poblizu rodzicow
			if (map[x - 1][y - 1] == ' ') {
				SheWolves.push_back(SheWolf());
				SheWolves[s].setFat(0.2);
				SheWolves[s].setPos(x - 1, y - 1, 'S');
			}
			else if (map[x - 1][y] == ' ') {
				SheWolves.push_back(SheWolf());
				SheWolves[s].setFat(0.2);
				SheWolves[s].setPos(x - 1, y, 'S');
			}
			else if (map[x - 1][y + 1] == ' ') {
				SheWolves.push_back(SheWolf());
				SheWolves[s].setFat(0.2);
				SheWolves[s].setPos(x - 1, y + 1, 'S');
			}
			else if (map[x][y + 1] == ' ') {
				SheWolves.push_back(SheWolf());
				SheWolves[s].setFat(0.2);
				SheWolves[s].setPos(x, y + 1, 'S');
			}
			else if (map[x + 1][y + 1] == ' ') {
				SheWolves.push_back(SheWolf());
				SheWolves[s].subFat();
				SheWolves[s].setPos(x + 1, y + 1, 'S');
			}
			else if (map[x + 1][y] == ' ') {
				SheWolves.push_back(SheWolf());
				SheWolves[s].setFat(0.2);
				SheWolves[s].setPos(x + 1, y, 'S');
			}
			else if (map[x + 1][y - 1] == ' ') {
				SheWolves.push_back(SheWolf());
				SheWolves[s].setFat(0.2);
				SheWolves[s].setPos(x + 1, y - 1, 'S');
			}
			else if (map[x][y - 1] == ' ') {
				SheWolves.push_back(SheWolf());
				SheWolves[s].setFat(0.2);
				SheWolves[s].setPos(x, y - 1, 'S');
			}
			else {
				subFat();
			}
		}
	}
	
}

void Wolf::move() {
	// Wylosuj kierunek
	int d = rand() % 8 + 1;
	// Pobierz aktualna pozycje zwierzaka
	int x = getPosX();
	int y = getPosY();

	int r = closeRabbitPos();
	// Jeœli królik jest w pobli¿u to rusz w poœcig
	if (r == 1){
		setPos(x - 1, y - 1, 'W');
		addFat();
	}
	else if (r == 2) {
		setPos(x - 1, y, 'W');
		addFat();
	}
	else if (r == 3) {
		setPos(x - 1, y + 1, 'W');
		addFat();
	}
	else if (r == 4) {
		setPos(x, y + 1, 'W');
		addFat();
	}
	else if (r == 5) {
		setPos(x + 1, y + 1, 'W');
		addFat();
	}
	else if (r == 6) {
		setPos(x + 1, y, 'W');
		addFat();
	}
	else if (r == 7) {
		setPos(x + 1, y - 1, 'W');
		addFat();
	}
	else if (r == 8) {
		setPos(x, y - 1, 'W');
		addFat();
	}
	else {
		// Jeœli nie ma królika, ale jest wilczyca w pobli¿u to rusz w poœcig i wyprodukuj potomka losowej p³ci
		if (map[x - 1][y - 1] == 'S') {
			doReproduction(x, y);
			subFat();
		}
		else if (map[x - 1][y] == 'S') {
			doReproduction(x, y);
			subFat();
		}
		else if (map[x - 1][y + 1] == 'S') {
			doReproduction(x, y);
			subFat();
		}
		else if (map[x][y + 1] == 'S') {
			doReproduction(x, y);
			subFat();
		}
		else if (map[x + 1][y + 1] == 'S') {
			doReproduction(x, y);
			subFat();
		}
		else if (map[x + 1][y] == 'S') {
			doReproduction(x, y);
			subFat();
		}
		else if (map[x + 1][y - 1] == 'S') {
			doReproduction(x, y);
			subFat();
		}
		else if (map[x][y - 1] == 'S') {
			doReproduction(x, y);
			subFat();
		}
		// Ruch w razie, gdy w poblizu nie ma krolika/wilczycy
		else {
			if (d == 1 && map[x - 1][y - 1] == ' ') {
				setPos(x - 1, y - 1, 'W');
				subFat();
			}
			else if (d == 2 && map[x - 1][y] == ' ') {
				setPos(x - 1, y, 'W');
				subFat();
			}
			else if (d == 3 && map[x - 1][y + 1] == ' ') {
				setPos(x - 1, y + 1, 'W');
				subFat();
			}
			else if (d == 4 && map[x][y + 1] == ' ') {
				setPos(x, y + 1, 'W');
				subFat();
			}
			else if (d == 5 && map[x + 1][y + 1] == ' ') {
				setPos(x + 1, y + 1, 'W');
				subFat();
			}
			else if (d == 6 && map[x + 1][y] == ' ') {
				setPos(x + 1, y, 'W');
				subFat();
			}
			else if (d == 7 && map[x + 1][y - 1] == ' ') {
				setPos(x + 1, y - 1, 'W');
				subFat();
			}
			else if (d == 8 && map[x][y - 1] == ' ') {
				setPos(x, y - 1, 'W');
				subFat();
			}
			else subFat();
		}
	}
}

void Wolf::subFat() {
	// odejmij 0.1 porcji t³uszczu
	if (fat > 0.1) {
		fat -= 0.1;
	}
	else {
		dieWolf();
	}
}

SheWolf::SheWolf(){
	// n - oznacza rozmiar mapy (z ogrodzeniem)
	posX = rand() % (fence - 1) + 1;
	posY = rand() % (m - 1) + 1;
	if (map[posX][posY] == ' ') {
		map[posX][posY] = 'S';
	}
	else {
		while (map[posX][posY] != ' ') {
			posX = rand() % (fence - 1) + 1;
			posY = rand() % (m - 1) + 1;
		}
		map[posX][posY] = 'S';
	}
}

int SheWolf::closeRabbitPos() const{
	int x = getPosX();
	int y = getPosY();

	if (map[x - 1][y - 1] == 'R') return 1;
	else if (map[x - 1][y] == 'R') return 2;
	else if (map[x - 1][y + 1] == 'R') return 3;
	else if (map[x][y + 1] == 'R') return 4;
	else if (map[x + 1][y + 1] == 'R') return 5;
	else if (map[x + 1][y] == 'R') return 6;
	else if (map[x + 1][y - 1] == 'R') return 7;
	else if (map[x][y - 1] == 'R') return 8;
	else return 0;
}

void SheWolf::move(){
	// Wylosuj kierunek
	int d = rand() % 8 + 1;
	// Pobierz aktualna pozycje zwierzaka
	int x = getPosX();
	int y = getPosY();

	int r = closeRabbitPos();
	// Gonitwa za królikiem
	if (r == 1) {
		setPos(x - 1, y - 1, 'S');
		addFat();
	}
	else if (r == 2) {
		setPos(x - 1, y, 'S');
		addFat();
	}
	else if (r == 3) {
		setPos(x - 1, y + 1, 'S');
		addFat();
	}
	else if (r == 4) {
		setPos(x, y + 1, 'S');
		addFat();
	}
	else if (r == 5) {
		setPos(x + 1, y + 1, 'S');
		addFat();
	}
	else if (r == 6) {
		setPos(x + 1, y, 'S');
		addFat();
	}
	else if (r == 7) {
		setPos(x + 1, y - 1, 'S');
		addFat();
	}
	else if (r == 8) {
		setPos(x, y - 1, 'S');
		addFat();
	}
	else {
		// Normalny losowy ruch, jeœli królika nie ma w oko³o
		if (d == 1 && map[x - 1][y - 1] == ' ' && isEndOfMap(x - 1, y - 1) == false) {
			setPos(x - 1, y - 1, 'S');
			subFat();
		}
		else if (d == 2 && map[x - 1][y] == ' ' && isEndOfMap(x - 1, y) == false) {
			setPos(x - 1, y, 'S');
			subFat();
		}
		else if (d == 3 && map[x - 1][y + 1] == ' ' && isEndOfMap(x - 1, y + 1) == false) {
			setPos(x - 1, y + 1, 'S');
			subFat();
		}
		else if (d == 4 && map[x][y + 1] == ' ' && isEndOfMap(x, y + 1) == false) {
			setPos(x, y + 1, 'S');
			subFat();
		}
		else if (d == 5 && map[x + 1][y + 1] == ' ' && isEndOfMap(x + 1, y + 1) == false) {
			setPos(x + 1, y + 1, 'S');
			subFat();
		}
		else if (d == 6 && map[x + 1][y] == ' ' && isEndOfMap(x + 1, y) == false) {
			setPos(x + 1, y, 'S');
			subFat();
		}
		else if (d == 7 && map[x + 1][y - 1] == ' ' && isEndOfMap(x + 1, y - 1) == false) {
			setPos(x + 1, y - 1, 'S');
			subFat();
		}
		else if (d == 8 && map[x][y - 1] == ' ' && isEndOfMap(x, y - 1) == false) {
			setPos(x, y - 1, 'S');
			subFat();
		}
		else subFat();
	}
}

void SheWolf::dieSheWolf() {
	int x = getPosX();
	int y = getPosY();

	for (int i = 0; i < SheWolves.size(); i++) {
		if (SheWolves[i].getPosX() == x && SheWolves[i].getPosY() == y) {
			SheWolves.erase(SheWolves.begin() + i);
			map[x][y] = ' ';
		}
	}
}

void SheWolf::subFat(){
	// odejmij 0.1 porcji t³uszczu
	if (fat > 0.1) {
		fat -= 0.1;
	}
	else {
		dieSheWolf();
	}
}
