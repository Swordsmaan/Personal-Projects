#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
using namespace std;
using namespace sf; //Uso el namespace sf para no poner sf:: todo el tiempo

class Plataforma
{
public:
	//Constructor
	Plataforma()
	{
		plat.setSize(Vector2f(200, 50));
		plat.setFillColor(Color::Green);

	}
	~Plataforma()
	{
	}

	//Set
	void setPosition(Vector2f newpos)
	{
		plat.setPosition(newpos);
	}
	void draw(RenderWindow &window)
	{
		window.draw(plat);
	}

	//Get
	Vector2f getPosition()
	{
		return plat.getPosition();
	}

	RectangleShape getRect()
	{
		return plat;
	}

private:
	RectangleShape plat;
};