#pragma once
#include <SFML/Graphics.hpp>
#include <iostream> 
#include "map.h"
#include "Class.h"
#include <SFML/Audio.hpp>
#include <list>
#include <sstream> 
using namespace sf;

int main()
{


	RenderWindow window(sf::VideoMode(1600, 928), "awful game", sf::Style::Resize);
	window.setFramerateLimit(60);


	Image heroImage;
	heroImage.loadFromFile("Image/sailor.png");
	heroImage.createMaskFromColor(Color(255, 255, 255));
	Player p(heroImage, 250, 250, 20, 40, "Player1");


	std::list<Smth*> enemies; //список врагов 
	std::list<Smth*> Bullets; //список пуль 
	std::list<Smth*>::iterator it; //итератор чтобы проходить по элементам списка
	std::list<Smth*>::iterator it2;

	Image EnemImage;
	EnemImage.loadFromFile("Image/sailorenemy.png");
	EnemImage.createMaskFromColor(Color(255, 255, 255));

	Image map_imagee;//?????????? ?? ???
	map_imagee.loadFromFile("Image/juh.png");//??????? ?? ???
	Texture mapp;//???? ???
	mapp.loadFromImage(map_imagee);//???? ???? ?????
	Sprite j_map;//??? ??? ?? ???
	j_map.setTexture(mapp);//???? ???? ????

	float CurrentFrame = 0;
	Clock clock;
	Clock gameTimeClock;//????? ???? ???? ?????? ???? ??? ?? 
	int gameTime = 0;//????? ???????, ????????.
	int em = 0;



	const int enemy = 5; //максимальное количество врагов в игре 
	int enemiescount = 0;
	p.Health = 100;




	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		if (p.Health) {
			gameTime = gameTimeClock.getElapsedTime().asSeconds();
		}

		clock.restart();
		time = time / 800;

		sf::Event event;

		for (enemiescount; enemiescount < enemy; enemiescount++)
		{
			float xr = 150 + rand() % 500; // случайная координата врага на поле игры по оси “x”
			float yr = 150 + rand() % 350; // случайная координата врага на поле игры по оси “y”
			enemies.push_back(new Enemy(EnemImage, xr, yr, 20, 32, "EasyEnemy"));	//увеличили счётчик врагов		
		}


		if (em >= enemy) { enemiescount = 0; em = 0; }



		for (it = enemies.begin(); it != enemies.end();)//говорим что проходимся от начала до конца
		{
			Smth *b = *it;//для удобства, чтобы не писать (*it)->
			b->update(time);//вызываем ф-цию update для всех объектов (по сути для тех, кто жив)
			if (b->Life == false) { it = enemies.erase(it); delete b; }// если этот объект мертв, то удаляем его
			else it++;//и идем курсором (итератором) к след объекту. так делаем со всеми объектами списка
		}

		window.clear();

		/////////////////////////////Map////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == '1') {
					j_map.setTextureRect(sf::IntRect(0, 0, 32, 32)); //?? ???????? ???, ? ??? 1??????
					j_map.setPosition(j * 32, i * 32);
				};//? ?? ?????? ?????, ????? ???? ? ?? ??? ????? ?? ????. ?? ???, ? ?? ???????? ???????? 32*32 ?? ??? ?? ????
				if (TileMap[i][j] == '0') {
					j_map.setTextureRect(sf::IntRect(33, 0, 32, 32)); //?? ???????? ???, ? ??? 1??????
					j_map.setPosition(j * 32, i * 32);
				};
				if (TileMap[i][j] == ' ') {
					j_map.setTextureRect(sf::IntRect(66, 0, 32, 32)); //?? ???????? ???, ? ??? 1??????
					j_map.setPosition(j * 32, i * 32);
				};
				if (TileMap[i][j] == '2') {
					j_map.setTextureRect(sf::IntRect(99, 0, 32, 32)); //?? ???????? ???, ? ??? 1??????
					j_map.setPosition(j * 32, i * 32);
				};
				if (TileMap[i][j] == '4') {
					j_map.setTextureRect(sf::IntRect(133, 0, 64, 64)); //?? ???????? ???, ? ??? 1??????
					j_map.setPosition(j * 32, i * 32);
				};
				if (TileMap[i][j] == '5') {
					j_map.setTextureRect(sf::IntRect(0, 33, 32, 32)); //?? ???????? ???, ? ??? 1??????
					j_map.setPosition(j * 32, i * 32);
				};
				window.draw(j_map);
			}



		p.update(time);
		window.draw(p.sprite);
		//отрисовка врагов
		for (it = enemies.begin(); it != enemies.end(); it++) {
			window.draw((*it)->sprite); //рисуем enemies объекты


		}

		window.display();
	}

	return 0;
}