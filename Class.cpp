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
	for (int i = y / 32; i < (y + h) / 32; i++)
    //проходимся по элементам карты
		for (int j = x / 32; j<(x + w) / 32; j++) 
		{

			if (TileMap[i][j] == '5'){
				TileMap[i][j] =' ';
				Health += 10;
				playerScore -= 10;

			}

         if (TileMap[i][j] == '1')//если элемент - тайлик земли 
         { 
         	if (Dy > 0) 
         	{
         		y = i * 32 - h; dy = -0.1; 
                 //Направление движения врага 
                    }//по Y
                    if (Dy < 0) 
                    {
                    	y = i * 32 + 32; 
                    	dy = 0.1;
                  		//Направление движения врага 
                      }//столкновение с верхними краями
                      if (Dx > 0)
                      { 
                      	x = j * 32 - w;
                      	dx = -0.1;
                       //Направление движения врага 
                      }//с правым краем карты 
                      if (Dx < 0) 
                      {
                      	x = j * 32 + 32; 
                      	dx = 0.1; 
                        //Направление движения врага
                      }// с левым краем карты 

                  } 
              }
              
          };
void Player::control() 
{	 
};
void Player::update(float time) //метод "оживления/обновления" объекта класса.
{
};