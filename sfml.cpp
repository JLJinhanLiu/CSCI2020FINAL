#include <SFML/Window.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;

void Stardust()
{
    sf::Music BGM;
    if (!BGM.openFromFile("Stardust.ogg"))
        cout<<"bgm_LOAD_FAILED"<<endl;
    BGM.play();
    BGM.setLoop(true);
}

void Spaceflight()
{
    sf::Music BGM;
    if (!BGM.openFromFile("Spaceflight.ogg"))
        cout<<"bgm_LOAD_FAILED"<<endl;
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
    sf::Sprite ship;
    ship.setTexture(UFO,true);
    window.draw(ship);
    ship.setOrigin(500,500);
    ship.scale(0.05f, 0.05f);
    ship.setPosition(366,550);
    
    //importBullet
    sf::Texture ammo;
    if (!ammo.loadFromFile("bullet.png"))
        cout<<"bullet_LOAD_FAIL"<<endl;
    ammo.setSmooth(true);
    sf::Sprite bullet;
    bullet.setTexture(ammo,true);
    window.draw(bullet);
    bullet.setOrigin(300,450);
    bullet.scale(0.015f, 0.015f);
    bullet.setPosition(ship.getPosition());
    
    //importComet
    sf::Texture com1;
    if (!com1.loadFromFile("ast1.png"))
        cout<<"comet1_LOAD_FAIL"<<endl;
    com1.setSmooth(true);
    sf::Texture com2;
    if (!com2.loadFromFile("ast2.png"))
        cout<<"comet2_LOAD_FAIL"<<endl;
    com2.setSmooth(true);
    sf::Texture com3;
    if (!com3.loadFromFile("ast3.png"))
        cout<<"comet3_LOAD_FAIL"<<endl;
    com3.setSmooth(true);
    sf::Texture com4;
    if (!com4.loadFromFile("ast4.png"))
        cout<<"comet4_LOAD_FAIL"<<endl;
    com4.setSmooth(true);
    sf::Sprite comet1;
    comet1.setTexture(com1,true);
    comet1.setOrigin(512,382);
    comet1.scale(0.08f, 0.08f);
    comet1.setPosition(rand() % 600+50,-100);
    sf::Sprite comet2;
    comet2.setTexture(com2,true);
    comet2.setOrigin(310,174);
    comet2.scale(0.15f, 0.15f);
    comet2.setPosition(rand() % 600+50,-100);
    sf::Sprite comet3;
    comet3.setTexture(com3,true);
    comet3.setOrigin(1051,1039);
    comet3.scale(0.03f, 0.03f);
    comet3.setPosition(rand() % 600+50,-100);
    sf::Sprite comet4;
    comet4.setTexture(com4,true);
    comet4.setOrigin(331,249);
    comet4.scale(0.15f, 0.15f);
    comet4.setPosition(rand() % 600+50,-100);
    
    //    setCollision
    sf::FloatRect com1box = comet1.getGlobalBounds();
    sf::FloatRect com2box = comet2.getGlobalBounds();
    sf::FloatRect com3box = comet3.getGlobalBounds();
    sf::FloatRect com4box = comet4.getGlobalBounds();
    sf::FloatRect bulletbox = bullet.getGlobalBounds();
    sf::FloatRect shipbox = ship.getGlobalBounds();
    
    //playBGM
    sf::Music BGM;
    if (!BGM.openFromFile("Stardust.ogg"))
        cout<<"bgm_LOAD_FAILED"<<endl;
    BGM.play();
    BGM.setLoop(true);
    BGM.setVolume(60);
    
    int bullety(0);
    int com1y(0);
    int com2y(0);
    int com3y(0);
    int com4y(0);
    int com1spd(rand() % 7 + 1);
    int com2spd(rand() % 7 + 1);
    int com3spd(rand() % 7 + 1);
    int com4spd(rand() % 7 + 1);
    
    //RUNTIME
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
        window.draw(ship);
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            ship.move(-10, 0);
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            ship.move(10, 0);
        
        //FORDEBUGONLY
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
        {
            ship.setPosition(366,550);
            //fire.play();
        }
        
        //comet1
        if (com1y>700)
        {
            com1y=0;
            comet1.setPosition(rand() % 600+50,-100);
            com1spd=(rand() % 7 + 1);
            window.draw(comet1);
        }
        else
        {
            com1y+=com1spd;
            comet1.move(0,com1spd);
            window.draw(comet1);
        }
        
        //comet2
        if (com2y>700)
        {
            com2y=0;
            comet2.setPosition(rand() % 600+50,-100);
            com2spd=(rand() % 7 + 1);
            window.draw(comet2);
        }
        else
        {
            com2y+=com2spd;
            comet2.move(0,com2spd);
            window.draw(comet2);
        }
        
        //comet3
        if (com3y>700)
        {
            com3y=0;
            comet3.setPosition(rand() % 600+50,-100);
            com3spd=(rand() % 7 + 1);
            window.draw(comet3);
        }
        else
        {
            com3y+=com3spd;
            comet3.move(0,com3spd);
            window.draw(comet3);
        }
        
        //comet4
        if (com4y>700)
        {
            com4y=0;
            comet4.setPosition(rand() % 600+50,-100);
            com4spd=(rand() % 7 + 1);
            window.draw(comet4);
        }
        else
        {
            com4y+=com4spd;
            comet4.move(0,com4spd);
            window.draw(comet4);
        }
        //Fire
        if (bullety>600)
        {
            bullety=0;
            bullet.setPosition(ship.getPosition());
            window.draw(bullet);
        }
        else{
            bullety+=30;
            bullet.move(0,-30);
            window.draw(bullet);
        }
        
        //checkCollision
        if (com1box.intersects(bulletbox))
        {
            com1y=0;
            comet1.setPosition(rand() % 600+50,-100);
            com1spd=(rand() % 7 + 1);
            window.draw(comet1);
        }
        if (com2box.intersects(bulletbox))
        {
            com2y=0;
            comet2.setPosition(rand() % 600+50,-100);
            com2spd=(rand() % 7 + 1);
            window.draw(comet2);
        }
        if (com3box.intersects(bulletbox))
        {
            com3y=0;
            comet3.setPosition(rand() % 600+50,-100);
            com3spd=(rand() % 7 + 1);
            window.draw(comet3);
        }
        if (com4box.intersects(bulletbox))
        {
            com4y=0;
            comet4.setPosition(rand() % 600+50,-100);
            com4spd=(rand() % 7 + 1);
            window.draw(comet4);
        }
        if (com1box.intersects(shipbox) || com2box.intersects(shipbox) || com3box.intersects(shipbox) || com4box.intersects(shipbox))
        {
            window.close();
        }
        
        //gameoverCheck
        if (ship.getPosition()==comet1.getPosition() || ship.getPosition()==comet2.getPosition() || ship.getPosition()==comet3.getPosition() || ship.getPosition()==comet4.getPosition())
        {
            window.close();
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
        
        window.display();
    }
    return EXIT_SUCCESS;
}



