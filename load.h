#include <SFML\Graphics.hpp>

using namespace sf;

	Texture background;//������� ������ Texture (��������)
	Sprite BackGroundg;

	Image cellImage;//������ ����������� ��� �����	
	Texture cellTexture;//�������� �����	
	Sprite cellSprite;

	Image map_image;//������ ����������� ��� �����	
	Texture map_texture;//�������� �����	
	Sprite s_map; //������ ������ ��� �����

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
		background.loadFromFile("Images/bg.png");//�������� � ���� ������ Image (�����������)
		BackGroundg.setTexture(background);

		cellImage.loadFromFile("images/2.png");//��������� ���� ��� �����
		cellTexture.loadFromImage(cellImage);//�������� �������� ���������
		cellSprite.setTexture(cellTexture);//������ ������ ��� �����

		map_image.loadFromFile("images/2.png");//��������� ���� ��� �����
		map_texture.loadFromImage(map_image);//�������� �������� ���������
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

			sprite.setPosition(center.x - size.x / 2 + rx, center.y - size.y / 2 + ry);//������� �� ������
			
			window.draw(sprite);
		}
	};
