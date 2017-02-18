#include <SFML\Graphics.hpp>

using namespace sf;

View view;

void getPlayerCoordinateForView(float x, float y, const unsigned short int WW, const unsigned short int WH) { //������� ��� ���������� ��������� ������
	float tempX = x; float tempY = y;//��������� ����� ������ � ��������� ��, ����� ������ ����
	const unsigned short int WindowWidht = WW;
	const unsigned short int WindowHeight = WH;

	if (x < 534) tempX = 534;//������� �� ���� ����� �������
	if (x > WindowWidht - 810) tempX = WindowWidht - 810;//������� �� ���� ����� �������
	if (y < 300) tempY = 300;//������� �������
	if (y > WindowHeight - 500) tempY = WindowHeight - 500;//������ �������	

	view.setCenter(tempX, tempY); //������ �� �������, ��������� ��� ����������. 

}