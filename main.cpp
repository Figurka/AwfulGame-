#pragma once
#include <SFML/Graphics.hpp>
#include <iostream> 
#include "map.h"
#include "menu.h"
#include "Class.h"
#include <SFML/Audio.hpp>
#include <list>
#include <sstream> 
using namespace sf;

int main()
{
	Music music;//создаем объект музыки
	music.openFromFile("Music/ap.flac");//загружаем файл
	music.play();//воспроизводим музыку
	music.setVolume(20);

	SoundBuffer deathp;//создаём буфер для звука
	deathp.loadFromFile("Music/sc.flac");//загружаем в него звук
	Sound death(deathp);//создаем звук и загружаем в него звук из буфера
	death.setVolume(20);

	SoundBuffer shootp;//создаём буфер для звука
	shootp.loadFromFile("Music/shoot1.flac");//загружаем в него звук
	Sound shoot(shootp);//создаем звук и загружаем в него звук из буфера

	Font font;//шрифт 
	font.loadFromFile("nove.ttf");//передаем нашему шрифту файл шрифта
	Text text("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	text.setColor(Color::White);

	RenderWindow window(sf::VideoMode(1600, 928), "awful game", sf::Style::Resize);
	window.setFramerateLimit(60);
	while (true) {

		if (menu(window)) break;

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
	Enemy enem(EnemImage, 250, 250, 20, 40, "EasyEnemy");

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
		p.update(time);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) { window.close(); }
			if (event.type == sf::Event::KeyPressed) //shoot
			{
				if (event.key.code == sf::Keyboard::P)
				{
					Bullets.push_back(new Bullet(heroImage, p.x, p.y, 16, 16, "Bullet1", p.state));
					shoot.play();

				}

			}

		}


		for (it = Bullets.begin(); it != Bullets.end(); it++)
		{
			(*it)->update(time); //запускаем метод update() 
		}

		//Проверяем список на наличие "мертвых" пуль и удаляем их 
		for (it = Bullets.begin(); it != Bullets.end(); )//говорим что проходимся от начала до конца 
		{// если этот объект мертв, то удаляем его 
			if ((*it)->Life == false)
			{
				delete (*it);
				it = Bullets.erase(it);
			}
			else { it++; }//и идем курсором (итератором) к след объекту. 
		} //Проверка пересечения игрок


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
			if (b->Life == false) { it = enemies.erase(it); delete b; death.play(); }// если этот объект мертв, то удаляем его
			else it++;//и идем курсором (итератором) к след объекту. так делаем со всеми объектами списка
		}


		for (it2 = Bullets.begin(); it2 != Bullets.end(); it2++)
		{//проходимся по эл-там списка

			for (it = enemies.begin(); it != enemies.end(); it++)//проходимся по эл-там списка
			{
				if ((*it)->getRect() != (*it2)->getRect())//при этом это должны быть разные прямоугольники

					if (((*it)->getRect().intersects((*it2)->getRect())) && ((*it)->name == "EasyEnemy") && ((*it2)->name == "Bullet1"))
					{
						(*it2)->Life = false;
						(*it)->Health = 0;
						p.playerScore += 20;
						em += 1;
					}

			}
		}
		for (it = Bullets.begin(); it != Bullets.end(); it++)
		{//проходимся по эл-там списка				
			if ((*it)->getRect() != p.getRect())//при этом это должны быть разные прямоугольники
				if ((*it)->getRect().intersects(p.getRect()) && ((*it)->name == "Bullet"))
				{
					(*it)->Life = false;
					p.Health -= 10;
				}


		}







		for (it = enemies.begin(); it != enemies.end(); it++)//проходимся по эл-там списка
		{
			if ((*it)->getRect().intersects(p.getRect()))//если прямоугольник спрайта объекта пересекается с игроком
			{


				if ((*it)->name == "EasyEnemy") {//и при этом имя объекта EasyEnemy,то..
					(*it)->Life = false;
					p.playerScore -= 10;
					em += 1;

				}

			}
		}




		for (it = enemies.begin(); it != enemies.end(); it++) {
			if ((*it)->name == "EasyEnemy") {
				(*it)->update(time); //запускаем метод update()

				int ran;
				ran = rand() % (4);
				if (!((int)time % 20)) { Bullets.push_back(new Bullet(heroImage, ((*it)->x) + 5, (*it)->y, 16, 16, "Bullet", (*it)->direction)); }
			}
		}

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

			//отрисовка времени
			std::ostringstream gameTimeString, scoregame, healthplay;    // объявили переменную здоровья и времени
			gameTimeString << gameTime; scoregame << p.playerScore;	healthplay << p.Health;	//формируем строку
			text.setString("\nTime: " + gameTimeString.str() + "\nScore:" + scoregame.str() + "\nHealth:" + healthplay.str());//задаем строку тексту и вызываем сформированную выше строку методом .str()
			text.setPosition(1500, 50);//задаем позицию текста, отступая от центра камеры
			window.draw(text);//рисую этот текст



		p.update(time);
		window.draw(p.sprite);
		//отрисовка врагов
		p.update(time);
		window.draw(p.sprite);
		//отрисовка врагов
		for (it = enemies.begin(); it != enemies.end(); it++) {
			window.draw((*it)->sprite); //рисуем enemies объекты
		}

		//Отрисовка пуль
		for (it = Bullets.begin(); it != Bullets.end(); it++)
		{
			if ((*it)->Life); //если пули живы 
			{
				window.draw((*it)->sprite);
			} //рисуем объекты 
		}


		if (p.Life == false) { break; }
		window.display();
		}
	}

	return 0;
}