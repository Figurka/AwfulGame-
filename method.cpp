#pragma once // ��������� ���������� ������ 1 ���. �� ����������� ����������.��������� VS
#include <iostream> 
#include <SFML\Graphics.hpp>
#include "Class.h"
#include "map.h"
using namespace sf;

//////////Enemy//////////
Enemy::Enemy(Image &image, float X, float Y, int W, int H, std::string Name) :Smth(image, X, Y, W, H, Name)
{
	if (name == "EasyEnemy")
	{
		direction = rand() % (4); //����������� �������� ����� ����� ��������� ������� //����� ��������� ��������� �����
		Speed = 0.1;//���� ��������.���� ������ ������ ��������� 
		dx = Speed;
	}
}


void Enemy::interactionWithMap(float Dx, float Dy)//�-��� �������� ������������ � ������
{

};

void Enemy::update(float time)
{

};