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


		std::list<Smth*> enemies; //������ ������ 
		std::list<Smth*> Bullets; //������ ���� 
		std::list<Smth*>::iterator it; //�������� ����� ��������� �� ��������� ������
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



		const int enemy = 5; //������������ ���������� ������ � ���� 
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
					
					}

				}

			}
			for (it = Bullets.begin(); it != Bullets.end(); it++)
			{
				(*it)->update(time); //��������� ����� update() 
			}

			//��������� ������ �� ������� "�������" ���� � ������� �� 
			for (it = Bullets.begin(); it != Bullets.end(); )//������� ��� ���������� �� ������ �� ����� 
			{// ���� ���� ������ �����, �� ������� ��� 
				if ((*it)->Life == false)
				{
					delete (*it);
					it = Bullets.erase(it);
				}
				else { it++; }//� ���� �������� (����������) � ���� �������. 
			} //�������� ����������� �����



		
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
			//��������� ����
			for (it = Bullets.begin(); it != Bullets.end(); it++)
			{
				if ((*it)->Life); //���� ���� ���� 
				{
					window.draw((*it)->sprite);
				} //������ ������� 
			}
		

			p.update(time);
			window.draw(p.sprite);
		

		

			window.display();
	}

	return 0;
}