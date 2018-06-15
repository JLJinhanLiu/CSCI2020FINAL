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
    
//importTitle
    sf::Texture titleimage;
    if (!titleimage.loadFromFile("title.png"))
        cout<<"title_LOAD_FAILED"<<endl;
    titleimage.setSmooth(true);
    sf::Sprite title;
    title.setTexture(titleimage,true);
    title.setOrigin(224,67);
    title.scale(0.8f, 0.8f);
    title.setPosition(400,100);
    
//importStart
    sf::Texture startimage;
    if (!startimage.loadFromFile("start.png"))
        cout<<"startimage_LOAD_FAILED"<<endl;
    startimage.setSmooth(true);
    sf::Sprite start;
    start.setTexture(startimage,true);
    start.setOrigin(118,45);
    start.scale(0.8f, 0.8f);
    //start.setPosition(366,550);
    
//importDifficulty
    sf::Texture diffimage;
    if (!diffimage.loadFromFile("diffic.png"))
        cout<<"diffimage_LOAD_FAILED"<<endl;
    diffimage.setSmooth(true);
    sf::Sprite diffic;
    diffic.setTexture(diffimage,true); 
    diffic.setOrigin(230,45);
    diffic.scale(0.8f, 0.8f);
    //diffic.setPosition(366,550); 
    
//importExit
    sf::Texture exitimage;
    if (!exitimage.loadFromFile("exit.png"))
        cout<<"exitimage_LOAD_FAILED"<<endl;
    exitimage.setSmooth(true);
    sf::Sprite exit;
    exit.setTexture(exitimage,true);  
    exit.setOrigin(92,46);
    //exit.setPosition(366,550);
    
//importHeart
    sf::Texture heartimage;
    if (!heartimage.loadFromFile("heart.png"))
        cout<<"heartimage_LOAD_FAILED"<<endl;
    heartimage.setSmooth(true);
    sf::Sprite heart;
    heart.setTexture(heartimage,true);
    heart.setOrigin(88,77);
    //heart.setPosition(366,550);
    
//importGAMEOVER
    sf::Texture overimage;
    if (!overimage.loadFromFile("gameo.png"))
        cout<<"overimage_LOAD_FAILED"<<endl;
    overimage.setSmooth(true);
    sf::Sprite gameo;
    gameo.setTexture(overimage,true);
    gameo.setOrigin(1769,334);
    gameo.scale(0.15f, 0.15f);
    gameo.setPosition(400,120);
    
//importEXPLOSION
    sf::Texture explo;
    if (!explo.loadFromFile("exp.png"))
        cout<<"exp_LOAD_FAILED"<<endl;
    explo.setSmooth(true);
    sf::Sprite exp;
    exp.setTexture(explo,true);
    exp.setOrigin(387,360);
    exp.scale(0.8f, 0.8f);
    //exp.setPosition(366,550);
    
//importSHIP
    sf::Texture UFO;
    if (!UFO.loadFromFile("ship.png"))
        cout<<"SHIP_LOAD_FAIL"<<endl;
    UFO.setSmooth(true);
    sf::Sprite ship;
    ship.setTexture(UFO,true);
    window.draw(ship);
    ship.setOrigin(496,236);
    ship.scale(0.08f, 0.08f);
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
    comet1.setOrigin(303,272);
    comet1.scale(0.08f, 0.08f);
    comet1.setPosition(rand() % 600+50,-100);
    sf::Sprite comet2;
    comet2.setTexture(com2,true);
    comet2.setOrigin(221,206);
    comet2.scale(0.15f, 0.15f);
    comet2.setPosition(rand() % 600+50,-100);
    sf::Sprite comet3;
    comet3.setTexture(com3,true);
    comet3.setOrigin(773,937);
    comet3.scale(0.04f, 0.04f);
    comet3.setPosition(rand() % 600+50,-100);
    sf::Sprite comet4;
    comet4.setTexture(com4,true);
    comet4.setOrigin(95,95);
    comet4.scale(0.5f, 0.5f);
    comet4.setPosition(rand() % 600+50,-100);
    
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
    int com1spd(rand() % 6 + 1);
    int com2spd(rand() % 6 + 1);
    int com3spd(rand() % 6 + 1);
    int com4spd(rand() % 6 + 1);
    
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
        window.draw(comet1);
        window.draw(comet2);
        window.draw(comet3);
        window.draw(comet4);
        window.draw(bullet);
//setCollision
		sf::FloatRect com1box = comet1.getGlobalBounds();
		sf::FloatRect com2box = comet2.getGlobalBounds();
		sf::FloatRect com3box = comet3.getGlobalBounds();
		sf::FloatRect com4box = comet4.getGlobalBounds();
		sf::FloatRect bulletbox = bullet.getGlobalBounds();
		sf::FloatRect shipbox = ship.getGlobalBounds();
        
        
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
            com1spd=(rand() % 6 + 1);  
        }
        else
        {
            com1y+=com1spd;
            comet1.move(0,com1spd);
        }
        
//comet2
        if (com2y>700)
        {
            com2y=0;
            comet2.setPosition(rand() % 600+50,-100);
            com2spd=(rand() % 6 + 1);
        }
        else
        {
            com2y+=com2spd;
            comet2.move(0,com2spd);
        }
        
//comet3
        if (com3y>700)
        {
            com3y=0;
            comet3.setPosition(rand() % 600+50,-100);
            com3spd=(rand() % 6 + 1);
        }
        else
        {
            com3y+=com3spd;
            comet3.move(0,com3spd);
        }
        
//comet4
        if (com4y>700)
        {
            com4y=0;
            comet4.setPosition(rand() % 600+50,-100);
            com4spd=(rand() % 6 + 1);
        }
        else
        {
            com4y+=com4spd;
            comet4.move(0,com4spd);
        }
//Fire
        if (bullety>600)
        {
            bullety=0;
            bullet.setPosition(ship.getPosition());
        }
        else{
            bullety+=30;
            bullet.move(0,-30);
        }
        
//checkCollision
        if (com1box.intersects(bulletbox))
        {
            com1y=0;
            comet1.setPosition(rand() % 600+50,-100);
            com1spd=(rand() % 6 + 1);;
            bullety=0;
            bullet.setPosition(ship.getPosition());
        }
        
        if (com2box.intersects(bulletbox))
        {
            com2y=0;
            comet2.setPosition(rand() % 600+50,-100);
            com2spd=(rand() % 6 + 1);
            bullety=0;
            bullet.setPosition(ship.getPosition());
        }
        
        if (com3box.intersects(bulletbox))
        {
            com3y=0;
            comet3.setPosition(rand() % 600+50,-100);
            com3spd=(rand() % 6 + 1);
            bullety=0;
            bullet.setPosition(ship.getPosition());
        }
        
        if (com4box.intersects(bulletbox))
        {
            com4y=0;
            comet4.setPosition(rand() % 600+50,-100);
            com4spd=(rand() % 6 + 1);
            bullety=0;
            bullet.setPosition(ship.getPosition());
        }
        
        if (com1box.intersects(shipbox) || com2box.intersects(shipbox) || com3box.intersects(shipbox) || com4box.intersects(shipbox))
        {
            window.draw(gameo);
            cout<<"GAME OVER"<<endl;
        }
        
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
        
        window.display();
    }
    return EXIT_SUCCESS;
}



