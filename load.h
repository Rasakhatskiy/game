#include <SFML\Graphics.hpp>

using namespace sf;

	Texture background;//создаем объект Texture (текстура)
	Sprite BackGroundg;

	Image cellImage;//объект изображения для карты	
	Texture cellTexture;//текстура карты	
	Sprite cellSprite;

	Image map_image;//объект изображения для карты	
	Texture map_texture;//текстура карты	
	Sprite s_map; //создаём спрайт для карты

	Image swordImage;
	Texture swordTexture;
	Sprite swordSprite;

	Image enemyImage;
	Image heroImage;

	Image spritesIm;
	Texture spritesTex;

	Image bombImage;
	Texture bombTexture;
	Sprite bombSprite;
	

	void loadImages() {
		background.loadFromFile("Images/bg.png");//передаем в него объект Image (изображения)
		BackGroundg.setTexture(background);

		cellImage.loadFromFile("images/2.png");//загружаем файл для карты
		cellTexture.loadFromImage(cellImage);//заряжаем текстуру картинкой
		cellSprite.setTexture(cellTexture);//создаём спрайт для карты

		map_image.loadFromFile("images/2.png");//загружаем файл для карты
		map_texture.loadFromImage(map_image);//заряжаем текстуру картинкой
		s_map.setTexture(map_texture);


		enemyImage.loadFromFile("images/enemyAnim.png");
		enemyImage.createMaskFromColor(Color::White);

		swordImage.loadFromFile("images/ammozhopa.png");
		swordTexture.loadFromImage(swordImage);
		swordSprite.setTexture(swordTexture);

		spritesIm.loadFromFile("images/sprites.png");
		spritesTex.loadFromImage(spritesIm);

		bombImage.loadFromFile("images/bomb.png");
		bombTexture.loadFromImage(bombImage);
		bombSprite.setTexture(bombTexture);
	}

	class Button {
	public:
		Image image;
		Texture texture;
		Sprite sprite;
		float rx, ry;
		int w, h, sx, sy;
		Button(float X, float Y, int W, int H, int SX, int SY) {
			rx = X;
			ry = Y;
			w = W;
			h = H;
			sx = SX;
			sy = SY;
			
			image.loadFromFile("images/sprites.png");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			sprite.setTextureRect(IntRect(sy, sx, w, h));
			//sprite.setPosition(rx, ry);
		}
		void draw(RenderWindow &window) {
			Vector2f center = window.getView().getCenter();
			Vector2f size = window.getView().getSize();

			sprite.setPosition(center.x - size.x / 2 + rx, center.y - size.y / 2 + ry);//позиция на экране
			
			window.draw(sprite);
		}
	};
