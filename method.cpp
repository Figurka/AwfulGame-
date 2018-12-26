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

//////////Bullet//////////
Bullet::Bullet(Image &image, float X, float Y, int W, int H, std::string Name, int dir) :Smth(image, X, Y, W, H, Name)
{
	x = X; //���������� ���� �� ����� ����
	y = Y;
	direction = dir; //����������� ������ ���� 
	Speed = 6;
	w = W;
	h = H;//������� ����������� ���� 
	Life = true; //���� ����
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
	{ // ���� ���� ���� 
		x += dx * 0.1*time;//���� �������� ���� �� �
		y += dy * 0.1*time;//�� �
		for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������� ����� 
			for (int j = x / 32; j < (x + w) / 32; j++)
			{
				if (TileMap[i][j] == '1')
				{
					Life = false;// �� ���� ������� 
				}
				sprite.setPosition(x + w, y + h);
			}
	}      //�������� ������� ���� 
};

void  Bullet::interactionWithMap(float Dx, float Dy)
{
	Life = false;
};
