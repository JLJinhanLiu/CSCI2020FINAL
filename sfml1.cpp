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
	if (!Background.loadFromFile("spacebackground.jpeg"))
	{
		cout<<"background_LOAD_FAILED"<<endl;
	}
	Background.setSmooth(true);
	sf::Sprite bgImage;
	bgImage.setTexture(Background,true);
	
	sf::Texture UFO;
    UFO.loadFromFile("ship.png");
    if (!UFO.loadFromFile("ship.png"))
	{
		cout<<"SHIP_LOAD_FAIL"<<endl;
	}
	UFO.setSmooth(true);
	sf::Sprite UFOdrew;
	UFOdrew.setTexture(UFO,true);
	window.draw(UFOdrew);
	UFOdrew.setOrigin(100,100);
	UFOdrew.scale(0.25f, 0.25f);
	
	while (window.isOpen())
	{
		
		sf::Event windowopen;
		while (window.pollEvent(windowopen))
		{
			if (windowopen.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear(sf::Color::White);
        window.draw(bgImage);
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
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			UFOdrew.rotate(5);
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			UFOdrew.rotate(-5);
		}
		
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		//{
			
		//}
		
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		//{
			
		//}
		
		
		window.display();
	}
    
    return 0;
}
