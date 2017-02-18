#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <list>

#include "bars.h"
#include "windows.h"
#include "map.h"
#include "camera.h"
#include "inventory.h"
#include "load.h"
#include "QuickSlots.h"

using namespace std;
using namespace sf;

const unsigned short int WindowWidht = 1600;
const unsigned short int WindowHeight = 900;
const unsigned short int BackGroundWidth = 1324;
const unsigned short int BackGroundHeight = 699;

void Game();
void worldUpdate();

class Entity {
public:
	float dx, dy;//направление
	float px, py;//положение
	float speed;//скорость
	int w, h;//габариты
	unsigned int health;//здоровье
	bool life, isMove, onGround;
	Texture texture;
	Sprite sprite;
	
	Entity(Image &image, float X, float Y, int W, int H) {
		px = X; py = Y; 
		w = W; h = H;
		speed = 0; health = 100; 
		dx = 0; dy = 0;
		life = true; onGround = false; isMove = false;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(0, 0);
	}
	FloatRect getRect() {
		return FloatRect(px, py, w, h);
	}
	virtual void update(float time) = 0;
};

class Bomb :public Entity{
public:
	float allahAkbarTimer;
	Bomb(Image &image, float X, float Y, float W, float H, float plx, float ply) :Entity(image, X, Y, W, H) {
		dx = 0.9;
		dy = -0.5;
		w = W;
		h = H;
		px = plx;
		py = ply;
		allahAkbarTimer = 1000;
	}
	void CheckCollision(float Dx, float Dy) {
		for (int i = py / 10; i < (py + h) / 10; i++) {
			for (int j = px / 10; j < (px + w) / 10; j++) {
				if ((i < HEIGHT_MAP) && (i < WIDTH_MAP)) {
					switch (TileMap[i][j]) {
					case '0':
					case 'b':
					case 'g':
					case 'z':
					case 't':
						if (Dy > 0) {
							py = i * 10 - h;
							dy = 0;
							onGround = true;
						}
						if (Dy < 0) {
							py = i * 10 + 10;
							dy = 0;
							onGround = false;
						}
						if (Dx > 0) {
							px = j * 10 - w;
							dx = 0;
						}
						if (Dx < 0) {
							px = j * 10 + 10;
							dx = 0;
						}
						break;
					}
				}
			}
		}
	}
	


	void update(float time) {
		dx = dx / 1.1;
		
		if (allahAkbarTimer >= 0)
			allahAkbarTimer -=  time/2;
		
		dy += 0.0015*time;

		px += dx*time;
		CheckCollision(dx, 0);
		py += dy*time;
		CheckCollision(0, dy);

		sprite.setPosition(px, py);
	}

};

class Item :public Entity{
public:
	char ID;
	Item(Image &image, float X, float Y, float W, float H, char id) :Entity(image, X, Y, W, H) {
		speed = 0;
		dx = 0;
		dy = 0;
		onGround = false;
		isMove = false;
		health = 100;
		w = W;
		h = H;
		px = X;
		py = Y;
		ID = id;
		switch (ID) {
		case '0': sprite.setTextureRect(IntRect(10, 10, 10, 10)); break;
		case 'g': sprite.setTextureRect(IntRect(0, 10, 10, 10)); break;
		case 'w': sprite.setTextureRect(IntRect(0, 0, 10, 10)); break;
		case 'z': sprite.setTextureRect(IntRect(20, 0, 10, 10)); break;
		case 't': sprite.setTextureRect(IntRect(30, 0, 10, 10)); break;

		case 's': sprite.setTextureRect(IntRect(40, 0, 32, 32));break;

		}
	}
	void CheckCollision(float Dx, float Dy) {
		for (int i = py / 10; i < (py + h) / 10; i++) {
			for (int j = px / 10; j < (px + w) / 10; j++) {
				if ((i < HEIGHT_MAP) && (i < WIDTH_MAP)) {
					switch (TileMap[i][j]) {
					case '0':
					case 'b':
					case 'g':
					case 'z':
					case 't':
						if (Dy > 0) {
							py = i * 10 - h;
							dy = 0;
							onGround = true;
						}
						if (Dy < 0) {
							py = i * 10 + 10;
							dy = 0;
							onGround = false;
						}
						if (Dx > 0) {
							px = j * 10 - w;
						}
						if (Dx < 0) {
							px = j * 10 + 10;
						}
						break;
					}
				}
			}
		}
	}
	void update(float time) {}
	void updateI(float time, float plx, float ply) {

		
		dy += 0.0015*time;

		if (dy == 0)
			onGround = true;

		px += dx*time;
		CheckCollision(dx, 0);
		py += dy*time;
		CheckCollision(0, dy);
		if (!isMove)
			speed = 0;

		
		sprite.setPosition(px, py);
	}
};

