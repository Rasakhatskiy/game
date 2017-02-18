#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>



unsigned const  short int invH = 6;
unsigned const  short int invW = 8;

char inventoryArray[invH][invW]{
	'z', 'z', ' ', ' ', ' ', ' ', ' ', ' ',
	'g', 'w', ' ', ' ', ' ', ' ', ' ', ' ',
	'0', 'z', ' ', ' ', ' ', ' ', ' ', ' ',
	'z', 't', ' ', ' ', ' ', ' ', ' ', ' ',
	'g', 'z', ' ', ' ', ' ', ' ', ' ', ' ',
	'g', 'z', ' ', ' ', ' ', ' ', ' ', ' ',
};
char quickSlotArray[invW];

unsigned short int invCount[invH][invW]{
	1, 1, 0, 0, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0, 0, 0,
};


class Inventory {
public:
	Image image;
	Texture t;
	Sprite s;
	Font font;
	Text numt;
	string nums;
	
	Inventory()
	{
		image.loadFromFile("images/topInventory.png");
		image.createMaskFromColor(Color::White);
		t.loadFromImage(image);
		s.setTexture(t);

		font.loadFromFile("Aileron-Regular.otf");
		numt.setFont(font);
		//num.setString("Health : 100 / 100");
		numt.setColor(Color::Black);
		numt.setCharacterSize(6);
	}

	void draw(RenderWindow &window)
	{
		Vector2f center = window.getView().getCenter();
		Vector2f size = window.getView().getSize();

		s.setPosition(center.x - size.x / 2 + 10, center.y - size.y / 2 + 10);//позиция на экране
		window.draw(s);
		for (int i = 0; i < invH; i++) {
			for (int j = 0; j < invW; j++) {
				nums = std::to_string(invCount[i][j]);
				if (invCount[i][j] == 0)
					numt.setString("");
				else
				numt.setString(nums);
				numt.setPosition((s.getPosition().x + 35) + j * 20, (s.getPosition().y + 10 + i * 20));
				window.draw(numt);
			}
		}
	}
};

