#pragma once // Включение происходит только 1 раз. не стандартная дирректива.предложил VS
#include <iostream> 
#include <SFML\Graphics.hpp>
#include "Class.h"

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
