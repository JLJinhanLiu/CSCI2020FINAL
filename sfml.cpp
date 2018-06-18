#include "ResourcePath.hpp"
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
    
    //importUIElements
    
    //importFont
    sf::Font invasion;
    if (!invasion.loadFromFile(resourcePath() + "invasion.ttf"))
        cout<<"font_LOAD_FAILED"<<endl;
    
    //buildString
    sf::Text score;
    score.setFont(invasion);
    score.setCharacterSize(30);
    score.setFillColor(sf::Color::White);
    score.setString("Score: ");
    score.setPosition(5, 0);
    
    sf::Text points;
    points.setFont(invasion);
    points.setCharacterSize(30);
    points.setPosition(5, 30);
    points.setFillColor(sf::Color::White);
    
    sf::Text lives;
    lives.setFont(invasion);
    lives.setCharacterSize(30);
    lives.setFillColor(sf::Color::Red);
    lives.setPosition(750, 0);
    
    sf::Text highscore;
    highscore.setFont(invasion);
    highscore.setCharacterSize(30);
    highscore.setFillColor(sf::Color::White);
    highscore.setString("HIGH SCORE: ");
    highscore.setPosition(8, 0);
    
    sf::Text hiscore;
    hiscore.setFont(invasion);
    hiscore.setCharacterSize(30);
    hiscore.setFillColor(sf::Color::White);
    hiscore.setPosition(6, 30);
    
    sf::Text Tutorial;
    Tutorial.setFont(invasion);
    Tutorial.setCharacterSize(30);
    Tutorial.setFillColor(sf::Color::White);
    Tutorial.setPosition(140, 450);
    Tutorial.setString("Use A and D to move your ship");
    
    //importBACKGROUND
    sf::Texture Background;
    if (!Background.loadFromFile(resourcePath() + "spacebackground.jpeg"))
        cout<<"background_LOAD_FAILED"<<endl;
    Background.setSmooth(true);
    sf::Sprite bgImage;
    bgImage.setTexture(Background,true);
    
    //importTitle
    sf::Texture titleimage;
    if (!titleimage.loadFromFile(resourcePath() + "title.png"))
        cout<<"title_LOAD_FAILED"<<endl;
    titleimage.setSmooth(true);
    sf::Sprite title;
    title.setTexture(titleimage,true);
    title.setOrigin(224,67);
    title.scale(1.2f, 1.2f);
    title.setPosition(400,200);
    
    //importStart
    sf::Texture startimage;
    if (!startimage.loadFromFile(resourcePath() + "start.png"))
        cout<<"startimage_LOAD_FAILED"<<endl;
    startimage.setSmooth(true);
    sf::Sprite start;
    start.setTexture(startimage,true);
    start.setOrigin(118,45);
    start.scale(0.5f, 0.5f);
    start.setPosition(400,350);
    
    //importDifficulty
    sf::Texture diffimage;
    if (!diffimage.loadFromFile(resourcePath() + "diffic.png"))
        cout<<"diffimage_LOAD_FAILED"<<endl;
    diffimage.setSmooth(true);
    sf::Sprite diffic;
    diffic.setTexture(diffimage,true);
    diffic.setOrigin(230,45);
    diffic.scale(0.5f, 0.5f);
    diffic.setPosition(400,400);
    
    sf::Texture easyimage;
    if (!easyimage.loadFromFile(resourcePath() + "easy.png"))
        cout<<"easy_LOAD_FAILED"<<endl;
    easyimage.setSmooth(true);
    sf::Sprite easy;
    easy.setTexture(easyimage,true);
    easy.setOrigin(76,30);
    easy.scale(0.75f, 0.75f);
    easy.setPosition(400,450);
    
    sf::Texture mediumimage;
    if (!mediumimage.loadFromFile(resourcePath() + "medium.png"))
        cout<<"medium_LOAD_FAILED"<<endl;
    mediumimage.setSmooth(true);
    sf::Sprite medium;
    medium.setTexture(mediumimage,true);
    medium.setOrigin(100,31);
    medium.scale(0.75f, 0.75f);
    medium.setPosition(400,500);
    
    sf::Texture hardimage;
    if (!hardimage.loadFromFile(resourcePath() + "hard.png"))
        cout<<"hard_LOAD_FAILED"<<endl;
    hardimage.setSmooth(true);
    sf::Sprite hard;
    hard.setTexture(hardimage,true);
    hard.setOrigin(75,25);
    hard.scale(0.75f, 0.75f);
    hard.setPosition(400,550);
    
    //importMusicSel.
    sf::Texture musicselect;
    if (!musicselect.loadFromFile(resourcePath() + "music.png"))
        cout<<"musicselect_LOAD_FAILED"<<endl;
    musicselect.setSmooth(true);
    sf::Sprite musicsel;
    musicsel.setTexture(musicselect,true);
    musicsel.setOrigin(65,35);
    musicsel.scale(0.6f, 0.6f);
    musicsel.setPosition(400,440);
    
    sf::Texture song;
    if (!song.loadFromFile(resourcePath() + "songs.png"))
        cout<<"music_LOAD_FAILED"<<endl;
    song.setSmooth(true);
    sf::Sprite songs;
    songs.setTexture(song,true);
    songs.setOrigin(225,80);
    songs.scale(0.6f, 0.6f);
    songs.setPosition(400,520);
    
    //importSoundEffects
    sf::SoundBuffer hitBuffer;
    if (!hitBuffer.loadFromFile(resourcePath() + "hit.ogg"))
        cout<<"hitsound_LOAD_FAILED"<<endl;
    
    sf::Sound hitSound;
    hitSound.setBuffer(hitBuffer);
    hitSound.setVolume(30);
    
    sf::SoundBuffer deadBuffer;
    if (!deadBuffer.loadFromFile(resourcePath() + "dead.ogg"))
        cout<<"deathsound_LOAD_FAILED"<<endl;
    
    sf::Sound deathSound;
    deathSound.setBuffer(deadBuffer);
    deathSound.setVolume(60);
    
    sf::SoundBuffer loselifeBuffer;
    if (!loselifeBuffer.loadFromFile(resourcePath() + "loselife.ogg"))
        cout<<"loselifesound_LOAD_FAILED"<<endl;
    
    sf::Sound loselifeSound;
    loselifeSound.setBuffer(loselifeBuffer);
    loselifeSound.setVolume(40);
    
    sf::SoundBuffer gainalife;
    if (!gainalife.loadFromFile(resourcePath() + "addlife.ogg"))
        cout<<"addlifesound_LOAD_FAILED"<<endl;
    
    sf::Sound getlife;
    getlife.setBuffer(gainalife);
    
    sf::SoundBuffer gameoverBuffer;
    if (!gameoverBuffer.loadFromFile(resourcePath() + "gameover.ogg"))
        cout<<"gameoversound_LOAD_FAILED"<<endl;
    
    sf::Sound gameoverSound;
    gameoverSound.setBuffer(gameoverBuffer);
    
    sf::SoundBuffer selectBuffer;
    if (!selectBuffer.loadFromFile(resourcePath() + "select.ogg"))
        cout<<"selectsound_LOAD_FAILED"<<endl;
    
    sf::Sound selectSound;
    selectSound.setBuffer(selectBuffer);
    
    //importExit
    sf::Texture exitimage;
    if (!exitimage.loadFromFile(resourcePath() + "exit.png"))
        cout<<"exitimage_LOAD_FAILED"<<endl;
    exitimage.setSmooth(true);
    sf::Sprite exit;
    exit.setTexture(exitimage,true);
    exit.setOrigin(81,32);
    exit.scale(0.55f, 0.55f);
    exit.setPosition(400,490);
    
    //importHeart
    sf::Texture heartimage;
    if (!heartimage.loadFromFile(resourcePath() + "heart.png"))
        cout<<"heartimage_LOAD_FAILED"<<endl;
    heartimage.setSmooth(true);
    sf::Sprite heart;
    heart.setTexture(heartimage,true);
    heart.setOrigin(88,77);
    heart.setPosition(730,20);
    heart.scale(0.15f, 0.15f);
    
    sf::Sprite addlife;
    addlife.setTexture(heartimage,true);
    addlife.setOrigin(88,77);
    addlife.scale(0.2f, 0.2f);
    
    //importGAMEOVER
    sf::Texture overimage;
    if (!overimage.loadFromFile(resourcePath() + "gameo.png"))
        cout<<"overimage_LOAD_FAILED"<<endl;
    overimage.setSmooth(true);
    sf::Sprite gameo;
    gameo.setTexture(overimage,true);
    gameo.setOrigin(1769,334);
    gameo.scale(0.15f, 0.15f);
    gameo.setPosition(400,120);
    
    //importEXPLOSION
    sf::Texture explo;
    if (!explo.loadFromFile(resourcePath() + "exp.png"))
        cout<<"exp_LOAD_FAILED"<<endl;
    explo.setSmooth(true);
    sf::Sprite exp;
    exp.setTexture(explo,true);
    exp.setOrigin(387,360);
    exp.scale(0.3f, 0.3f);
    exp.setPosition(0,0);
    
    //importSHIP
    sf::Texture UFO;
    if (!UFO.loadFromFile(resourcePath() + "ship.png"))
        cout<<"SHIP_LOAD_FAIL"<<endl;
    UFO.setSmooth(true);
    sf::Sprite ship;
    ship.setTexture(UFO,true);
    window.draw(ship);
    ship.setOrigin(500,500);
    ship.scale(0.05f, 0.05f);
    
    //importBullet
    sf::Texture ammo;
    if (!ammo.loadFromFile(resourcePath() + "bullet.png"))
        cout<<"bullet_LOAD_FAIL"<<endl;
    ammo.setSmooth(true);
    sf::Sprite bullet;
    bullet.setTexture(ammo,true);
    window.draw(bullet);
    bullet.setOrigin(300,2000);
    bullet.scale(0.015f, 0.015f);
    
    //importComet
    sf::Texture com1;
    if (!com1.loadFromFile(resourcePath() + "ast1.png"))
        cout<<"comet1_LOAD_FAIL"<<endl;
    com1.setSmooth(true);
    sf::Texture com2;
    if (!com2.loadFromFile(resourcePath() + "ast2.png"))
        cout<<"comet2_LOAD_FAIL"<<endl;
    com2.setSmooth(true);
    sf::Texture com3;
    if (!com3.loadFromFile(resourcePath() + "ast3.png"))
        cout<<"comet3_LOAD_FAIL"<<endl;
    com3.setSmooth(true);
    sf::Texture com4;
    if (!com4.loadFromFile(resourcePath() + "ast4.png"))
        cout<<"comet4_LOAD_FAIL"<<endl;
    com4.setSmooth(true);
    sf::Sprite comet1;
    comet1.setTexture(com1,true);
    comet1.setOrigin(512,382);
    comet1.scale(0.08f, 0.08f);
    sf::Sprite comet2;
    comet2.setTexture(com2,true);
    comet2.setOrigin(310,174);
    comet2.scale(0.15f, 0.15f);
    sf::Sprite comet3;
    comet3.setTexture(com3,true);
    comet3.setOrigin(1051,1039);
    comet3.scale(0.03f, 0.03f);
    sf::Sprite comet4;
    comet4.setTexture(com4,true);
    comet4.setOrigin(150,249);
    comet4.scale(0.5f, 0.5f);
    
    //variableDefinition
    int hscore(0);
    int life(5);
    int hearts;
    int xaxis(366);
    int diff(1);
    int point(0);
    int bullety(0);
    int hearty(0);
    int heartrand(0);
    int heartdiff(10);
    unsigned int com1y(0);
    unsigned int com2y(0);
    unsigned int com3y(0);
    unsigned int com4y(0);
    int com1spd(rand() % 6 + diff);
    int com2spd(rand() % 6 + diff);
    int com3spd(rand() % 6 + diff);
    int com4spd(rand() % 6 + diff);
    
    //loadBGM
    sf::Music BGM;
    if (!BGM.openFromFile(resourcePath() + "Stardust.ogg"))
        cout<<"bgm_LOAD_FAILED"<<endl;
    BGM.setLoop(true);
    BGM.setVolume(60);
    
    //setBoolVar
    bool tutorial(true);
    bool titlescreen(true);
    bool gamerunning(false);
    bool difficulty(false);
    bool musicselection(false);
    bool heartdrop(false);
    
    //RUNTIME
    while (window.isOpen())
    {
        sf::Event windowopen;
        while (window.pollEvent(windowopen))
        {
            if (windowopen.type == sf::Event::Closed)
                window.close();
        }
        hiscore.setString(to_string(hscore));
        while (titlescreen)
        {
            sf::Event windowopen;
            while (window.pollEvent(windowopen))
            {
                if (windowopen.type == sf::Event::Closed)
                    window.close();
            }
            hiscore.setString(to_string(hscore));
            hearts=life;
            lives.setString(to_string(hearts));
            point=0;
            ship.setPosition(366,580);
            xaxis=366;
            com1y=0;
            com2y=0;
            com3y=0;
            com4y=0;
            hearty=0;
            heartdrop=false;
            addlife.setPosition(rand() % 500 + 50, -200);
            bullet.setPosition(ship.getPosition());
            comet1.setPosition(rand() % 500+50,-100);
            comet2.setPosition(rand() % 500+50,-100);
            comet3.setPosition(rand() % 500+50,-100);
            comet4.setPosition(rand() % 500+50,-100);
            window.clear(sf::Color::White);
            window.draw(bgImage);
            window.draw(title);
            window.draw(start);
            window.draw(diffic);
            window.draw(musicsel);
            window.draw(exit);
            window.draw(highscore);
            window.draw(hiscore);
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                selectSound.play();
                titlescreen=false;
                gamerunning=true;
                BGM.play();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                selectSound.play();
                titlescreen=false;
                difficulty=true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
            {
                selectSound.play();
                titlescreen=false;
                musicselection=true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {
                selectSound.play();
                titlescreen=false;
                window.close();
            }
            window.display();
        }
        
        while (difficulty)
        {
            sf::Event windowopen;
            while (window.pollEvent(windowopen))
            {
                if (windowopen.type == sf::Event::Closed)
                    window.close();
            }
            window.clear(sf::Color::White);
            window.draw(bgImage);
            window.draw(title);
            window.draw(diffic);
            window.draw(easy);
            window.draw(medium);
            window.draw(hard);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
            {
                selectSound.play();
                diff=1;
                titlescreen=true;
                difficulty=false;
                life=5;
                heartdiff=7;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
            {
                selectSound.play();
                diff=3;
                titlescreen=true;
                difficulty=false;
                life=5;
                heartdiff=4;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
            {
                selectSound.play();
                diff=3;
                titlescreen=true;
                difficulty=false;
                life=3;
                heartdiff=2;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                selectSound.play();
                titlescreen=true;
                difficulty=false;
            }
            window.display();
        }
        
        while (musicselection)
        {
            sf::Event windowopen;
            while (window.pollEvent(windowopen))
            {
                if (windowopen.type == sf::Event::Closed)
                    window.close();
            }
            window.clear(sf::Color::White);
            window.draw(bgImage);
            window.draw(title);
            window.draw(musicsel);
            window.draw(songs);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
            {
                selectSound.play();
                BGM.openFromFile(resourcePath() + "Stardust.ogg");
                titlescreen=true;
                musicselection=false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
            {
                selectSound.play();
                BGM.openFromFile(resourcePath() + "Spaceflight.ogg");
                titlescreen=true;
                musicselection=false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
            {
                selectSound.play();
                BGM.openFromFile(resourcePath() + "Home.ogg");
                titlescreen=true;
                musicselection=false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                selectSound.play();
                titlescreen=true;
                musicselection=false;
            }
            window.display();
        }
        
        while (gamerunning)
        {
            sf::Event windowopen;
            while (window.pollEvent(windowopen))
            {
                if (windowopen.type == sf::Event::Closed)
                    window.close();
            }
            lives.setString(to_string(hearts));
            window.clear(sf::Color::White);
            window.draw(bgImage);
            window.draw(ship);
            window.draw(comet1);
            window.draw(comet2);
            window.draw(comet3);
            window.draw(comet4);
            window.draw(bullet);
            window.draw(score);
            window.draw(points);
            window.draw(lives);
            window.draw(heart);
            window.draw(addlife);
            
            //setCollision
            sf::FloatRect com1box = comet1.getGlobalBounds();
            sf::FloatRect com2box = comet2.getGlobalBounds();
            sf::FloatRect com3box = comet3.getGlobalBounds();
            sf::FloatRect com4box = comet4.getGlobalBounds();
            sf::FloatRect bulletbox = bullet.getGlobalBounds();
            sf::FloatRect shipbox = ship.getGlobalBounds();
            sf::FloatRect heartbox = addlife.getGlobalBounds();
            
            //Escape
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                titlescreen=true;
                gamerunning=false;
                BGM.stop();
            }
            
            //shipControl
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                tutorial=false;
                if (xaxis>=28)
                {
                    ship.move(-15, 0);
                    xaxis-=15;
                }
            }
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                tutorial=false;
                if (xaxis<=760)
                {
                    ship.move(15, 0);
                    xaxis+=15;
                }
            }
            //Tutorial?
            if (tutorial)
            {
                window.draw(Tutorial);
                window.display();
                continue;
            }
            
            //comets
            //comet1
            if (com1y>800)
            {
                com1y=0;
                comet1.setPosition(rand() % 500+50,-100);
                com1spd=(rand() % 6 + diff);
                hearts-=1;
                loselifeSound.play();
            }
            else
            {
                com1y+=com1spd;
                comet1.move(0,com1spd);
            }
            
            //comet2
            if (com2y>800)
            {
                com2y=0;
                comet2.setPosition(rand() % 500+50,-100);
                com2spd=(rand() % 6 + diff);
                hearts-=1;
                loselifeSound.play();
            }
            else
            {
                com2y+=com2spd;
                comet2.move(0,com2spd);
            }
            
            //comet3
            if (com3y>800)
            {
                com3y=0;
                comet3.setPosition(rand() % 500+50,-100);
                com3spd=(rand() % 6 + diff);
                hearts-=1;
                loselifeSound.play();
            }
            else
            {
                com3y+=com3spd;
                comet3.move(0,com3spd);
            }
            
            //comet4
            if (com4y>800)
            {
                com4y=0;
                comet4.setPosition(rand() % 500+50,-100);
                com4spd=(rand() % 6 + diff);
                hearts-=1;
                loselifeSound.play();
            }
            else
            {
                com4y+=com4spd;
                comet4.move(0,com4spd);
            }
            //fire
            if (bullety>600)
            {
                bullety=0;
                bullet.setPosition(ship.getPosition());
            }
            else
            {
                bullety+=55;
                bullet.move(0,-50);
            }
            
            //randomHeartDrop
            if (!heartdrop)
            {
                heartrand = rand() % 10000 + 1;
                if (heartrand<heartdiff)
                    heartdrop=true;
            }
            
            if (heartdrop)
            {
                hearty+=2;
                addlife.move(0, 2);
                if (hearty>800)
                {
                    hearty=0;
                    heartdrop=false;
                    addlife.setPosition(rand() % 500 + 50, -200);
                }
            }
            
            //checkCollision
            if (heartbox.intersects(shipbox))
            {
                hearts+=1;
                hearty=0;
                addlife.setPosition(rand() % 500+50, -200);
                heartdrop=false;
                getlife.play();
            }
            
            if (com1box.intersects(bulletbox))
            {
                com1y=0;
                comet1.setPosition(rand() % 500+50,-100);
                com1spd=(rand() % 6 + diff);
                bullety=0;
                bullet.setPosition(ship.getPosition());
                point+=100;
                hitSound.play();
            }
            
            if (com2box.intersects(bulletbox))
            {
                com2y=0;
                comet2.setPosition(rand() % 500+50,-100);
                com2spd=(rand() % 6 + diff);
                bullety=0;
                bullet.setPosition(ship.getPosition());
                point+=100;
                hitSound.play();
            }
            
            if (com3box.intersects(bulletbox))
            {
                com3y=0;
                comet3.setPosition(rand() % 500+50,-100);
                com3spd=(rand() % 6 + diff);
                bullety=0;
                bullet.setPosition(ship.getPosition());
                point+=100;
                hitSound.play();
            }
            
            if (com4box.intersects(bulletbox))
            {
                com4y=0;
                comet4.setPosition(rand() % 500+50,-100);
                com4spd=(rand() % 6 + diff);
                bullety=0;
                bullet.setPosition(ship.getPosition());
                point+=100;
                hitSound.play();
            }
            
            //GameOverConditions
            if (com1box.intersects(shipbox) || com2box.intersects(shipbox) || com3box.intersects(shipbox) || com4box.intersects(shipbox))
            {
                window.draw(gameo);
                exp.setPosition(ship.getPosition());
                window.draw(exp);
                window.display();
                BGM.stop();
                deathSound.play();
                if (point>hscore)
                    hscore=point;
                while (true)
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                        break;
                }
                titlescreen=true;
                gamerunning=false;
            }
            
            if (hearts==0)
            {
                lives.setString(to_string(hearts));
                window.draw(lives);
                window.draw(gameo);
                window.display();
                BGM.stop();
                gameoverSound.play();
                if (point>hscore)
                    hscore=point;
                while (true)
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                        break;
                }
                titlescreen=true;
                gamerunning=false;
            }
            point+=1;
            points.setString(to_string(point));
            window.display();
        }//endOfGamerunningLoop
        
    }//endOfWindowOpenLoop
    
    return EXIT_SUCCESS;
}
