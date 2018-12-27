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
  ///////////////////////////////////////////Управление персонажем с анимацией////////////////////////////////////////////////////////////////////////
  void Player::control() {

	  if (Keyboard::isKeyPressed(Keyboard::A))
	  {
		  state = left; Speed = 0.1;
	  }
	  if (Keyboard::isKeyPressed(Keyboard::D))
	  {
		  state = right; Speed = 0.1;
	  }
	  if (Keyboard::isKeyPressed(Keyboard::W))
	  {
		  state = up; Speed = 0.1;
	  }
	  if (Keyboard::isKeyPressed(Keyboard::S))
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
				  if (CurrentFrame > 2) CurrentFrame -= 2;
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