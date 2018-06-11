#include <SFML/Window.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

//void setWindow()
//{
	////SET RUNTIME WINDOW
	//sf::RenderWindow window(sf::VideoMode(800, 600), "UFO");
	//window.setVerticalSyncEnabled(true);
	//window.setFramerateLimit(60);
//}

//void setBackground()
//{
	////LOAD BACKGROUND TEXTURE
	//sf::Texture Background;
	//Background.loadFromFile("spacebackground.jpeg");
	
	//if (!Background.loadFromFile("spacebackground.jpeg"))
		//cout<<"background_LOAD_FAILED"<<endl;
	
	//Background.setSmooth(true);
	//sf::Sprite bgImage;
	//bgImage.setTexture(Background,true);
//}

//void loadShip()
//{
	////LOAD SPACESHIP
	//sf::Texture UFO;
    //UFO.loadFromFile("ship.png");
   
    //if (!UFO.loadFromFile("ship.png"))
		//cout<<"SHIP_LOAD_FAIL"<<endl;
	
	//UFO.setSmooth(true);
	//sf::Sprite UFOdrew;
	//UFOdrew.setTexture(UFO,true);
//}

//void loadBullet()
//{
	////LOAD BULLETS
	//sf::Texture bulletTex;
	//bulletTex.loadFromFile("bullet.png");
	
	//if (!bulletTex.loadFromFile("bullet.png"))
		//cout<<"bullet_LOAD_FAILED"<<endl;
		
	//sf::Sprite bullet;
	//bullet.setTexture(bulletTex,true);
	//bullet.setOrigin(320,320);
	//bullet.scale(0.02f, 0.02f);
//}

//class fire
//{
	//public:
		
		//void firegun()
		//{
			//if (second()>=1);
			//{
				
			//}
		//}
			
//}
int main()
{
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "UFO");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	sf::Texture Background;
	Background.loadFromFile("spacebackground.jpeg");
	
	if (!Background.loadFromFile("spacebackground.jpeg"))
		cout<<"background_LOAD_FAILED"<<endl;
	
	Background.setSmooth(true);
	sf::Sprite bgImage;
	bgImage.setTexture(Background,true);
	sf::Texture UFO;
    UFO.loadFromFile("ship.png");
   
    if (!UFO.loadFromFile("ship.png"))
		cout<<"SHIP_LOAD_FAIL"<<endl;
	
	UFO.setSmooth(true);
	sf::Sprite UFOdrew;
	UFOdrew.setTexture(UFO,true);
	sf::Texture bulletTex;
	bulletTex.loadFromFile("bullet.png");
	
	if (!bulletTex.loadFromFile("bullet.png"))
		cout<<"bullet_LOAD_FAILED"<<endl;
		
	sf::Sprite bullet;
	bullet.setTexture(bulletTex,true);
	bullet.setOrigin(320,320);
	bullet.scale(0.02f, 0.02f);
	
	//setWindow();
	//setBackground();
	//loadShip();
	//loadBullet();
	
	//INITIAL DRAWING
	window.draw(UFOdrew);
	UFOdrew.setOrigin(100,100);
	UFOdrew.scale(0.25f, 0.25f);
	UFOdrew.setPosition(15,275);
	
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

		//CONTROLS
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			UFOdrew.move(0, 8);
		}
	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			UFOdrew.move(0, -8);
		}
		
		
		
        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		//{
			//UFOdrew.move(-5, 0);
		//}
	
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		//{
			//UFOdrew.move(5, 0);
		//}
		
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		//{
			//UFOdrew.move(0, 5);
		//}
	
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		//{
			//UFOdrew.move(0, -5);
		//}
		
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		//{
			//UFOdrew.rotate(5);
		//}
		
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		//{
			//UFOdrew.rotate(-5);
		//}
		
		////FOR DEBUG ONLY
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			UFOdrew.setPosition(15,275);
		}
		
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Space)
				window.draw(bullet);
		}
		//if (sf::Keyboard::isKeyReleased(sf::Keyboard::Space))
		//{
			//window.draw(bullet);
			////fire.firegun();
		//}
	
		window.display();
	}
    
    return 0;
}
