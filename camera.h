#include <SFML\Graphics.hpp>

using namespace sf;

View view;

void getPlayerCoordinateForView(float x, float y, const unsigned short int WW, const unsigned short int WH) { //функция для считывания координат игрока
	float tempX = x; float tempY = y;//считываем коорд игрока и проверяем их, чтобы убрать края
	const unsigned short int WindowWidht = WW;
	const unsigned short int WindowHeight = WH;

	if (x < 534) tempX = 534;//убираем из вида левую сторону
	if (x > WindowWidht - 810) tempX = WindowWidht - 810;//убираем из вида левую сторону
	if (y < 300) tempY = 300;//верхнюю сторону
	if (y > WindowHeight - 500) tempY = WindowHeight - 500;//нижнюю сторону	

	view.setCenter(tempX, tempY); //следим за игроком, передавая его координаты. 

}