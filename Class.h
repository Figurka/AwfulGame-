
#pragma once // Включение происходит только 1 раз. не стандартная дирректива.предложил VS
#include <iostream> 
#include <SFML\Graphics.hpp> 
using namespace sf;


//////////MainClass//////////
class Smth
{
public:
	int direction;//для определения какое необходимо выполнять сейчас действие
	enum { left, right, up, down, stay} state;//перечесляемый тип для того,чтобы игрок понимал какое действие нужно выполнять при различных состояни
	float dx, dy, x, y, Speed;//координаты пространства и скорости
	float CurrentFrame=0;//количество кадров
	int w, h, Health;//высота,ширина и здоровье
	bool Life;//для проверки жив ли объект
	Texture texture;
	Sprite sprite;
	std::string name;
	Smth(Image &image, float X, float Y, int W, int H, std::string Name);
	FloatRect getRect();//эта ф-ция нужна для проверки пересечений
	virtual void update(float time) = 0;//для выполнения различных действий в зависимости от времени
	virtual void interactionWithMap(float Dx, float Dy) =0; 
};


//////////Player//////////
class Player: public Smth // класс Игрока
{ 
public:
	int playerScore;
	int dir = 0; //направление (direction) движения игрока
	String File; //файл с расширением
	Player(Image &image, float X, float Y, int W, int H, std::string Name);
	void interactionWithMap(float Dx, float Dy);
	void update(float time);
	void control();//для управления игроком
};

//////////Enemy//////////
class Enemy: public Smth //
{
public:
	int num;
	Enemy(Image &image, float X, float Y, int W, int H, std::string Name);
	void interactionWithMap(float Dx, float Dy);//ф-ция проверки столкновений с картой
	void update(float time );
};

//////////Bullet//////////
class Bullet :public Smth
{//класс пули
public://направление пули 
	Bullet(Image &image, float X, float Y, int W, int H, std::string Name, int dir);
	void update(float time);
	void interactionWithMap(float Dx, float Dy);
};
