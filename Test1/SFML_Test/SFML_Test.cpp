#include "pch.h"//Include del encabezado precompilado o el precompiled header
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include "Personaje.h"
#include "Plataforma.h"

using namespace std; //Uso el namespace sf para no poner sf:: todo el tiempo
using namespace sf;

bool collide(Sprite &spr, RectangleShape &rect)
{
	return spr.getGlobalBounds().intersects(rect.getGlobalBounds());

}

int main() //Funcion main o principal
{
	//Declaracion de variables
	int width, height;
	float divide;
	Clock clock;

	//Inicializacion de variables
	width = 900;
	height = 900;

	//Variables de personaje
	bool esSaltando = true;
	int AlturaPiso = 700;
	float Gravedad = 0.2, velMovimiento = 0.5, velSalto = 3;
	Vector2f velocidad(Vector2f(0, 0));

	RenderWindow window; //Objeto ventana ventana
	Vector2i centerWindow((VideoMode::getDesktopMode().width / 2) - 445, (VideoMode::getDesktopMode().height / 2) - 445);
	window.create(VideoMode(width, height), "SFML Prueba", Style::Titlebar | Style::Close);
	//window.setPosition(centerWindow);
	window.setKeyRepeatEnabled(true);
	window.setFramerateLimit(60);

	Plataforma platform;
	platform.setPosition(Vector2f(0, 600));

	Personaje jugador("Imgs/Skelly_test_big.png");
	jugador.setPosition({ 400,400 });

	RectangleShape fondopj(Vector2f(jugador.getSizeX(), jugador.getSizeY()));
	fondopj.setFillColor(Color::Blue);

	RectangleShape floor(Vector2f(900, 200));
	floor.setPosition(0, AlturaPiso);
	floor.setFillColor(Color::Black);



	while (window.isOpen()) //Loop donde van a transcurrir las acciones del juego
	{
		Event event; //Creacion del objeto evento
		fondopj.setPosition(jugador.getPosition());

		//Reloj
		Time time = clock.getElapsedTime();
		int deltaTime = time.asMilliseconds();

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			velocidad.x = velMovimiento;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			velocidad.x = -velMovimiento;
		}
		else
		{
			velocidad.x = 0;
		}

		if (Keyboard::isKeyPressed(Keyboard::Up) && esSaltando)
		{
			velocidad.y = -velSalto;
			esSaltando = false;

		}

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed:
				if (event.key.code == Keyboard::Escape) {
					window.close();
					return EXIT_SUCCESS;
				}
			}
		}

		//Logica de la gravedad
		if ((jugador.getY() + jugador.getSizeY()) < AlturaPiso || (velocidad.y < 0) && (!esSaltando))
		{
			velocidad.y += Gravedad;
		}
		else
		{
			jugador.setPosition(Vector2f(jugador.getPosition().x, AlturaPiso - jugador.getSizeY()));
			velocidad.y = 0;
			esSaltando = true;
		}

		//Colisiones
		Sprite sprCol = jugador.getSpr();
		RectangleShape rectCol = platform.getRect();
		bool isColision = collide(sprCol, rectCol);
		if (isColision)
		{
			cout << "Colisiona \n";
			velocidad.y -= velocidad.y;

		}
		else
		{
			cout << "No colisiona \n";
		}

		//Colision Piso

		//bool colPiso = collide(sprCol, floor);
		//if(colPiso)
		//{
		//}

		jugador.move(Vector2f(velocidad.x * deltaTime, velocidad.y * deltaTime));
		clock.restart().asMilliseconds();
		window.clear(Color::White); //Limpia la pantalla
		//Aqui debajo se dibujan los objetos en el juego
		window.draw(floor);
		window.draw(fondopj);

		platform.draw(window);
		jugador.draw(window);
		window.display(); //Muestra por pantalla
	} //Fin loop del juego
	return EXIT_SUCCESS;
}

