#pragma once // Âêëþ÷åíèå ïðîèñõîäèò òîëüêî 1 ðàç. íå ñòàíäàðòíàÿ äèððåêòèâà.ïðåäëîæèë VS
#include <iostream> 
#include <SFML\Graphics.hpp>
#include "Class.h"
#include "map.h"
using namespace sf;

//////////Enemy//////////
Enemy::Enemy(Image &image, float X, float Y, int W, int H, std::string Name) :Smth(image, X, Y, W, H, Name)
{
	 if (name == "EasyEnemy")
         { //Задаем спрайту один прямоугольник для //вывода одного игрока. IntRect – для приведения типов 
         sprite.setTextureRect(IntRect(100, 6, w, h)); 
         direction = rand() % (4); //Направление движения врага задаём случайным образом //через генератор случайных чисел
         Speed = 0.1;//даем скорость.этот объект всегда двигается 
          dx = Speed; 
          }
};


void Enemy::interactionWithMap(float Dx, float Dy)//ô-öèÿ ïðîâåðêè ñòîëêíîâåíèé ñ êàðòîé
{
	for (int i = y / 32; i < (y + h) / 32; i++)
    //проходимся по элементам карты
      for (int j = x / 32; j<(x + w) / 32; j++) 
      {
         if (TileMap[i][j] == '1')//если элемент - тайлик земли 
         { 
           if (Dy > 0) 
           {
             y = i * 32 -40; dy = -0.1; 
                 direction = rand() % (4); //Направление движения врага 
                    }//по Y
                    if (Dy < 0) 
                    {
                     y = i * 32 +32; 
                     dy = 0.1;
                  direction = rand() % (4);//Направление движения врага 
                      }//столкновение с верхними краями
                      if (Dx > 0)
                      { 
                        x = j * 32-20;
						            dx = -0.1;
                       direction = rand() % (4);//Направление движения врага 
                      }//с правым краем карты 
                      if (Dx < 0) 
                      {
                       x = j * 32 + 32; 
                       dx = 0.1; 
                       direction = rand() % (4); //Направление движения врага
                      }// с левым краем карты 
                    } 
               }
};

void Enemy::update(float time)
{
	if (name == "EasyEnemy")
  {
      //для персонажа с таким именем логика будет такой 
      if (Life) {//проверяем, жив ли герой 
		  switch (direction)//делаются различные действия в зависимости от состояния
		  {
		  case 0: {//состояние идти вправо 
			  dx = Speed;
			  dy = 0;
			  CurrentFrame += 0.005*time;
			  if (CurrentFrame > 3) CurrentFrame -= 3;
			  sprite.setTextureRect(IntRect(19 * int(CurrentFrame), 120, 19, 38));
			  break; }
		  case 1: {//состояние идти влево
			  dx = -Speed;
			  dy = 0;
			  CurrentFrame += 0.005*time;
			  if (CurrentFrame > 3) CurrentFrame -= 3;
			  sprite.setTextureRect(IntRect(19 * int(CurrentFrame), 40, 19, 38));
			  break; }
		  case 2: {//идти вверх
			  dy = -Speed;
			  dx = 0; CurrentFrame += 0.005*time;
			  if (CurrentFrame > 3) CurrentFrame -= 3;
			  sprite.setTextureRect(IntRect(19 * int(CurrentFrame), 80, 19, 38));
			  break; }
		  case 3: {//идти вниз
			  dy = Speed;
			  dx = 0; CurrentFrame += 0.005*time;
			  if (CurrentFrame > 3) CurrentFrame -= 3;
			  sprite.setTextureRect(IntRect(19 * int(CurrentFrame), 0, 19, 38));
			  break; }
		  case 4: {//идти вниз
			  num = 0;
				  break;
		  }
		  }

                x += dx*time/3; 
                  //движение по “X” 
				interactionWithMap(dx, 0);//обрабатываем столкновение по Х

y += dy*time/3; //движение по “Y” 

interactionWithMap(0, dy);//обрабатываем столкновение по Y 
sprite.setPosition(x, y); //спрайт в позиции (x, y).
 if (Health <= 0){ Life = false; }//если жизней меньше 0, либо равно 0, то умираем 
} 
} 

};

//////////Bullet//////////
Bullet::Bullet(Image &image, float X, float Y, int W, int H, std::string Name, int dir) :Smth(image, X, Y, W, H, Name)
{
	x = X; //êîîðäèíàòû ïóëè íà êàðòå èãðû
	y = Y;
	direction = dir; //íàïðàâëåíèå ïîëåòà ïóëè 
	Speed = 6;
	w = W;
	h = H;//ðàçìåðû èçîáðàæåíèÿ ïóëè 
	Life = true; //ïóëÿ æèâà
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
	{ // åñëè ïóëÿ æèâà 
		x += dx * 0.1*time;//ñàìî äâèæåíèå ïóëè ïî õ
		y += dy * 0.1*time;//ïî ó
		for (int i = y / 32; i < (y + h) / 32; i++)//ïðîõîäèìñÿ ïî ýëåìåíòàì êàðòû 
			for (int j = x / 32; j < (x + w) / 32; j++)
			{
				if (TileMap[i][j] == '1')
				{
					Life = false;// òî ïóëÿ óìèðàåò 
				}
				sprite.setPosition(x + w, y + h);
			}
	}      //çàäàåòñÿ ïîçèöèþ ïóëè 
};

void  Bullet::interactionWithMap(float Dx, float Dy)
{
	Life = false;
};
