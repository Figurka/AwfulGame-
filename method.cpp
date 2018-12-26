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