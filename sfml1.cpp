#include <SFML/Window.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "UFO");

	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	
	sf::Texture UFO;
    UFO.loadFromFile("ufo.png");
    if (!UFO.loadFromFile("ufo.png"))
	{
		cout<<"WTF?"<<endl;
	}
	UFO.setSmooth(true);
	sf::Sprite UFOdrew;
	UFOdrew.setTexture(UFO,true);
	window.draw(UFOdrew);
	UFOdrew.setColor(sf::Color(255, 255, 255));
	//UFOdrew.setOrigin(sf::Vector2f(25, 25));
	while (window.isOpen())
	{
		sf::Event windowopen;
		while (window.pollEvent(windowopen))
		{
			if (windowopen.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);
        window.draw(UFOdrew);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			UFOdrew.move(-5, 0);
		}
	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			UFOdrew.move(5, 0);
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			UFOdrew.move(0, 5);
		}
	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			UFOdrew.move(0, -5);
		}
		window.display();
	}
    
    return 0;
}
