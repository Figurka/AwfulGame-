#pragma once
#include <SFML/Graphics.hpp>
#include <iostream> 
#include "map.h"
#include "Class.h"
#include <sstream> 
bool menu(RenderWindow & window) {
	Image ImNew, ImExit;
	ImNew.loadFromFile("Image/Newgame.png");
	ImExit.loadFromFile("Image/exit.png");
	ImNew.createMaskFromColor(Color(255, 255, 255));
	ImExit.createMaskFromColor(Color(255, 255, 255));

	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;


	menuTexture1.loadFromImage(ImNew);
	menuTexture2.loadFromImage(ImExit);
	menuBackground.loadFromFile("Image/sai.jpg");
	Sprite menu1(menuTexture1), menu2(menuTexture2), about(aboutTexture), menuBg(menuBackground);

	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(50, 450);
	menu2.setPosition(50, 650);
	menuBg.setPosition(0, 0);
	//////////////////////////////МЕНЮ///////////////////
	while (isMenu)
	{


		menuNum = 0;
		window.clear(Color(255, 255, 255));

		if (IntRect(50, 450, 100, 70).contains(Mouse::getPosition(window))) { menuNum = 1; }
		if (IntRect(50, 650, 100, 70).contains(Mouse::getPosition(window))) { menuNum = 2; }
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) { return false; }//если нажали первую кнопку, то выходим из меню 
			if (menuNum == 2) { window.close(); return true; }
		}
		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.display();
	}
	////////////////////////////////////////////////////
}