class Player :public Entity {
public:
	enum {
		left, right, up, down, jump, stay
	}state;//состояние игрока
	bool running = false, inWater = false;
	float frame;

	Player(Image &image, float X, float Y, float W, float H) :Entity(image, X, Y, W, H) {//началоб конец, ширина высота
		frame = 0;
		speed = 0;
		dx = 0;
		dy = 0;
		onGround = false;
		isMove = false;
		health = 100;
		w = W;
		h = H;
		px = X;
		py = Y;
		sprite.setTextureRect(IntRect(0, 0, w, h));
	}
	float getpcX() {
		return px;
	}
	float getpcY() {
		return py;
	}
	void control() {
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			if (px > 0) {
				state = left;
				running = true;
				speed = 0.1;
			}
		}else
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			if (px+20 < WindowWidht) {
				state = right;
				running = true;
				speed = 0.1;
			}
		}
		else
			running = false;

		if ((Keyboard::isKeyPressed(Keyboard::Space)) && (onGround)) {
			if (py < WindowHeight) {
				state = jump;
				onGround = false;
				dy = -0.5;
				if (inWater)dy = -0.2;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			if (py > 0) {
				state = down;
				speed = 0.1;
			}
		}

	}
	void CheckCollision(float Dx, float Dy) {
		for (int i = py / 10; i < (py + h) / 10; i++)
			for (int j = px / 10; j < (px + w) / 10; j++) {
				if ((i < HEIGHT_MAP) && (i < WIDTH_MAP)) {
					switch (TileMap[i][j]) {
					case '0':
					case 'b':
					case 'g':
					case 'z':
					case 't':
						if (Dy > 0) {
							py = i * 10 - h;
							dy = 0;
							onGround = true;
						}
						if (Dy < 0) {
							py = i * 10 + 10;
							dy = 0;
							onGround = false;
						}
						if (Dx > 0) {
							px = j * 10 - w;
						}
						if (Dx < 0) {
							px = j * 10 + 10;
						}
					break;
					case 'w':
						inWater = true;
					break;
					case ' ':
						inWater = false;
						//onGround = false;
					break;
					}				
				}				
			}
	}
	void update(float time) {
		control();

		if (dy == 0)
			onGround = true;

		switch (state) {
		case right:
			dx = speed;
			if (inWater)dx = speed / 3;
			if (running) {
				frame += 0.009*time;
				if (frame > 7) 
					frame = 0;
				sprite.setOrigin(0, 0);
				sprite.setTextureRect(IntRect(w * int(frame), 0, w, h));
				sprite.setScale(1, 1);
			}
			
			break;
		case left:
			dx = -speed;
			if (inWater)dx = (-speed) / 3;
			if (running) {
				frame += 0.009*time;
				if (frame > 7) 
					frame = 0;
				sprite.setOrigin(w, 0);
				sprite.setTextureRect(IntRect(w * int(frame), 0, w, h));
				sprite.setScale(-1, 1);
			}
			break;
		case jump:
			//onGround = false;
		break; 
		}
		if (!onGround) {
			frame += 0.009*time;
			if (frame > 7)
				frame = 7;
			sprite.setTextureRect(IntRect(50 * int(frame), 80, 50, h));
		}
		if (!running) {
			frame = 0;
			sprite.setTextureRect(IntRect(387, 0, w, h));
		}

		px += dx*time;
		CheckCollision(dx, 0);
		py += dy*time;
		CheckCollision(0, dy);
		if (!isMove)
			speed = 0;
		
		dy = dy + 0.0015*time;
		if (inWater)
			dy = dy + 0.0001*time;
		sprite.setPosition(px, py);
		if (px <= 0) px = 1;

	}
};

