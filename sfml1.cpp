#include <SFML/Window.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;

void Stardust()
{
	if (!music.openFromFile("Stardust.mp3"))
    return -1;
	BGM.play();
}

void Spaceflight()
{
	if (!music.openFromFile("Spaceflight.mp3"))
    return -1;
	BGM.play();
}

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
	UFOdrew.setPosition(366,15);

	//importBullet
	sf::Texture ammo;
	if (!ammo.loadFromFile("bullet.png"))
		cout<<"bullet_LOAD_FAIL"<<endl;
	ammo.setSmooth(true);
	sf::Sprite bullet;
	bullet.setTexture(ammo,true);
	window.draw(bullet);
	UFOdrew.setOrigin(300,300);
	UFOdrew.scale(0.015f, 0.015f);
	UFOdrew.setPosition(UFOdrew.getposition());

	while (window.isOpen())
	{
		sf::Event windowopen;
		while (window.pollEvent(windowopen))
		{
			if (windowopen.type == sf::Event::Closed)
      	window.close();
    }

		Spaceflight();
		
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
