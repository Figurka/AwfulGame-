#pragma once // Включение происходит только 1 раз. не стандартная дирректива.предложил VS
#include <iostream> 
#include <SFML\Graphics.hpp>
#include "Class.h"
#include "map.h"
using namespace sf;



//конструктор класса smth
	Smth:: Smth(Image &image, float X, float Y, int W, int H, std::string Name)
	{
		x = X;//Координаты x,y
		y = Y;
		w = W;//ширина и высота
		h = H;
		name = Name;//имя файла
		Speed = 0;//скорость
		Health = 100; //здоровье
		dx = 0; 
		dy = 0;
		Life = true;//жизни
		texture.loadFromImage(image); //заносим наше изображение в текстуру 
	 	sprite.setTexture(texture); //заливаем спрайт текстурой
	};
	//функция для проверки пересечения котоырая возвращает координаты
	FloatRect Smth::getRect()
	{ 
		FloatRect  FR ( x, y, w, h);
		return FR;  
	};



//конструктор класса Player
	Player:: Player(Image &image, float X, float Y, int W, int H, std::string Name) :Smth(image, X, Y, W, H, Name)  
  { 
		Player:: playerScore = 0;
		 state = stay;
    if (Name == "Player1")
      { 
       //Задаем спрайту один прямоугольник для //вывода одного игрока.IntRect – для приведения типов 
         sprite.setTextureRect(IntRect(0,40, w, h)); 
      }
	};

	void Player::interactionWithMap(float Dx,float Dy )//ф-ция взаимодействия с картой
	{

		 for (int i = y / 32; i < (y + h) / 32; i++)
    //проходимся по элементам карты
      for (int j = x / 32; j<(x + w) / 32; j++) 
      {
		  //если встречаем кота теряем очки, но получаем жизни
        if (TileMap[i][j] == '5'){
          TileMap[i][j] =' ';
		  Health += 10;
		  playerScore -= 10;

        }

         if (TileMap[i][j] == '1')//если элемент - тайлик земли 
         { 

				   if (Dy > 0) //проверка столкновения вниз
				   {
					 y = i * 32 - h; dy = -0.1; 
                
					}
                    if (Dy < 0) //вверх
                    {
                     y = i * 32 + 32; 
                     dy = 0.1;
               
                      }
                      if (Dx > 0)//вправо
                      { 
                        x = j * 32 - w;
					  dx = -0.1;
                      
                      }
                      if (Dx < 0) //влево
                      {
                       x = j * 32 + 32; 
                       dx = 0.1; 
                        //Направление движения врага
                      }
				
                    } 
               }
              };
  ///////////////////////////////////////////Управление персонажем с анимацией////////////////////////////////////////////////////////////////////////
  void Player::control() {

	  if (Keyboard::isKeyPressed(Keyboard::Left))
	  {
		  state = left; Speed = 0.1;
	  }
	  if (Keyboard::isKeyPressed(Keyboard::Right))
	  {
		  state = right; Speed = 0.1;
	  }
	  if (Keyboard::isKeyPressed(Keyboard::Up))
	  {
		  state = up; Speed = 0.1;
	  }
	  if (Keyboard::isKeyPressed(Keyboard::Down))
	  {
		  state = down; Speed = 0.1;
	  }
  };
	 void Player::update(float time) //метод "оживления/обновления" объекта класса.
	  {
		  if (Life)
		  {//проверяем, жив ли герой 
			  control();//функция управления персонажем 
			  switch (state)//делаются различные действия в зависимости от состояния 
			  {
			  case right:
			  {//состояние идти вправо
				  dx = Speed;
          dy =0;
           CurrentFrame += 0.005*time;
				  if (CurrentFrame > 2) CurrentFrame -= 2;//анимация
				 sprite.setTextureRect(IntRect(21*int(CurrentFrame), 80, 20, 40));
				  break;
			  }
			  case left:
			  {//состояние идти влево
				  dx = -Speed; 
          dy=0;
          CurrentFrame += 0.005*time;
				  if (CurrentFrame > 2) CurrentFrame -= 2;
				  sprite.setTextureRect(IntRect(21 * int(CurrentFrame), 40, 20, 40));
				  break;
			  } 
			  case up: {
				  //идти вверх 
				  dy = -Speed; 
				   dx=0;
				  CurrentFrame += 0.005*time;
				  if (CurrentFrame > 2) CurrentFrame -= 2;
				  sprite.setTextureRect(IntRect(21 * int(CurrentFrame), 120, 20, 40));
				  break; }
			  case down:
			  {//идти вниз 
				  dy = Speed; 
				 dx=0;
          CurrentFrame += 0.005*time;
				  if (CurrentFrame > 2) CurrentFrame -= 2;
				  sprite.setTextureRect(IntRect(21 * int(CurrentFrame), 0, 20, 40));
				  break; }
			  case stay: {
				  //стоим 
				  dy = Speed; 
				  dx = Speed;
				  sprite.setTextureRect(IntRect(21 * int(CurrentFrame), 0, 20, 40));
				  break;
							}
			  } 
			  x += dx*time; //движение по “X”
			  interactionWithMap(dx, 0); //обрабатываем столкновение по 
				y += dy*time; //движение по “Y”
				interactionWithMap(0, dy); //обрабатываем столкновение по Y 
			   Speed = 0; //обнуляем скорость, чтобы персонаж остановился. 
				//state = stay;/////////////////////////////////////////////////////////////завтра поправлю или сам поправь, но надо чтоб было состояние куда пуле лететь
			  sprite.setPosition(x, y); //спрайт в позиции (x, y).
			  if (Health <= 0)
			  {
				 Life = false;
			  }//если жизней меньше 0, либо равно 0, то умираем 
		  }
	  }
  ;