class Enemy :public Entity {
public:
	float frame;
	bool inWater;//walking;
	enum {
		left, right
	}state;
	Font font;
	Text healthText, damageText;
	string healthstr;
	float moveTimer = 0;
	Enemy(Image &image, float X, float Y, float W, float H) :Entity(image, X, Y, W, H) {
		frame = 0;
		speed = 0.07;
		dx = 0;
		dy = 0;
		onGround = false;
		inWater = false;
		health = 100;
		w = W;
		h = H;
		px = X;
		py = Y;
		float moveTimer = 0;
		sprite.setTextureRect(IntRect(0, 0, w, h));
		state = right;

		font.loadFromFile("Aileron-Regular.otf");
		healthText.setString("Health : 100 / 100");
		healthText.setFont(font);
		healthText.setColor(Color::Black);
		healthText.setCharacterSize(10);
		healthstr = std::to_string(health);
		healthText.setString("Health : " + healthstr + "/ 100");
		
	}
	void CheckCollision(float Dx, float Dy) {
		if ((px > WindowWidht - w) || (px <= 0) || (py>WindowHeight - h) || (py <= 9)) {
			px = 100;
			py = 100;
		}
		
		
		for (int i = py / 10; i < (py + h) / 10; i++)
			for (int j = px / 10; j < (px + w) / 10; j++) {
				if ((i < HEIGHT_MAP) && (i < WIDTH_MAP)) {
					switch (TileMap[i][j]) {
					case '0':
					case 'b':
					case 'g':
					case 'z':
					case 't':
						if (Dy > 0) {
							py = i * 10 - h;
							dy = 0;
							onGround = true;
						}
						if (Dy < 0) {
							py = i * 10 + 10;
							dy = 0;
							onGround = false;
						}
						if (Dx > 0) {
							px = j * 10 - w;
							state = left;
							moveTimer = 0;
						}
						if (Dx < 0) {
							px = j * 10 + 10;
							state = right;
							moveTimer = 0;
						}
						break;
					case 'w':
						inWater = true;
						break;
					case ' ':
						inWater = false;
						onGround = false;
						break;
					}					
				}
			}
	}

	void update(float time) {
		if ((px > WindowWidht - w) || (px <= 0) || (py>WindowHeight - h) || (py <= 9)) {
			px = 100;
			py = 100;
		}
		
		px += dx*time;
		CheckCollision(dx, 0);

		py += dy*time;
		CheckCollision(0, dy);

		switch (state) {
		case right:
			
			if (inWater)
				dx = speed / 3;
			else {
				speed = 0.07;
				dx = speed;
			}			
			
			//animation
			frame += 0.009*time;
			if (frame > 7)
				frame = 0;
			sprite.setOrigin(0, 0);
			sprite.setTextureRect(IntRect(w * int(frame), 0, w, h));
			sprite.setScale(1, 1);
			break;

		case left:
			if (inWater)
				dx = (-speed) / 3;
			else {
				speed = 0.07;
				dx = -speed;
			}
				
			//animation
			frame += 0.009*time;
			if (frame > 7)
				frame = 0;
			sprite.setOrigin(w, 0);
			sprite.setTextureRect(IntRect(w * int(frame), 0, w, h));
			sprite.setScale(-1, 1);
			break;
			
		}

		dy = dy + 0.0015*time;

		if (inWater)
			dy = dy + 0.0001*time;


		sprite.setPosition(px, py);
		if ((px > WindowWidht - w) || (px <= 0) || (py>WindowHeight - h) || (py <= 9)) {
			px = 100;
			py = 100;
		}
		healthstr = std::to_string(health);
		healthText.setString("Health : " + healthstr + "/ 100");
		healthText.setPosition(px, py - h/2);
	}

	void rozvorot(float Px) {
		if (Px > px)state = right;
		if (Px < px)state = left;
	}
};

