#include <SFML/Window.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "UFO");

	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	
	sf::Texture Background;
	Background.loadFromFile("spacebackground.jpeg");
	Background.setSmooth(true);
	sf::Sprite bgImage;
	bgImage.setTexture(Background,true);
	window.draw(bgImage);
	
	sf::Texture UFO;
    UFO.loadFromFile("spaceship.png");
    if (!UFO.loadFromFile("spaceship.png"))
	{
		cout<<"WTF?"<<endl;
	}
	UFO.setSmooth(true);
	sf::Sprite UFOdrew;
	UFOdrew.setTexture(UFO,true);
	window.draw(UFOdrew);
	UFOdrew.setColor(sf::Color(255, 255, 255));
	UFOdrew.setOrigin(130,167);
	
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			UFOdrew.move(-5, 0);
		}
	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			UFOdrew.move(5, 0);
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			UFOdrew.move(0, 5);
		}
	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			UFOdrew.move(0, -5);
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			UFOdrew.rotate(10);
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			UFOdrew.rotate(-10);
		}
		
		window.display();
	}
    
    return 0;
}
