#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
using namespace std; 
using namespace sf; //Uso el namespace sf para no poner sf:: todo el tiempo

class Personaje
{
public:
	//Constructor
	Personaje(string dir)
	{
		if(!pTexture.loadFromFile(dir))
		{
			cerr << "Error \n";
		}
		pTexture.setSmooth(true);
		pSprite.setTexture(pTexture);
		pSprite.setTextureRect(IntRect(0, 0, 704, 1088));
		pSprite.setScale(escala, escala);

	}
	//Destructor
	~Personaje()
	{
	}

	//Set
	void setPosition(Vector2f newPos)
	{
		pSprite.setPosition(newPos);
	}

	void draw(RenderWindow &window)
	{
		window.draw(pSprite);
	}

	void move(Vector2f distance)
	{
		pSprite.move(distance);
	}

	//Get
	Vector2f getPosition() 
	{
		return pSprite.getPosition();
	}

	Sprite getSpr()
	{
		return pSprite;
	}

	float getY()
	{
		return pSprite.getPosition().y;
	}

	float getX()
	{
		return pSprite.getPosition().x;
	}

	float getSizeY()
	{
		return pSprite.getGlobalBounds().height;
	}

	float getSizeX()
	{
		return pSprite.getGlobalBounds().width;
	}

private:
	Texture pTexture; //Textura del personaje
	Sprite pSprite; //Sprite del personaje
	float escala = float(0.1);
};