class FallingBlock {
public:
	float dx, dy, px, py;
	int w, h; //spx, spx;
	char id;
	bool toBlock, toStay;
	enum {
		right, left, stay
	}direction;
	Texture texture;
	Sprite sprite;
	FallingBlock(float PX, float PY, int W, int H, char ID) {
		px = PX; py = PY;
		w = W; h = H;
		id = ID;
		dy = 0.05;
		toBlock = false;
		texture.loadFromFile("images/sprites.png");
		sprite.setTexture(texture);
		switch (id) {
		case'g':
			sprite.setTextureRect(IntRect(0, 10, w, h));
			break;
		case'w':
			//sprite.setTextureRect(IntRect(0, 0, w, h));
			break;
		default:
			;
			//sprite.setTextureRect(IntRect(10, 20, 10, 10));
		}
	}
	void CheckCollision(float Dx, float Dy) {
		for (int i = py / 10; i < (py + h) / 10; i++) {
			for (int j = px / 10; j < (px + w) / 10; j++) {
				if ((i < HEIGHT_MAP) && (i < WIDTH_MAP)) {
					switch (TileMap[i][j]) {
					case '0':
					case 'b':
					case 'g':
					case 'z':
					case 't':
						switch (id) {
						case'g':
							if (Dy > 0) {
								py = i * 10 - h;
								dy = 0;
								toBlock = true;
							}
							break;
						/*case'w':
							if (Dy > 0) {
								py = i * 10 - h;
								dy = 0;
								//toStay = true;
							}
							if (Dx > 0) {
								px = j * 10 - w;
								dx = 0;
							}
							if (Dx < 0) {
								px = j * 10 + 10;
								dx = 0;
								if (toStay) {
									if (TileMap[i][j + 1] == ' ') {
										direction = right;
									}
									else
										if (TileMap[i][j - 1] == ' ') {
											direction = left;
										}
										else {
											direction = stay;
										}
								}
								
							}
							if (Dy < 0) {
								py = i * 10 + 10;
								dy = 0;
							}
							break;*/
						}
						break;
					}
				}
			}
		}
	}
	void update(float time) {
		/*switch (direction) {
		case left:
			dx = -0.05;
			break;
		case right:
			dx = 0.05;
			break;
		case stay:
			dx = 0;
			break;
		}*/


		/*if (id == 'w') {
			px += dx*time;
			CheckCollision(dx, 0);
		}*/
	
		dy += 0.0015*time;
		
		py += dy*time;
		CheckCollision(0, dy);

		sprite.setPosition(px, py);
		cout << px << " " << py << endl;
	}
};

