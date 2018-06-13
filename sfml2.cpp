#include <SFML/Window.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;




int main()
{	

	//buildWINDOW
	sf::RenderWindow window(sf::VideoMode(800, 600), "UFO");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);


	//importBACKGROUND
	sf::Texture Background;
	if (!Background.loadFromFile("spacebackground.jpeg"))
		cout<<"background_LOAD_FAILED"<<endl;
	Background.setSmooth(true);
	sf::Sprite bgImage;
	bgImage.setTexture(Background,true);

	//importSHIP
	sf::Texture UFO;
  if (!UFO.loadFromFile("ship.png"))
		cout<<"SHIP_LOAD_FAIL"<<endl;
	UFO.setSmooth(true);
	sf::Sprite UFOdrew;
	UFOdrew.setTexture(UFO,true);
	window.draw(UFOdrew);
	UFOdrew.setOrigin(500,500);
	UFOdrew.scale(0.05f, 0.05f);
	UFOdrew.setPosition(400,585);

	//importBullet
	sf::Texture ammo;
	if (!ammo.loadFromFile("bullet.png"))
		cout<<"bullet_LOAD_FAIL"<<endl;
	ammo.setSmooth(true);
	sf::Sprite bullet;
	bullet.setTexture(ammo,true);
	window.draw(bullet);
	bullet.setOrigin(300,300);
	bullet.scale(0.015f, 0.015f);
	bullet.setPosition(UFOdrew.getPosition());

	
	while (window.isOpen())
	{
		sf::Event windowopen;
		while (window.pollEvent(windowopen))
		{
			switch (windowopen.type)
    {
			// window closed
			case sf::Event::Closed:
				window.close();
				break;

			// key pressed
			case sf::Event::KeyReleased:
				if (windowopen.key.code == sf::Keyboard::Space)
				{
					std::cout << "the Space key was released" << std::endl;
					bullet.setPosition(UFOdrew.getPosition());
					window.draw(bullet);
					}
				break;


			default:
				break;
			}
    }

		
		
    window.clear(sf::Color::White);
    window.draw(bgImage);
    window.draw(UFOdrew);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			UFOdrew.move(-5, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			UFOdrew.move(5, 0);

	//FORDEBUGONLY
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		UFOdrew.setPosition(15,275);
		
	window.display();
	}

    return 0;

}
