#include <SFML\Graphics.hpp>
#include <string>
using namespace sf;

class HBar{
public:
	
	Image image;
	Texture t;
	Sprite s;
	Font alieron;
	Text lifeText;
	String healthstr;

	HBar() {
		image.loadFromFile("images/heart.png");
		alieron.loadFromFile("Aileron-Regular.otf");
		t.loadFromImage(image);
		s.setTexture(t);

		lifeText.setString("Health : 100 / 100");
		lifeText.setFont(alieron);
		lifeText.setColor(Color::Black);
		lifeText.setCharacterSize(12);
		
	}
	void draw(RenderWindow &window, unsigned int health)
	{
		Vector2f center = window.getView().getCenter();
		Vector2f size = window.getView().getSize();

		s.setPosition(center.x - size.x / 2 + 10, center.y - size.y / 2 + 10);//позиция на экране

		for (int i = 0; i < (health / 20); i++) {
			s.setPosition(center.x - size.x / 2 + i * 20 + 600, center.y - size.y / 2 + 10);//center.x - size.x / 2 + 500 + i*20, center.y - size.y / 2 + 10);
			lifeText.setPosition(center.x - size.x / 2 + 600, center.y - size.y / 2 + 35);
			healthstr = std::to_string(health);
			lifeText.setString("Health : " + healthstr +  "/ 100");
			window.draw(s);
			window.draw(lifeText);
		}


	}
};