void Game() {
	string strotv;
	cout << "Choose character (1/2): ";
	cin >> strotv;

	heroImage.loadFromFile("images/HeroAnim" + strotv + ".png");
	heroImage.createMaskFromColor(Color(160, 192, 64));


	loadMap();

	RenderWindow window(VideoMode(WindowWidht, WindowHeight), "Hallo, SFML or I am start to learn c++ SFML", Style::Fullscreen);//render window
	view.reset(sf::FloatRect(0, 0, WindowWidht / 1.5, WindowHeight / 1.5));
	//window.setKeyRepeatEnabled(false);
	//window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	loadImages();



	//создание обьектов
	Player p(heroImage, 0, 0, 40, 69);
	Inventory inventory1;
	QuickSlot quickSlotHead;
	HBar hbar;
	Button close(1000, 10, 26, 11, 20, 0);
	/*list<Entity*>  entities;//создаю список, сюда буду кидать объекты.например врагов.
	list<Entity*>::iterator it;//итератор чтобы проходить по эл-там списка

	entities.push_back(new Enemy(enemyImage, 0, 0, 34, 60));*/

	list<Enemy*> enemies;
	list<Enemy*>::iterator enIt;

	list<Item*> items;
	list<Item*>::iterator itIt;

	list<Bomb*> bombs;
	list<Bomb*>::iterator bombIt;

	list<FallingBlock*> fallingBlocks;
	list<FallingBlock*>::iterator fallingBlocksIter;

	short int swordWidth = 43, swordHeight = 16;

	bool ifAttac = false;
	bool invShow = false;//открыт ли инвентарь
	bool chosen = false;//выбран ли предмет
	char invBuff = ' ', buffBuff = ' ';//буфер инвентаря
	unsigned short int invCountBuff = 0, countBuffBuff = 0;
	float timerInv = 0,//кулдаун клацанья даунской мыши
		tabTimer = 0,//кулдаун таб
		teleportTimer = 0,
		spawnTimer = 0,//спавн ботов
		attacTimer = 0,//кулдаун атаки
		hurtTimer = 0,//кулдаун урона
		regenTimer = 0;


	Sprite movSprite(cellTexture);
	movSprite.setTextureRect(IntRect(10, 0, 10, 10));

	bool toClose = false;

	Clock clock;
	while (window.isOpen()) {
		float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
		clock.restart(); //перезагружает время
		time = time / 900;
		

		Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
		Vector2f pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)

		Vector2f center = window.getView().getCenter();
		Vector2f size = window.getView().getSize();
		
		if ((pos.x > close.sprite.getPosition().x) && (pos.x < close.sprite.getPosition().x + close.w) && (pos.y > close.sprite.getPosition().y) && (pos.y < close.sprite.getPosition().y + close.h)) {
			if (Mouse::isButtonPressed(Mouse::Left)){
				toClose = true;
			}
		}
			

		Event event;
		while (window.pollEvent(event)) {
			if ((event.type == Event::Closed) || (toClose)){
				saveMap();
				window.close();
			}
		}

		

		spawnTimer += time;
		if (spawnTimer > 500)
			spawnTimer = 500;
		if (Keyboard::isKeyPressed(Keyboard::E)) {
			if (spawnTimer == 500) {
				spawnTimer = 0;
				enemies.push_back(new Enemy(enemyImage, pos.x, pos.y, 34, 60));
			}
		}
		


		if (!invShow) {
			if (Mouse::isButtonPressed(Mouse::Left)) {
				switch (TileMap[int(pos.y / 10)][int(pos.x / 10)]) {
				case 't':
					items.push_back(new Item(spritesIm, pos.x, pos.y, 10, 10, 't'));
					TileMap[int(pos.y / 10)][int(pos.x / 10)] = ' ';
					break;
				case 'g':
					items.push_back(new Item(spritesIm, pos.x, pos.y, 10, 10, 'g'));
					TileMap[int(pos.y / 10)][int(pos.x / 10)] = ' ';
					break;
				case 'w':
					items.push_back(new Item(spritesIm, pos.x, pos.y, 10, 10, 'w'));
					TileMap[int(pos.y / 10)][int(pos.x / 10)] = ' ';
					break;
				case '0':
					items.push_back(new Item(spritesIm, pos.x, pos.y, 10, 10, '0'));
					TileMap[int(pos.y / 10)][int(pos.x / 10)] = ' ';
					break;
				case 'z':
					items.push_back(new Item(spritesIm, pos.x, pos.y, 10, 10, 'z'));
					TileMap[int(pos.y / 10)][int(pos.x / 10)] = ' ';
					break;

				}
			}
			
			if (Mouse::isButtonPressed(Mouse::Right)) {
				TileMap[int(pos.y / 10)][int(pos.x / 10)] = '0';
			}
			if (Keyboard::isKeyPressed(Keyboard::G)) {
				TileMap[int(pos.y / 10)][int(pos.x / 10)] = 'g';
			}
			if (Keyboard::isKeyPressed(Keyboard::V)) {
				TileMap[int(pos.y / 10)][int(pos.x / 10)] = 'w';
			}
			if (Keyboard::isKeyPressed(Keyboard::Z)) {
				TileMap[int(pos.y / 10)][int(pos.x / 10)] = 'z';
			}
			if (Keyboard::isKeyPressed(Keyboard::T)) {
				TileMap[int(pos.y / 10)][int(pos.x / 10)] = 't';
			}
			if (Keyboard::isKeyPressed(Keyboard::B)) {
				bombs.push_back(new Bomb(bombImage, pos.x, pos.y, 15, 15, p.px, p.py));//, p.px, p.py));
					
			}


		}

		if (invShow) {
			timerInv += time;

			if (timerInv > 500)
				timerInv = 500;

			if ((pixelPos.x < 283) && (pixelPos.y < 191) && (pixelPos.x > 46) && (pixelPos.y > 16)) {
				if (!chosen) {
					if (timerInv > 80) {
						if (Mouse::isButtonPressed(Mouse::Left)) {
							//if ((event.mouseButton.button == Mouse::Left) && (event.MouseButtonReleased)) 
							unsigned int tempCell_x = int((pixelPos.x - 46) / 30);
							unsigned int tempCell_y = int((pixelPos.y - 16) / 30);

							chosen = true;

							timerInv = 0;
							invCountBuff = invCount[tempCell_y][tempCell_x];
							invCount[tempCell_y][tempCell_x] = 0;

							invBuff = inventoryArray[tempCell_y][tempCell_x];
							inventoryArray[tempCell_y][tempCell_x] = ' ';
							//movSprite.setTextureRect(IntRect(10, 0, 10, 10));
						}
					}
				}
				if (chosen) {
					switch (invBuff) {
					case 'k': movSprite.setTextureRect(IntRect(10, 10, 10, 10)); break;
					case 'g': movSprite.setTextureRect(IntRect(0, 10, 10, 10)); break;
					case 'w': movSprite.setTextureRect(IntRect(0, 0, 10, 10)); break;
					case 'z': movSprite.setTextureRect(IntRect(20, 0, 10, 10)); break;
					case 't': movSprite.setTextureRect(IntRect(30, 0, 10, 10)); break;
					default: movSprite.setTextureRect(IntRect(10, 0, 10, 10));
					}
					movSprite.setPosition(pos.x, pos.y);
					if (timerInv > 80) {
						if (Mouse::isButtonPressed(Mouse::Left)) {
							unsigned int tempCell_x = int((pixelPos.x - 46) / 30);
							unsigned int tempCell_y = int((pixelPos.y - 16) / 30);
							chosen = false;
							timerInv = 0;

							if (inventoryArray[tempCell_y][tempCell_x] != ' ') {
								if (inventoryArray[tempCell_y][tempCell_x] == invBuff) {
									invBuff = ' ';
									buffBuff = ' ';
									invCount[tempCell_y][tempCell_x] += invCountBuff;
									invCountBuff = 0;
									countBuffBuff = 0;
								}
								if(invBuff != ' ')
									chosen = true;
								buffBuff = inventoryArray[tempCell_y][tempCell_x];
								countBuffBuff = invCount[tempCell_y][tempCell_x];

								inventoryArray[tempCell_y][tempCell_x] = invBuff;
								invCount[tempCell_y][tempCell_x] = invCountBuff;

								invCountBuff = countBuffBuff;
								invBuff = buffBuff;

								buffBuff = ' ';
								countBuffBuff = 0;
							}
							if (inventoryArray[tempCell_y][tempCell_x] == ' ') {
								inventoryArray[tempCell_y][tempCell_x] = invBuff;
								invCount[tempCell_y][tempCell_x] = invCountBuff;

								invCountBuff = 0;
								invBuff = ' ';

								buffBuff = ' ';
								countBuffBuff = 0;
							}
						}
					}
				}
			}
		}
		for (int i = 0; i < invW; i++) {
			quickSlotArray[i] = inventoryArray[0][i];
		}

		teleportTimer += time;
		if (teleportTimer > 5000)
			teleportTimer = 5000;

		if (teleportTimer == 5000)
			if (Keyboard::isKeyPressed(Keyboard::M)) {
				p.px = pos.x;
				p.py = pos.y;
				teleportTimer = 0;
			}



		tabTimer += time;
		if (tabTimer > 500)
			tabTimer = 500;
		if (tabTimer > 100)
			if (Keyboard::isKeyPressed(Keyboard::Tab)) {
				tabTimer = 0;
				invShow = !invShow;
			}

		///////////Ахтунг! респавн/////////////
		if ((p.px > WindowWidht - p.w) || (p.px <= 0) || (p.py>WindowHeight - p.h) || (p.py <= 9)) {
			p.px = 100;
			p.py = 100;
		}

		regenTimer += time / 2;
		if (regenTimer > 4000) {
			if (p.health < 100)
				p.health += 20;
			regenTimer = 0;
		}

		hurtTimer += time;
		if (hurtTimer > 3000)
			hurtTimer = 3000;

		for (enIt = enemies.begin(); enIt != enemies.end(); enIt++)//проходимся по эл-там списка
		{
			if ((*enIt)->getRect().intersects(p.getRect()))//если прямоугольник спрайта объекта пересекается с игроком
			{
				if (hurtTimer == 3000) {
					if (p.health >= 20)
						p.health -= 20;
					hurtTimer = 0;
					cout << p.health << endl;
				}
			}
		}

		for (itIt = items.begin(); itIt != items.end(); itIt++)//проходимся по эл-там списка
		{
			if ((*itIt)->getRect().intersects(p.getRect()))//если прямоугольник спрайта объекта пересекается с игроком
			{	
				for (int i = 0; i < invH; i++) {
					for (int j = 0; j < invW; j++) {
						if ((*itIt)->ID == inventoryArray[i][j]) {
							invCount[i][j]++;
							
							break;
						}
					}
				}
				itIt = items.erase(itIt);
				break;// это шоб итератор не глюкал АХТУНГ ВАЖНО НЕ УБИРАТЬ!!!
			}
		}

		getPlayerCoordinateForView(p.getpcX(), p.getpcY(), WindowWidht, WindowHeight);
		window.setView(view);
		window.clear();
		window.draw(BackGroundg);

		for (enIt = enemies.begin(); enIt != enemies.end(); enIt++) {
			(*enIt)->update(time);
			(*enIt)->rozvorot(p.px);
			window.draw((*enIt)->sprite);
			if ((pos.x > (*enIt)->px) && (pos.x < (*enIt)->px + (*enIt)->w) && (pos.y >(*enIt)->py) && (pos.y < (*enIt)->py + (*enIt)->h))
				window.draw((*enIt)->healthText);
		}
		
		for (itIt = items.begin(); itIt != items.end(); itIt++) {
			(*itIt)->updateI(time, p.px, p.py);
			window.draw((*itIt)->sprite);		
		}
		for (bombIt = bombs.begin(); bombIt != bombs.end(); bombIt++) {
			(*bombIt)->update(time);
			window.draw((*bombIt)->sprite);
		}
		for (bombIt = bombs.begin(); bombIt != bombs.end(); bombIt++) {
			//if ((*bombIt)->getRect().intersects(FloatRect(swordSprite.getPosition().x, swordSprite.getPosition().y, swordWidth, swordHeight))) {
			//(*enIt)->health -= 20;
			//(*enIt)->dy = -0.3;
			//if ((*enIt)->dx > 0)
			//	(*enIt)->dx = 0.7;
			//	if ((*enIt)->dx < 0)
			//	(*enIt)->dx = -0.7;
			//	if ((*enIt)->health <= 0) {
			if ((*bombIt)->allahAkbarTimer <= 0)
				bombIt = bombs.erase(bombIt);//убиваем врага
			break;// это шоб итератор не глюкал АХТУНГ ВАЖНО НЕ УБИРАТЬ!!!
		}
		//для всех элементов списка(пока это только враги,но могут быть и пули к примеру) активируем ф-цию update

		for (int i = 1; i < HEIGHT_MAP - 1; i++) {
			for (int j = 1; j < WIDTH_MAP - 1; j++) {
				switch (TileMap[i][j])
				{
				case 'g':
					if (TileMap[i + 1][j] == ' ' || TileMap[i + 1][j] == 'w') {
						fallingBlocks.push_back(new FallingBlock(j * 10, i * 10, 10, 10, TileMap[i][j]));
						cout << j << " " << i << TileMap[i][j] << endl;
						TileMap[i][j] = TileMap[i + 1][j];
						
					}
					break;
				/*case 'w':
					if (TileMap[i + 1][j] == ' ') {
						
						TileMap[i][j] = TileMap[i + 1][j];
						
					}

					if (TileMap[i][j + 1] == ' ') {
						
						TileMap[i][j] = TileMap[i][j + 1];
						
					}
					if (TileMap[i][j - 1] == ' ') {
						
						TileMap[i][j] = TileMap[i][j - 1];
						
					}
					break;*/
				}
			}
		}

		for (fallingBlocksIter = fallingBlocks.begin(); fallingBlocksIter != fallingBlocks.end(); fallingBlocksIter++) {
			(*fallingBlocksIter)->update(time);
			window.draw((*fallingBlocksIter)->sprite);
		}
		for (fallingBlocksIter = fallingBlocks.begin(); fallingBlocksIter != fallingBlocks.end(); fallingBlocksIter++) {
			if ((*fallingBlocksIter)->toBlock) {
				TileMap[(int)((*fallingBlocksIter)->py / 10)][(int)((*fallingBlocksIter)->px / 10)] = 'g'; 
				fallingBlocksIter = fallingBlocks.erase(fallingBlocksIter);
				break;
			}		
		}
		
		p.update(time);
		window.draw(p.sprite);

		attacTimer += time / 2;
		if (attacTimer > 300)
			attacTimer = 300;

		swordHeight = 16;
		swordWidth = 43;
		swordSprite.setPosition(p.px + p.w / 2, p.py + p.h / 2);
		switch (p.state) {
		case 0://left
			swordSprite.setScale(-1, 1);
			swordWidth = -43;			
			break;
		case 1://right
			swordSprite.setScale(1, 1);
			swordWidth = 43;
			break;
		}



		for (int i = 0; i < HEIGHT_MAP; i++) {
			for (int j = 0; j < WIDTH_MAP; j++) {
				switch (TileMap[i][j]) {
				case 's':
					s_map.setTextureRect(IntRect(0, 0, 10, 10));
					break;
				case '0':
					s_map.setTextureRect(IntRect(10, 10, 10, 10));
					break;
				case 'g':
					s_map.setTextureRect(IntRect(0, 10, 10, 10));
					break;
				case 'w':
					s_map.setTextureRect(IntRect(0, 0, 10, 10));
					break;
				case 'z':
					s_map.setTextureRect(IntRect(20, 0, 10, 10));
					break;
				case 't':
					s_map.setTextureRect(IntRect(30, 0, 10, 10));
					break;
				default:
					s_map.setTextureRect(IntRect(10, 0, 10, 10));
					break;
				}

				//lol kek cheburek what it is???
				s_map.setPosition(j * 10, i * 10);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

				window.draw(s_map);//рисуем квадратики на экран
			}
		}

		if (attacTimer == 300)
			if (Keyboard::isKeyPressed(Keyboard::Q)) {
				attacTimer = 0;
				for (enIt = enemies.begin(); enIt != enemies.end(); enIt++)
					if ((*enIt)->getRect().intersects(FloatRect(swordSprite.getPosition().x, swordSprite.getPosition().y, swordWidth, swordHeight))) {
						(*enIt)->health -= 20;
						(*enIt)->dy = -0.3;
						if ((*enIt)->dx > 0)
							(*enIt)->dx = 0.7;
						if ((*enIt)->dx < 0)
							(*enIt)->dx = -0.7;
						if ((*enIt)->health <= 0) {
							enIt = enemies.erase(enIt);//убиваем врага
							break;// это шоб итератор не глюкал АХТУНГ ВАЖНО НЕ УБИРАТЬ!!!
						}

					}
				window.draw(swordSprite);
			}

		


		if (invShow) {
			inventory1.draw(window);

			for (int i = 0; i < invH; i++) {
				for (int j = 0; j < invW; j++) {
					switch (inventoryArray[i][j]) {
					case '0': cellSprite.setTextureRect(IntRect(10, 10, 10, 10)); break;
					case 'g': cellSprite.setTextureRect(IntRect(0, 10, 10, 10)); break;
					case 'w': cellSprite.setTextureRect(IntRect(0, 0, 10, 10)); break;
					case 'z': cellSprite.setTextureRect(IntRect(20, 0, 10, 10)); break;
					case 't': cellSprite.setTextureRect(IntRect(30, 0, 10, 10)); break;
					default: cellSprite.setTextureRect(IntRect(10, 0, 10, 10));
					}
					cellSprite.setOrigin(5, 5);
					cellSprite.setPosition((inventory1.s.getPosition().x + 30) + j * 20, (inventory1.s.getPosition().y + 10 + i * 20));
					window.draw(cellSprite);
				}
			}
			
			if (chosen)
				window.draw(movSprite);
		}
		else {
			quickSlotHead.draw(window);
			quickSlotHead.drawQuickSlot(window, quickSlotArray);
		}

		hbar.draw(window, p.health);
		close.draw(window);

		window.display();

	}
}


int main()
{
	Game();
	return 0;
}