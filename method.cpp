#pragma once // Включение происходит только 1 раз. не стандартная дирректива.предложил VS
#include <iostream> 
#include <SFML\Graphics.hpp>
#include "Class.h"
#include "map.h"
using namespace sf;

//////////Enemy//////////
Enemy::Enemy(Image &image, float X, float Y, int W, int H, std::string Name) :Smth(image, X, Y, W, H, Name)
{
	if (name == "EasyEnemy")
	{
		direction = rand() % (4); //Направление движения врага задаём случайным образом //через генератор случайных чисел
		Speed = 0.1;//даем скорость.этот объект всегда двигается 
		dx = Speed;
	}
}


void Enemy::interactionWithMap(float Dx, float Dy)//ф-ция проверки столкновений с картой
{

};

void Enemy::update(float time)
{

};

//////////Bullet//////////
Bullet::Bullet(Image &image, float X, float Y, int W, int H, std::string Name, int dir) :Smth(image, X, Y, W, H, Name)
{
	x = X; //координаты пули на карте игры
	y = Y;
	direction = dir; //направление полета пули 
	Speed = 6;
	w = W;
	h = H;//размеры изображения пули 
	Life = true; //пуля жива
	sprite.setTextureRect(IntRect(88, 3, w, h));

};




void Bullet::update(float time)
{

	switch (direction)
	{
	case 0:
	{
		dx = -Speed;
		dy = 0;
		break;
	} //     state = left 
	case 1:
	{
		dx = Speed;
		dy = 0;
		break;
	} //       state = right 
	case 2:
	{
		dx = 0;
		dy = -Speed;
		break;
	} //       state = up 
	case 3:
	{
		dx = 0;
		dy = Speed;
		break;
	}//       tate = down 
	}
	if (Life)
	{ // если пуля жива 
		x += dx * 0.1*time;//само движение пули по х
		y += dy * 0.1*time;//по у
		for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты 
			for (int j = x / 32; j < (x + w) / 32; j++)
			{
				if (TileMap[i][j] == '1')
				{
					Life = false;// то пуля умирает 
				}
				sprite.setPosition(x + w, y + h);
			}
	}      //задается позицию пули 
};

void  Bullet::interactionWithMap(float Dx, float Dy)
{
	Life = false;
};
