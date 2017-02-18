#include <SFML\Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class QuickSlot {
public:
	Image image;
	Texture t;
	Sprite s;
	
	Image cellImage;//объект изображения для карты	
	Texture cellTexture;//текстура карты	
	Sprite cellSprite;

	QuickSlot()
	{
		image.loadFromFile("images/qslot.png");
		t.loadFromImage(image);
		s.setTexture(t);
		cellImage.loadFromFile("images/sprites.png");//загружаем файл для карты
		cellTexture.loadFromImage(cellImage);//заряжаем текстуру картинкой
		cellSprite.setTexture(cellTexture);//создаём спрайт для карты
	}

	void draw(RenderWindow &window)
	{
		Vector2f center = window.getView().getCenter();
		Vector2f size = window.getView().getSize();

		s.setPosition(center.x - size.x / 2 + 30, center.y - size.y / 2 + 10);//позиция на экране

		window.draw(s);
	}
	void drawQuickSlot(RenderWindow &window, char quick[]) {
		Vector2f center = window.getView().getCenter();
		Vector2f size = window.getView().getSize();
		for (int i = 0; i < invW; i++) {
			switch (quick[i]) {
			case 'k': cellSprite.setTextureRect(IntRect(10, 10, 10, 10)); break;
			case 'g': cellSprite.setTextureRect(IntRect(0, 10, 10, 10)); break;
			case 'w': cellSprite.setTextureRect(IntRect(0, 0, 10, 10)); break;
			case 'z': cellSprite.setTextureRect(IntRect(20, 0, 10, 10)); break;
			case 't': cellSprite.setTextureRect(IntRect(30, 0, 10, 10)); break;
			default: cellSprite.setTextureRect(IntRect(11, 0, 9, 9));

			}
			cellSprite.setPosition(center.x - size.x / 2 + 35 + i * 20, center.y - size.y / 2 + 15);//(s.getPosition().x + 30 + i * 20), (s.getPosition().y + 10));
			window.draw(cellSprite);
		}
	}

};
