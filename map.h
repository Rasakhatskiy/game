#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>

using namespace std;


const int WIDTH_MAP = 134;//размер карты ширина 
const int HEIGHT_MAP = 70;//размер карты высота

char TileMap[HEIGHT_MAP][WIDTH_MAP]  = {' '};

/*sf::String TileMap[HEIGHT_MAP] = {
	"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
	"0                                                                                                                ",
	"0                                                                                                                ",
	"0                                                                                                                ",
	"0                                                                                                                ",
	"0                                                                                                                ",
	"0                                                                                                                ",
	"0                                                                                                                ",
	"0                                                                                                                ",
	"0                                                                                                                ",
	"0                                                                                                                ",
	"0                                                                                                                ",
	"0                                                                                                                ",
	"0                                                                                                                ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"    00000000 0000000000     000000000000      00000000000000000000000000000                                      ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"                                                                                                                 ",
	"     0                                                                                                           ",
	"    0                                                                                                          000",
	"   0                                                                                                        000000",
	"  0                                                                                                     0000000000",
	" 0                                                                                                 000000000000000",
	"0                                                                                               000000000000000000",
	"000000000000000000000000000000000000000000000000000000000000000000000000000000000   000000000000000000000000000000",
};*/

void saveMap() {
	ofstream File;
	File.open("map.txt", ios_base::in | ios_base::out);

	char buff;
	for (int i = 0; i < HEIGHT_MAP; i++) {
		for (int j = 0; j < WIDTH_MAP; j++) {
			buff = TileMap[i][j];
			File << buff;
		}
		File << endl;
	}
	File.close();
}
void loadMap() {
	ifstream File;
	File.open("map.txt", ios_base::in | ios_base::out);

	string buff;
	for (int i = 0; i < HEIGHT_MAP; i++) {
		getline(File, buff);
		for (int j = 0; j < WIDTH_MAP; j++) {
			TileMap[i][j] = buff[j] ;
		}
		
	}
	File.close();
}

