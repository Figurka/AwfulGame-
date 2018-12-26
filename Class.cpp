#pragma once // Включение происходит только 1 раз. не стандартная дирректива.предложил VS
#include <iostream> 
#include <SFML\Graphics.hpp>
#include "Class.h"
#include "map.h"
using namespace sf;



//////////MainClass//////////
	Smth:: Smth(Image &image, float X, float Y, int W, int H, std::string Name)
	{
		x = X;
		y = Y;
		w = W; h = H;
		name = Name;
		MoveTimer = 0;
		Speed = 0;
		Health = 100; 
		dx = 0; 
		dy = 0;
		Life = true;
		texture.loadFromImage(image); //заносим наше изображение в текстуру 
	 	sprite.setTexture(texture); //заливаем спрайт текстурой
	};

	FloatRect Smth::getRect()
	{ 
		FloatRect  FR ( x, y, w, h);
		return FR;  
	};



//////////Player//////////
Player:: Player(Image &image, float X, float Y, int W, int H, std::string Name) :Smth(image, X, Y, W, H, Name)  //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
{ 
	Player:: playerScore = 0;
	state = stay;
    
};
  ///////////////////////////////////////////Управление персонажем с анимацией////////////////////////////////////////////////////////////////////////
void Player::interactionWithMap(float Dx,float Dy )//ф-ция взаимодействия с картой
{

};
void Player::control() 
{	 
};
void Player::update(float time) //метод "оживления/обновления" объекта класса.
{
};