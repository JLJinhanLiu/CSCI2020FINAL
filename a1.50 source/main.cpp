#include <SFML/Window.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

//function definitions
string convertToString(char a)
{
	string result(1, a);
	return result;
}

int loseALife(bool inv)
{
	if (inv)
		return 0;
	else
		return 1;
}

string difficultyIdentifier(int difficultySelector)
{
	if (difficultySelector == 0)
		return "Medium";
	else if (difficultySelector == 1)
		return "Hard";
	else if (difficultySelector == 2)
		return "Impossible";
}

void menuConfirmation(int menuselector, int itemnumber, bool& bool1, bool& bool2)
{
	if (menuselector == itemnumber)
	{
		bool1 = false;
		bool2 = true;
	}
}

void textContainerResizing(vector<sf::Text>& inputVector, int startingX, int startingY,
	int deltaY)
{
	sf::FloatRect textRect;
	for (int x(0); x < inputVector.size();x++)
	{
		textRect = inputVector[x].getLocalBounds();
		inputVector[x].setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);
		inputVector[x].setPosition(startingX, startingY + x * deltaY);
		inputVector[x].setFillColor(sf::Color::White);
	}
}

void singleTextResizing(sf::Text& text, int startingX, int startingY)
{
	sf::FloatRect textRect;
	textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	text.setPosition(startingX, startingY);
}

void readLeaderboard(string difficulty, vector<sf::Text>& leaderboardVector)
{
	ifstream myfile("Miscs\\leaderboard.txt");
	string line;
	int vectorIterator(1);
	bool section(false);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			if (line == difficulty)
			{
				leaderboardVector[0].setString(line+"\n\n");
				section = true;
				break;
			}
		}
		while (getline(myfile, line) && section)
		{
			leaderboardVector[vectorIterator].setString(line);
			vectorIterator++;
			if (vectorIterator > 10)
			{
				section = false;
				break;
			}
		}
		myfile.close();
	}
	for (int x(0); x < leaderboardVector.size();x++)
		leaderboardVector[x].setPosition(150, 150 + x*35);
}

int checkHighScore(int score, string difficulty, bool& recordScore)
{
	fstream myfile("Miscs\\leaderboard.txt");
	string line;
	int vectorIterator(1);
	bool section(false);
	bool record(false);
	string temp;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			if (line == difficulty)
			{
				section = true;
				break;
			}
		}
		while (getline(myfile, line) && section)
		{
			for (int y(0);y < line.size();y++)
			{
				if (record)
					temp.append(convertToString(line[y]));
				if (line[y] == '#')
					record = true;
			}
			record = false;
			if (stoi(temp) < score)
			{
				recordScore = true;
				break;
			}
			vectorIterator++;
			if (vectorIterator > 10)
			{
				section = false;
				vectorIterator = 0;
				break;
			}
			temp = string();
		}
		myfile.close();
	}
	return vectorIterator;
}
void writeHighScore(int score, string playerName, string difficulty)
{
	fstream myfile("Miscs\\leaderboard.txt");
	string line;
	int vectorIterator(0), sectionNumber(0);
	bool section(false);
	bool record(false);
	string temp;
	vector<string> tempVector(33);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			tempVector[vectorIterator] = line;
			vectorIterator++;
			if (vectorIterator > 32)
				break;
		}
	}
	myfile.close();
	vectorIterator = 0;
	for (int x(0);x < tempVector.size();x++)
	{
		if (tempVector[x] == difficulty)
		{
			sectionNumber++;
			vectorIterator = 0;
			section = true;
			continue;
		}

		for (int y(0);y < tempVector[x].size();y++)
		{
			if (record)
				temp.append(convertToString(tempVector[x][y]));
			if (tempVector[x][y] == '#')
				record = true;
		}
		record = false;

		if (temp == string())
		{
			sectionNumber++;
			vectorIterator = 0;
			continue;
		}
		if (stoi(temp) < score)
		{
			if (section)
			{
				for (int z(10);z > vectorIterator;z--)
				{
					if (z == 10)
						tempVector[(sectionNumber - 1) * 10 + (sectionNumber - 1) + z] = string();
					tempVector[(sectionNumber - 1) * 10 + (sectionNumber - 1) + z] = tempVector[(sectionNumber - 1) * 10 + (sectionNumber - 1) + z-1];
				}
				tempVector[x] = playerName + '#' + to_string(score);
				section = false;
			}
		}
		temp = string();
		vectorIterator++;
	}

	myfile.open("Miscs\\leaderboard.txt", ios::out | ios::trunc);
	if (myfile.is_open())
	{
		for (int x(0);x < tempVector.size();x++)
			myfile << tempVector[x] + '\n';
	}
	myfile.close();
}

int main()
{
	//buildWINDOW
	sf::RenderWindow window(sf::VideoMode(800, 600), "Space Breakout");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	//importUIElements
	sf::FloatRect textRect; //rectangle asset for later on when calculating text boundary

	//importFont
	sf::Font invasion;
	if (!invasion.loadFromFile("Miscs/invasion.ttf"))
		cout << "font_LOAD_FAILED" << endl;

	sf::Font Futura;
	if (!Futura.loadFromFile("Miscs/FuturaLight.ttf"))
		cout << "Font2_LOAD_FAILED" << endl;

	//buildString

	sf::Text howtoquit("Press Space to continue...", invasion, 25);
	singleTextResizing(howtoquit, 400, 350);

	sf::Text score("Score: ", invasion, 30);
	score.setPosition(5, 0);

	sf::Text points('0', invasion, 30);
	points.setPosition(5, 30);

	sf::Text lives('0', invasion, 30);
	lives.setPosition(750, 0);
	lives.setFillColor(sf::Color::Red);

	sf::Text playerName(string(), invasion, 45);
	string playerNameString=string();

	sf::Text enterName("Please Enter Your Name", invasion, 35);
	singleTextResizing(enterName, 400, 280);

	vector<sf::Text> tutorialText(4);
	tutorialText[0].setString("Use A and D to move your ship");
	tutorialText[1].setString("Use Left and Right Arrow to move your ship");
	tutorialText[2].setString("Press Esc to exit");
	tutorialText[3].setString("Don't let any astriods pass by!");
	for (int x(0);x < tutorialText.size();x++)
	{
		tutorialText[x].setFont(invasion);
		tutorialText[x].setCharacterSize(25);
		textRect = tutorialText[x].getLocalBounds();
		tutorialText[x].setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);
		if (x == 3)
			tutorialText[x].setPosition(400, 250);
		else if (x != 2)
			tutorialText[x].setPosition(400, 450);
		else
			tutorialText[x].setPosition(400, 490);
	}


	sf::Text newHighScore("New High Score!", invasion, 45);
	newHighScore.setFillColor(sf::Color::Red);
	singleTextResizing(newHighScore, 400, 180);

	sf::Text quitConfirmation("    Current progress will be lost upon exiting.\n\nPress Esc again to exit or press Space to resume.", invasion, 23);
	quitConfirmation.setFillColor(sf::Color::White);
	quitConfirmation.setPosition(55, 180);

	//importSoundEffects
	sf::SoundBuffer hitBuffer;
	if (!hitBuffer.loadFromFile("Effects/hit.ogg"))
		cout << "hitsound_LOAD_FAILED" << endl;
	sf::Sound hitSound(hitBuffer);

	sf::SoundBuffer deadBuffer;
	if (!deadBuffer.loadFromFile("Effects/dead.ogg"))
		cout << "deathsound_LOAD_FAILED" << endl;
	sf::Sound deathSound(deadBuffer);

	sf::SoundBuffer loselifeBuffer;
	if (!loselifeBuffer.loadFromFile("Effects/loselife.ogg"))
		cout << "loselifesound_LOAD_FAILED" << endl;
	sf::Sound loselifeSound(loselifeBuffer);

	sf::SoundBuffer gainalife;
	if (!gainalife.loadFromFile("Effects/addlife.ogg"))
		cout << "addlifesound_LOAD_FAILED" << endl;
	sf::Sound getlife(gainalife);

	sf::SoundBuffer gameoverBuffer;
	if (!gameoverBuffer.loadFromFile("Effects/gameover.ogg"))
		cout << "gameoversound_LOAD_FAILED" << endl;
	sf::Sound gameoverSound(gameoverBuffer);

	sf::SoundBuffer selectBuffer;
	if (!selectBuffer.loadFromFile("Effects/select.ogg"))
		cout << "selectsound_LOAD_FAILED" << endl;
	sf::Sound selectSound(selectBuffer);

	sf::SoundBuffer errorBuffer;
	if (!errorBuffer.loadFromFile("Effects/error.ogg"))
		cout << "errorSound_LOAD_FAILED" << endl;
	sf::Sound errorSound(errorBuffer);
	errorSound.setVolume(20);

	sf::SoundBuffer lowHealthBuffer;
	if (!lowHealthBuffer.loadFromFile("Effects/lowHealth.ogg"))
		cout << "lowHealthsound_LOAD_FAILED" << endl;
	sf::Sound lowHealthSound(lowHealthBuffer);

	//importBACKGROUND
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("Textures/spaceBackground.png"))
		cout << "background_LOAD_FAILED" << endl;
	backgroundTexture.setSmooth(true);
	sf::Sprite background(backgroundTexture);
	background.setOrigin(400, 900);
	background.setPosition(400, 300);

	//importHeart
	sf::Texture heartimage;
	if (!heartimage.loadFromFile("Textures/heart.png"))
		cout << "heartimage_LOAD_FAILED" << endl;
	heartimage.setSmooth(true);
	sf::Sprite heart(heartimage);
	heart.setOrigin(88, 77);
	heart.setPosition(730, 20);
	heart.scale(0.15f, 0.15f);

	sf::Sprite addlife(heartimage);
	addlife.setOrigin(88, 77);
	addlife.scale(0.2f, 0.2f);

	//importGAMEOVER
	sf::Texture overimage;
	if (!overimage.loadFromFile("Textures/gameo.png"))
		cout << "overimage_LOAD_FAILED" << endl;
	overimage.setSmooth(true);
	sf::Sprite gameo(overimage);
	gameo.setOrigin(1769, 334);
	gameo.scale(0.12f, 0.12f);
	gameo.setPosition(400, 120);

	//importShipEXPLOSION
	sf::Texture shipExplosionTexture;
	if (!shipExplosionTexture.loadFromFile("Textures/exp.png"))
		cout << "shipExplosionTexture_LOAD_FAILED" << endl;
	shipExplosionTexture.setSmooth(true);
	sf::Sprite exp(shipExplosionTexture);
	exp.setOrigin(202, 206);
	exp.scale(0.5f, 0.5f);
	exp.setPosition(0, 0);

	//importAstroidExplosion
	sf::Texture astroidExplosionTexture;
	if (!astroidExplosionTexture.loadFromFile("Textures/exp2.png"))
		cout << "astroidExplosionTexture_LOAD_FAILED" << endl;
	astroidExplosionTexture.setSmooth(true);

	//importSHIP
	sf::Texture UFO;
	if (!UFO.loadFromFile("Textures/ship.png"))
		cout << "SHIP_LOAD_FAIL" << endl;
	UFO.setSmooth(true);
	sf::Sprite ship(UFO);
	ship.setOrigin(500, 500);
	ship.scale(0.05f, 0.05f);

	//importShipProtected
	sf::Texture shipProtected;
	if (!shipProtected.loadFromFile("Textures/shipBubble.png"))
		cout << "SHIPProtected_LOAD_FAIL" << endl;
	shipProtected.setSmooth(true);

	//importBullet
	sf::Texture ammo;
	if (!ammo.loadFromFile("Textures/bullet.png"))
		cout << "bullet_LOAD_FAIL" << endl;
	ammo.setSmooth(true);
	sf::Sprite bullet(ammo);
	bullet.setOrigin(300, 2000);
	bullet.scale(0.015f, 0.015f);

	//importComet
	sf::Texture com1;
	if (!com1.loadFromFile("Textures/ast1.png"))
		cout << "comet1_LOAD_FAIL" << endl;
	com1.setSmooth(true);
	sf::Texture com2;
	if (!com2.loadFromFile("Textures/ast2.png"))
		cout << "comet2_LOAD_FAIL" << endl;
	com2.setSmooth(true);
	sf::Texture com3;
	if (!com3.loadFromFile("Textures/ast3.png"))
		cout << "comet3_LOAD_FAIL" << endl;
	com3.setSmooth(true);
	sf::Texture com4;
	if (!com4.loadFromFile("Textures/ast4.png"))
		cout << "comet4_LOAD_FAIL" << endl;
	com4.setSmooth(true);
	sf::Sprite comet1(com1);
	comet1.setOrigin(303, 272);
	comet1.scale(0.08f, 0.08f);
	sf::Sprite comet2(com2);
	comet2.setOrigin(221, 205);
	comet2.scale(0.15f, 0.15f);
	sf::Sprite comet3(com3);
	comet3.setOrigin(773, 937);
	comet3.scale(0.03f, 0.03f);
	sf::Sprite comet4(com4);
	comet4.setOrigin(95, 95);
	comet4.scale(0.5f, 0.5f);

	//create vector arrays of sprites of independent textures
	vector<sf::Sprite> explosion2(4, sf::Sprite(astroidExplosionTexture));
	for (int i(0); i < explosion2.size(); i++)//explosion textures definition
	{
		explosion2[i].setOrigin(650, 650);
		explosion2[i].scale(0.12f, 0.12f);
	}
	vector<int> explosion2Clock(4, 60);

	//variableDefinition
	int life(5), hearts(0), point(0);
	int xaxis(366), movespd(12);
	int bullety(0), backgroundY(300), hearty(0);
	int heartrand(0), diff(1), heartdiff(10);
	int flash(0), countdown(0);
	unsigned int com1y(0), com2y(0), com3y(0), com4y(0);
	int com1spd(rand() % 6 + diff), com2spd(rand() % 6 + diff), 
		com3spd(rand() % 6 + diff), com4spd(rand() % 6 + diff);

	//setBoolVar
	bool opening(true), preGame(true), titlescreen(true), gamerunning(false), 
		difficulty(false), leaderboard(false), musicselection(false), heartdrop(false), 
		settingScreen(false), invincible(false), recordScore(false), gameOverScreen(false);

	//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	//menu iterator
	int mainSelector(0), BGMSelector(0), difficultySelector(0);

	//UI Text Items------------------------------------------------------------------
	//MenuItems
	vector<sf::Text> menuVector(8);
	menuVector[0] = sf::Text("Start", invasion, 30);
	menuVector[1] = sf::Text("Difficulty", invasion, 30);
	menuVector[2] = sf::Text("BGM", invasion, 30);
	menuVector[3] = sf::Text("Leaderboard", invasion, 30);
	menuVector[4] = sf::Text("Settings", invasion, 30);
	menuVector[5] = sf::Text("Quit", invasion, 30);
	menuVector[6] = sf::Text("  SPACE\nBREAKOUT", invasion, 90);
	menuVector[7] = sf::Text("Created by Jinhan Liu\nVersion Number a1.50", Futura, 18);

	//difficultyItems
	vector<sf::Text> difficultyVector(3);
	difficultyVector[0] = sf::Text("Medium", invasion, 30);
	difficultyVector[1] = sf::Text("Hard", invasion, 30);
	difficultyVector[2] = sf::Text("Impossible", invasion, 30);

	textContainerResizing(difficultyVector, 400, 400, 40);

	difficultyVector[0].setFillColor(sf::Color::Green);
	difficultyVector[1].setFillColor(sf::Color::Yellow);
	difficultyVector[2].setFillColor(sf::Color::Red);

	//BGM items
	vector<sf::Text> BGMVector(4);
	BGMVector[0] = sf::Text("Stardust", invasion, 30);
	BGMVector[1] = sf::Text("Spaceflight", invasion, 30);
	BGMVector[2] = sf::Text("Lost Future", invasion, 30);
	BGMVector[3] = sf::Text("Press Space to start or stop sampling.", invasion, 20);

	textContainerResizing(BGMVector, 400, 480, 40);

	BGMVector[3].setPosition(400, 445);

	//Settings items

	vector < vector<sf::Text> > settingVector(3);
	settingVector[0].push_back(sf::Text("Control Scheme", invasion, 30));
	settingVector[0].push_back(sf::Text("Control with arrow keys", invasion, 20));
	settingVector[0].push_back(sf::Text("Control with A,D", invasion, 20));
	int controlScheme(0);

	settingVector[1].push_back(sf::Text("Sensitivity Settings", invasion, 30));
	settingVector[1].push_back(sf::Text("Use up and down arrow to change sensitivity.", invasion, 20));	
	settingVector[1].push_back(sf::Text("Use left and right arrow to test sensitivity.", invasion, 20));
	settingVector[1].push_back(sf::Text("Use A and D to test sensitivity.", invasion, 20));
	settingVector[1].push_back(sf::Text(to_string(movespd), invasion, 30));
	settingVector[1][4].setFillColor(sf::Color(51, 255, 255));

	float musicVolume(5.0), effectVolume(5.0);

	settingVector[2].push_back(sf::Text("Volume Settings", invasion, 30));
	settingVector[2].push_back(sf::Text("Music Volume", invasion, 20));
	settingVector[2].push_back(sf::Text(to_string(int(musicVolume)), invasion, 30));
	settingVector[2].push_back(sf::Text("Effect Volume", invasion, 20));
	settingVector[2].push_back(sf::Text(to_string(int(effectVolume)), invasion, 30));

	vector<bool> settingVectorBool(settingVector.size());
	for (int x(0); x < settingVectorBool.size(); x++)
		settingVectorBool[x] = false;

	for (int x(0); x < settingVector.size(); x++)
	{
		textRect = settingVector[x][0].getLocalBounds();
		settingVector[x][0].setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);
		settingVector[x][0].setPosition(400, 350 + x * 40);
		for (int y(1); y < settingVector[x].size(); y++)
		{
			textRect = settingVector[x][y].getLocalBounds();
			settingVector[x][y].setOrigin(textRect.left + textRect.width / 2.0f,
				textRect.top + textRect.height / 2.0f);
			if (x == 1 && y > 2)
				settingVector[x][y].setPosition(400, 340 + x * 40 + (y) * 30);
			else
				settingVector[x][y].setPosition(400, 340 + x * 40 + (y + 1) * 30);
		}
	}

	vector<vector<int>> settingSelectorVector(settingVector.size());
	for (int x(0); x < settingSelectorVector.size(); x++)
		settingSelectorVector[x].push_back(1);
	settingSelectorVector[0][0] = 0;
	//Music Items-------------------------------------------------------------------

	//importMenuMusic
	sf::Music menuMusic;
	menuMusic.openFromFile("Musics/menuMusic.ogg");
	menuMusic.setVolume(40);
	menuMusic.setPlayingOffset(sf::seconds(56.f));
	menuMusic.setLoop(true);

	//importBGM
	vector<sf::Music> BGM(3);
	BGM[0].openFromFile("Musics/Stardust.ogg");
	BGM[1].openFromFile("Musics/Spaceflight.ogg");
	BGM[2].openFromFile("Musics/LostFuture.ogg");
	for (int x(0); x < BGM.size(); x++)
	{
		BGM[x].setLoop(true);
		BGM[x].setVolume(40);
	}
	//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	textContainerResizing(menuVector, 400, 320, 40);
	
	menuVector[6].setPosition(400, 180);
	menuVector[6].setFillColor(sf::Color::Red);
	menuVector[7].setPosition(90, 570);

	//introTextures
	vector<sf::Texture> introTextureVector(4);
	introTextureVector[0].loadFromFile("Textures/black.png");
	introTextureVector[1].loadFromFile("Textures/disclaimer.png");
	introTextureVector[2].loadFromFile("Textures/studioPresents.png");
	introTextureVector[3].loadFromFile("Textures/Engine.png");

	vector<sf::Sprite> introSpriteVector(introTextureVector.size());
	for (int x(0); x < introSpriteVector.size(); x++)
	{
		introSpriteVector[x].setTexture(introTextureVector[x]);
		introSpriteVector[x].setOrigin(400, 300);
		introSpriteVector[x].setPosition(400, 300);
	}
	introSpriteVector[2].setOrigin(400, 220);
	//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	//leaderboardItems
	vector<sf::Text> leaderboardMediumVector(11);
	vector<sf::Text> leaderboardHardVector(11);
	vector<sf::Text> leaderboardImpossibleVector(11);
	for (int x(0);x < leaderboardMediumVector.size();x++)
	{
		leaderboardMediumVector[x].setCharacterSize(25);
		leaderboardMediumVector[x].setFont(invasion);
	}
	for (int x(0);x < leaderboardHardVector.size();x++)
	{
		leaderboardHardVector[x].setCharacterSize(25);
		leaderboardHardVector[x].setFont(invasion);
	}
	for (int x(0);x < leaderboardImpossibleVector.size();x++)
	{
		leaderboardImpossibleVector[x].setCharacterSize(25);
		leaderboardImpossibleVector[x].setFont(invasion);
	}
	unsigned int leaderboardSelector(0);
	sf::Text leaderboardMsg("Use left and right arrows to navigate.", invasion, 20);
	singleTextResizing(leaderboardMsg, 400, 100);
	//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	window.setKeyRepeatEnabled(false);
	sf::Event windowopen;

	//RUNTIME
	//Intro
	int x(0);
	for (int i(0); i < 3; i++)
	{
		while (x <= 360)
		{
			if (i == 1 && x < 48 && x%4 == 0)
				menuMusic.setVolume(x/4);
			if (x <= 60)
				introSpriteVector[0].setColor(sf::Color(255, 255, 255, -4 * x + 240));
			else if (x >= 300 && x <= 360)
				introSpriteVector[0].setColor(sf::Color(255, 255, 255, 4 * (x - 300)));
			window.clear(sf::Color::Black);
			window.draw(introSpriteVector[i + 1]);
			window.draw(introSpriteVector[0]);
			window.display();
			while (window.pollEvent(windowopen))
			{
				if (windowopen.type == sf::Event::KeyPressed)
				{
					if (windowopen.key.code == sf::Keyboard::Enter || windowopen.key.code == sf::Keyboard::Escape || windowopen.key.code == sf::Keyboard::Space)
					{
						x = 360;
						break;
					}
				}
			}
			x++;
		}
		if (i == 0)
			menuMusic.play();
		x = 0;
	}
	menuMusic.setVolume(12 * (musicVolume / 5));
	for (int x(0); x < 60; x++)
	{
		introSpriteVector[0].setColor(sf::Color(255, 255, 255, -4 * x + 240));
		window.clear(sf::Color::Black);
		background.setPosition(400, backgroundY);
		backgroundY++;
		window.draw(background);
		for (int x(0); x < menuVector.size(); x++)
			window.draw(menuVector[x]);
		window.draw(introSpriteVector[0]);
		window.display();
	}
	while (window.isOpen()) //BEGINNING OF GAME LOOP - MENUS, GAME, ETC
	{
		//correct sound volume
		hitSound.setVolume(20 * (effectVolume / 5));
		deathSound.setVolume(60 * (effectVolume / 5));
		loselifeSound.setVolume(25 * (effectVolume / 5));
		lowHealthSound.setVolume(165 * (effectVolume / 5));
		getlife.setVolume(100 * (effectVolume / 5));
		gameoverSound.setVolume(100 * (effectVolume / 5));
		menuMusic.setVolume(12 * (musicVolume / 5));
		for (int x(0);x < BGM.size();x++)
			BGM[x].setVolume(40 * (musicVolume / 5));

		//reset window item positions
		for (int x(0); x < menuVector.size(); x++)
		{
			if (x == 8)
				continue;
			textRect = menuVector[x].getLocalBounds();
			menuVector[x].setOrigin(textRect.left + textRect.width / 2.0f,
				textRect.top + textRect.height / 2.0f);
			menuVector[x].setPosition(400, 320 + x * 40);
			menuVector[x].setFillColor(sf::Color::White);
		}
		menuVector[6].setPosition(400, 180);
		menuVector[6].setFillColor(sf::Color::Red);
		menuVector[7].setPosition(90, 570);


		for (int i(0); i < explosion2.size(); i++)//explosion textures reset
		{
			explosion2[i].setPosition(-200, -200);
			explosion2[i].setColor(sf::Color(255, 255, 255, 0));
		}

		//Loadleaderboard
		readLeaderboard("Medium", leaderboardMediumVector);
		readLeaderboard("Hard", leaderboardHardVector);
		readLeaderboard("Impossible", leaderboardImpossibleVector);

		while (titlescreen)
		{
			window.setFramerateLimit(60);
			
			hearts = life;
			lives.setString(to_string(hearts));

			//reset Parameters
			point = 0;
			ship.setPosition(400, 580);
			xaxis = 400;
			com1y = 0;
			com2y = 0;
			com3y = 0;
			com4y = 0;
			hearty = 0;
			countdown = 0;
			heartdrop = false;
			invincible = false;
			addlife.setPosition(rand() % 500 + 50, -200);
			bullet.setPosition(ship.getPosition());
			comet1.setPosition(rand() % 500 + 50, -100);
			comet2.setPosition(rand() % 500 + 50, -100);
			comet3.setPosition(rand() % 500 + 50, -100);
			comet4.setPosition(rand() % 500 + 50, -100);

			//draw basic entities
			window.clear(sf::Color::White);
			if (backgroundY > 899)
			{
				backgroundY = 300;
			}
			background.setPosition(400, backgroundY);
			backgroundY++;
			window.draw(background);
			//draw menu

			for (int x(0); x < menuVector.size(); x++)
				window.draw(menuVector[x]);

			for (int x(0); x < menuVector.size(); x++)
				menuVector[x].setFillColor(sf::Color::White);
			menuVector[mainSelector].setFillColor(sf::Color(51, 153, 255));
			menuVector[6].setFillColor(sf::Color::Red);

			//grab inputs
			while (window.pollEvent(windowopen))
			{
				if (windowopen.type == sf::Event::Closed)
				{
					window.close();	
					break;
				}

				if (windowopen.type == sf::Event::KeyPressed)
				{
					if (windowopen.key.code == sf::Keyboard::Down)
					{
						if (mainSelector > 4)
						{
							errorSound.play();
							continue; 
						}
						else
						{
							selectSound.play();
							mainSelector++;
						}
					}

					if (windowopen.key.code == sf::Keyboard::Up)
					{
						if (mainSelector < 1)
						{
							errorSound.play();
							continue;
						}
						else
						{
							selectSound.play();
							mainSelector--;
						}
					}

					if (windowopen.key.code == sf::Keyboard::Enter)
					{
						selectSound.play();
						if (mainSelector == 0) //Selected start game
						{
							for (int x(0); x < 60; x++)
							{
								window.clear(sf::Color::Black);
								background.setPosition(400, backgroundY);
								backgroundY++;
								window.draw(background);
								if (menuMusic.getVolume() > 0.5)
									menuMusic.setVolume(menuMusic.getVolume() - 0.25);
								else
									menuMusic.stop();
								for (int x(0); x < menuVector.size(); x++)
								{
									menuVector[x].move(0.f,12.f);
								}
								for (int x(0); x < menuVector.size(); x++)
									window.draw(menuVector[x]);
								window.draw(introSpriteVector[0]);
								window.display();
							}
							
							titlescreen = false;
							gamerunning = true;
							BGM[BGMSelector].play();
						}
						//difficulty trigger
						menuConfirmation(mainSelector, 1, titlescreen, difficulty);
						//bgm trigger
						if (mainSelector == 2)
						{
							titlescreen = false;
							musicselection = true;
							menuMusic.pause();
						}
						//leaderboard trigger
						menuConfirmation(mainSelector, 3, titlescreen, leaderboard);
						//setting trigger
						menuConfirmation(mainSelector, 4, titlescreen, settingScreen);
						//quit trigger
						if (mainSelector == 5)
						{
							titlescreen = false;
							window.close();
						}
					}
				}
			}			
			window.display();
		}//main menu end

		//settings
		while (settingScreen)
		{
			window.clear(sf::Color::White);
			if (backgroundY > 899)
			{
				backgroundY = 300;
			}
			background.setPosition(400, backgroundY);
			backgroundY++;
			window.draw(background);

			//draw settings menu
			window.draw(menuVector[6]);
			for (int x(0); x < settingVector.size(); x++)
			{
				settingVector[x][0].setFillColor(sf::Color::White);
				if (x == settingSelectorVector[0][0])
					settingVector[x][0].setFillColor(sf::Color(51, 153, 255));
				window.draw(settingVector[x][0]);
			}
			while (window.pollEvent(windowopen)) //grab input
			{
				if (windowopen.type == sf::Event::KeyPressed)
				{
					if (windowopen.key.code == sf::Keyboard::Enter)
					{
						selectSound.play();
						settingVectorBool[settingSelectorVector[0][0]] = true;
					}
					else if (windowopen.key.code == sf::Keyboard::Escape || windowopen.key.code == sf::Keyboard::BackSpace)
					{
						selectSound.play();
						settingSelectorVector[0][0] = 0;
						titlescreen = true;
						settingScreen = false;
					}
					else if (windowopen.key.code == sf::Keyboard::Down && settingSelectorVector[0][0] < 2)
					{
						selectSound.play();
						settingSelectorVector[0][0]++;
					}
					else if (windowopen.key.code == sf::Keyboard::Up && settingSelectorVector[0][0] > 0)
					{
						selectSound.play();
						settingSelectorVector[0][0]--;
					}
					else
						errorSound.play();
				}
			}

			//first item in settings (control scheme)
			while (settingVectorBool[0])
			{
				window.clear(sf::Color::White);
				if (backgroundY > 899)
				{
					backgroundY = 300;
				}
				background.setPosition(400, backgroundY);
				backgroundY++;
				window.draw(background);

				window.draw(menuVector[6]);
				for (int x(0); x < settingVector[0].size(); x++)
				{
					if (x != 0)
						settingVector[0][x].setFillColor(sf::Color::White);
					if (x == settingSelectorVector[1][0])
						settingVector[0][x].setFillColor(sf::Color(0,255,255));
					window.draw(settingVector[0][x]);
				}
				while (window.pollEvent(windowopen)) //grab input
				{
					if (windowopen.type == sf::Event::KeyPressed)
					{
						if (windowopen.key.code == sf::Keyboard::Enter || windowopen.key.code == sf::Keyboard::BackSpace || windowopen.key.code == sf::Keyboard::Escape)
						{
							if (settingSelectorVector[1][0] == 1)
							{
								selectSound.play();
								controlScheme = 0;
								settingVectorBool[0] = false;
							}
							else if (settingSelectorVector[1][0] == 2)
							{
								selectSound.play();
								controlScheme = 1;
								settingVectorBool[0] = false;
							}
						}
						if (windowopen.key.code == sf::Keyboard::Down && settingSelectorVector[1][0] < 2)
						{
							selectSound.play();
							settingSelectorVector[1][0]++;
						}
						else if (windowopen.key.code == sf::Keyboard::Up && settingSelectorVector[1][0] > 1)
						{
							selectSound.play();
							settingSelectorVector[1][0]--;
						}
					}
				}
				window.display();
			}
			while (settingVectorBool[1])// second item in settings (sensitivity)
			{
				window.clear(sf::Color::White);
				if (backgroundY > 899)
				{
					backgroundY = 300;
				}
				background.setPosition(400, backgroundY);
				backgroundY++;
				window.draw(background);

				window.draw(menuVector[6]);
				window.draw(ship);
				settingVector[1][4].setString(to_string(movespd));
				for (int x(0); x < settingVector[1].size(); x++)
				{
					if (x == 2 && controlScheme == 1)
						continue;
					if (x == 3 && controlScheme == 0)
						continue;
					window.draw(settingVector[1][x]);
				}

				while (window.pollEvent(windowopen)) //grab input
				{
					if (windowopen.type == sf::Event::KeyPressed)
					{
						if (windowopen.key.code == sf::Keyboard::Down && movespd > 5)
						{
							movespd--;
						}
						if (windowopen.key.code == sf::Keyboard::Up && movespd < 30)
						{
							movespd++;
						}
						if (windowopen.key.code == sf::Keyboard::Enter || windowopen.key.code == sf::Keyboard::BackSpace || windowopen.key.code == sf::Keyboard::Escape)
						{
							selectSound.play();
							settingVectorBool[1] = false;
						}
					}
				}

				//test sensitivity
				if (controlScheme == 1)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
					{
						if (xaxis >= 28)
						{
							ship.move(-movespd, 0);
							xaxis -= movespd;
						}
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
					{
						if (xaxis <= 760)
						{
							ship.move(movespd, 0);
							xaxis += movespd;
						}
					}
				}
				else if (controlScheme == 0)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					{
						if (xaxis >= 28)
						{
							ship.move(-movespd, 0);
							xaxis -= movespd;
						}
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					{
						if (xaxis <= 760)
						{
							ship.move(movespd, 0);
							xaxis += movespd;
						}
					}
				}
				window.display();
			}

			while (settingVectorBool[2]) // third item in settings (volume settings)
			{
				window.clear(sf::Color::White);
				if (backgroundY > 899)
				{
					backgroundY = 300;
				}
				background.setPosition(400, backgroundY);
				backgroundY++;
				window.draw(background);

				window.draw(menuVector[6]);
				for (int x(0); x < settingVector[2].size(); x++)
				{
					if (x == 2)
						settingVector[2][x].setString(to_string(int(musicVolume)));
					if (x == 4)
						settingVector[2][x].setString(to_string(int(effectVolume)));
					if (x != 0)
						settingVector[2][x].setFillColor(sf::Color::White);
					if (x == settingSelectorVector[2][0])
						settingVector[2][x].setFillColor(sf::Color(0, 255, 255));
					window.draw(settingVector[2][x]);
				}
				while (window.pollEvent(windowopen)) //grab input
				{
					if (windowopen.type == sf::Event::KeyPressed)
					{
						if (windowopen.key.code == sf::Keyboard::Enter || windowopen.key.code == sf::Keyboard::BackSpace || windowopen.key.code == sf::Keyboard::Escape)
						{
							selectSound.play();
							settingVectorBool[2] = false;
							settingSelectorVector[2][0] = 1;
							if (menuMusic.getStatus() != menuMusic.Playing)
								menuMusic.play();
						}
						if (windowopen.key.code == sf::Keyboard::Down && settingSelectorVector[2][0] < 3)
						{
							selectSound.play();
							settingSelectorVector[2][0] += 2;
							if (settingSelectorVector[2][0] == 3)
								menuMusic.pause();
						}
						if (windowopen.key.code == sf::Keyboard::Up && settingSelectorVector[2][0] > 1)
						{
							selectSound.play();
							settingSelectorVector[2][0] -= 2;
							if (settingSelectorVector[2][0] == 1)
								menuMusic.play();
						}
						if (windowopen.key.code == sf::Keyboard::Left)
						{
							if (settingSelectorVector[2][0] == 1 && musicVolume > 0)
							{
								musicVolume--;
								menuMusic.setVolume(12 * (musicVolume / 5));
							}
							else if (settingSelectorVector[2][0] == 3 && effectVolume > 0)
							{
								effectVolume--;
								selectSound.setVolume(100 * (effectVolume / 5));
								selectSound.play();
							}
						}
						if (windowopen.key.code == sf::Keyboard::Right)
						{
							if (settingSelectorVector[2][0] == 1 && musicVolume < 10)
							{
								musicVolume++;
								menuMusic.setVolume(12 * (musicVolume / 5));
							}
							else if (settingSelectorVector[2][0] == 3 && effectVolume < 10)
							{
								effectVolume++;
								selectSound.setVolume(100  * (effectVolume / 5));
								selectSound.play();
							}
						}
					}
				}
				window.display();
				
			}
		window.display();
		}//settings end

		//difficulty menu
		while (difficulty)
		{
			window.clear(sf::Color::White);
			if (backgroundY > 899)
			{
				backgroundY = 300;
			}
			background.setPosition(400, backgroundY);
			backgroundY++;
			window.draw(background);
			window.draw(menuVector[6]);
			window.draw(menuVector[1]);

			for (int x(0); x < difficultyVector.size(); x++)
				difficultyVector[x].setFillColor(sf::Color::White);
			difficultyVector[difficultySelector].setFillColor(sf::Color(255, -120*difficultySelector+255, 0));

			for (int x(0); x < difficultyVector.size(); x++)
				window.draw(difficultyVector[x]);

			while (window.pollEvent(windowopen))
			{
				if (windowopen.type == sf::Event::Closed)
					window.close();
				if (windowopen.type == sf::Event::KeyPressed)
				{
					if (windowopen.key.code == sf::Keyboard::Down && difficultySelector < 2)
					{
						difficultySelector++;
						selectSound.play();
					}
					if (windowopen.key.code == sf::Keyboard::Up && difficultySelector > 0)
					{
						difficultySelector--;
						selectSound.play();
					}
					if (windowopen.key.code == sf::Keyboard::Escape || windowopen.key.code == sf::Keyboard::Enter || windowopen.key.code == sf::Keyboard::BackSpace)
					{
						if (difficultySelector == 0)
						{
							diff = 1;
							life = 5;
							heartdiff = 7;
						}
						if (difficultySelector == 1)
						{
							diff = 3;
							life = 5;
							heartdiff = 4;
						}
						if (difficultySelector == 2)
						{
							diff = 3;
							life = 3;
							heartdiff = 3;
						}
						selectSound.play();
						titlescreen = true;
						difficulty = false;
					}
				}
			}
			window.display();
		}//difficulty end

		//music settings
		while (musicselection)
		{
			while (window.pollEvent(windowopen))
			{
				if (windowopen.type == sf::Event::Closed)
				{
					window.close();
					break;
				}
				if (windowopen.type == sf::Event::KeyPressed)
				{
					if (windowopen.key.code == sf::Keyboard::Down && BGMSelector < 2)
					{
						for (int x(0); x < BGM.size(); x++)
							BGM[x].stop();
						BGMSelector++;
						selectSound.play();
					}
					if (windowopen.key.code == sf::Keyboard::Up && BGMSelector > 0)
					{
						for (int x(0); x < BGM.size(); x++)
							BGM[x].stop();
						BGMSelector--;
						selectSound.play();
					}
					if (windowopen.key.code == sf::Keyboard::Enter || windowopen.key.code == sf::Keyboard::BackSpace || windowopen.key.code == sf::Keyboard::Escape)
					{
						for (int x(0); x < BGM.size(); x++)
							BGM[x].stop();
						menuMusic.play();
						selectSound.play();
						titlescreen = true;
						musicselection = false;
					}
					if (windowopen.key.code == sf::Keyboard::Space)
					{
						if (BGM[BGMSelector].getStatus()==BGM[BGMSelector].Playing)
							BGM[BGMSelector].stop();
						else
							BGM[BGMSelector].play();
					}
				}
			}
			for (int x(0); x < BGMVector.size(); x++)
				BGMVector[x].setFillColor(sf::Color::White);
			BGMVector[BGMSelector].setFillColor(sf::Color(153, 51, 255));

			window.clear(sf::Color::White);
			if (backgroundY > 899)
			{
				backgroundY = 300;
			}
			background.setPosition(400, backgroundY);
			backgroundY++;
			window.draw(background);
			window.draw(menuVector[6]);
			window.draw(menuVector[2]);

			for (int x(0); x<BGMVector.size(); x++)
				window.draw(BGMVector[x]);

			window.display();
		}
		//leaderboard
		while (leaderboard)
		{

			window.clear(sf::Color::White);

			if (backgroundY > 899)
			{
				backgroundY = 300;
			}
			background.setPosition(400, backgroundY);
			backgroundY++;
			window.draw(background);
			if (leaderboardSelector == 0)
			{
				leaderboardMediumVector[0].setFillColor(sf::Color(255, -120 * leaderboardSelector + 255, 0));
				for (int x(0); x < leaderboardMediumVector.size();x++)
				{
					window.draw(leaderboardMediumVector[x]);
				}
			}
			if (leaderboardSelector == 1)
			{
				leaderboardHardVector[0].setFillColor(sf::Color(255, -120 * leaderboardSelector + 255, 0));
				for (int x(0); x < leaderboardHardVector.size();x++)
				{
					window.draw(leaderboardHardVector[x]);
				}
			}
			if (leaderboardSelector == 2)
			{
				leaderboardImpossibleVector[0].setFillColor(sf::Color(255, -120 * leaderboardSelector + 255, 0));
				for (int x(0); x < leaderboardImpossibleVector.size();x++)
				{
					window.draw(leaderboardImpossibleVector[x]);
				}
			}
			window.draw(leaderboardMsg);
			window.display();
			while (window.pollEvent(windowopen))
			{
				if (windowopen.type == sf::Event::Closed)
				{
					window.close();
					break;
				}
				if (windowopen.type == sf::Event::KeyPressed)
				{
					if (windowopen.key.code == sf::Keyboard::Left && leaderboardSelector > 0)
					{
						leaderboardSelector--;
						selectSound.play();
					}
					if (windowopen.key.code == sf::Keyboard::Right && leaderboardSelector < 2)
					{
						leaderboardSelector++;
						selectSound.play();
					}
					if (windowopen.key.code == sf::Keyboard::Enter || windowopen.key.code == sf::Keyboard::BackSpace || windowopen.key.code == sf::Keyboard::Escape)
					{
						leaderboardSelector = 0;
						selectSound.play();
						titlescreen = true;
						leaderboard = false;
						break;
					}
				}
			}
		}//leaderboard end

		//runtime
		while (gamerunning)
		{
			sf::Event windowopen;
			while (window.pollEvent(windowopen))
			{
				if (windowopen.type == sf::Event::Closed)
					window.close(); break;
			}

			lives.setString(to_string(hearts));

			//draw basic entities
			window.clear(sf::Color::White);
			if (backgroundY > 899)
			{
				backgroundY = 300;
			}
			background.setPosition(400, backgroundY);
			backgroundY++;
			window.draw(background);
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

			//check if explosion textures apply, refer fade out time.
			for (int i(0);i < explosion2.size();i++)
			{
				explosion2[i].setColor(sf::Color(255, 255, 255, 8*explosion2Clock[i]));
				window.draw(explosion2[i]);
				if (explosion2Clock[i] > 0)
					explosion2Clock[i]--;
			}

			//setCollision
			sf::FloatRect com1box = comet1.getGlobalBounds();
			sf::FloatRect com2box = comet2.getGlobalBounds();
			sf::FloatRect com3box = comet3.getGlobalBounds();
			sf::FloatRect com4box = comet4.getGlobalBounds();
			sf::FloatRect bulletbox = bullet.getGlobalBounds();
			sf::FloatRect shipbox = ship.getGlobalBounds();
			sf::FloatRect heartbox = addlife.getGlobalBounds();

			//QuitSession
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.draw(quitConfirmation);
				BGM[BGMSelector].pause();
				window.display();
				for (int x(0); x < 10; x++)
					continue;
				while (gamerunning)
				{
					while (window.pollEvent(windowopen))
					{
						if (windowopen.type == sf::Event::KeyPressed)
						{
							if (windowopen.key.code == sf::Keyboard::Escape)
							{
								ship.setTexture(UFO, true);
								titlescreen = true;
								gamerunning = false;
								BGM[BGMSelector].stop();
								menuMusic.play();
								break;
							}
						}
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					{
						BGM[BGMSelector].play();
						break;
					}
				}
				continue;
			}

			//shipControl
			if (controlScheme == 1)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					preGame = false;
					if (xaxis >= 28)
					{
						ship.move(-movespd, 0);
						xaxis -= movespd;
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					preGame = false;
					if (xaxis <= 760)
					{
						ship.move(movespd, 0);
						xaxis += movespd;
					}
				}
			}
			else if (controlScheme == 0)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					preGame = false;
					if (xaxis >= 28)
					{
						ship.move(-movespd, 0);
						xaxis -= movespd;
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					preGame = false;
					if (xaxis <= 760)
					{
						ship.move(movespd, 0);
						xaxis += movespd;
					}
				}
			}
			//Tutorial?
			if (preGame)
			{
				if (controlScheme == 1)
					window.draw(tutorialText[0]);
				else if (controlScheme == 0)
					window.draw(tutorialText[1]);
				window.draw(tutorialText[3]);
				window.draw(tutorialText[2]);
				window.display();
				continue;
			}

			//comets

			//comet1
			if (com1y>800)
			{
				com1y = 0;
				comet1.setPosition(rand() % 500 + 50, -100);
				com1spd = (rand() % 6 + diff);
				hearts -= loseALife(invincible);
				if (!invincible)
					loselifeSound.play();
			}
			else
			{
				com1y += com1spd;
				comet1.move(0, com1spd);
			}

			//comet2
			if (com2y>800)
			{
				com2y = 0;
				comet2.setPosition(rand() % 500 + 50, -100);
				com2spd = (rand() % 6 + diff);
				hearts -= loseALife(invincible);
				if (!invincible)
					loselifeSound.play();
			}
			else
			{
				com2y += com2spd;
				comet2.move(0, com2spd);
			}

			//comet3
			if (com3y>800)
			{
				com3y = 0;
				comet3.setPosition(rand() % 500 + 50, -100);
				com3spd = (rand() % 6 + diff);
				hearts -= loseALife(invincible);
				if (!invincible)
					loselifeSound.play();
			}
			else
			{
				com3y += com3spd;
				comet3.move(0, com3spd);
			}

			//comet4
			if (com4y>800)
			{
				com4y = 0;
				comet4.setPosition(rand() % 500 + 50, -100);
				com4spd = (rand() % 6 + diff);
				hearts -= loseALife(invincible);
				if (!invincible)
					loselifeSound.play();
			}
			else
			{
				com4y += com4spd;
				comet4.move(0, com4spd);
			}
			
			//fire
			if (bullety>600)
			{
				bullety = 0;
				bullet.setPosition(ship.getPosition());
			}
			else
			{
				bullety += 55;
				bullet.move(0, -50);
			}

			//randomHeartDrop
			if (!heartdrop)
			{
				heartrand = rand() % 10000 + 1;
				if (heartrand<heartdiff)
					heartdrop = true;
			}

			if (heartdrop)
			{
				hearty += 2;
				addlife.move(0, 2);
				if (hearty>800)
				{
					hearty = 0;
					heartdrop = false;
					addlife.setPosition(rand() % 500 + 50, -200);
				}
			}

			//checkCollision
			if (heartbox.intersects(shipbox))
			{
				hearts += 1;
				hearty = 0;
				addlife.setPosition(rand() % 500 + 50, -200);
				heart.setColor(sf::Color(255, 255, 255, 255));
				heartdrop = false;
				getlife.play();
			}

			if (com1box.intersects(bulletbox))
			{
				explosion2Clock[0] = 30;
				explosion2[0].setPosition(comet1.getPosition());
				com1y = 0;
				comet1.setPosition(rand() % 500 + 50, -100);
				com1spd = (rand() % 6 + diff);
				bullety = 0;
				bullet.setPosition(ship.getPosition());
				point += 100;
				hitSound.play();
			}

			if (com2box.intersects(bulletbox))
			{
				explosion2Clock[1] = 30;
				explosion2[1].setPosition(comet2.getPosition());
				com2y = 0;
				comet2.setPosition(rand() % 500 + 50, -100);
				com2spd = (rand() % 6 + diff);
				bullety = 0;
				bullet.setPosition(ship.getPosition());
				point += 100;
				hitSound.play();
			}

			if (com3box.intersects(bulletbox))
			{
				explosion2Clock[2] = 30;
				explosion2[2].setPosition(comet3.getPosition());
				com3y = 0;
				comet3.setPosition(rand() % 500 + 50, -100);
				com3spd = (rand() % 6 + diff);
				bullety = 0;
				bullet.setPosition(ship.getPosition());
				point += 100;
				hitSound.play();
			}

			if (com4box.intersects(bulletbox))
			{
				explosion2Clock[3] = 30;
				explosion2[3].setPosition(comet4.getPosition());
				com4y = 0;
				comet4.setPosition(rand() % 500 + 50, -100);
				com4spd = (rand() % 6 + diff);
				bullety = 0;
				bullet.setPosition(ship.getPosition());
				point += 100;
				hitSound.play();
			}

			//ShipCollision
			if (invincible)
			{
				float damageColor(100 * cos(countdown/4) + 155);
				ship.setColor(sf::Color(255, damageColor, damageColor, damageColor));
				countdown--;
				if (countdown <= 0)
				{
					ship.setTexture(UFO, true);
					ship.setColor(sf::Color(255, 255, 255, 255));
					invincible = false;	
				}
				
			}
			else if (com1box.intersects(shipbox) || com2box.intersects(shipbox) || com3box.intersects(shipbox) || com4box.intersects(shipbox))
			{
				ship.setTexture(shipProtected, true);
				invincible = true;
				hearts--;
				countdown=119;
				deathSound.play();
			}
			
			//heart flashing when only one health left
			if (hearts == 1)
			{
				if (flash < 1)
				{
					flash = 85;
					lowHealthSound.play();
				}
				heart.setColor(sf::Color(255, 255, 255, flash*3));
				flash--;
			}
			else
			{
				heart.setColor(sf::Color(255, 255, 255, 255));
				lowHealthSound.stop();
			}

			//GameOverConditions
			if (hearts <= 0)
			{
				gameOverScreen = true;
				lives.setString(to_string(hearts));
				heart.setColor(sf::Color(255, 255, 255, 255));
				ship.setColor(sf::Color(255, 255, 255, 255));
				
				exp.setPosition(ship.getPosition());
				
				BGM[BGMSelector].stop();
				gameoverSound.play();
				lowHealthSound.stop();

				if (checkHighScore(point, difficultyIdentifier(difficultySelector), recordScore) != 0)
					recordScore = true;
				while (gameOverScreen)
				{
					window.clear(sf::Color::White);
					window.draw(background);
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
					window.draw(gameo);
					window.draw(howtoquit);
					window.draw(exp);
					while (window.pollEvent(windowopen))
					{
						if (windowopen.type == sf::Event::KeyPressed)
						{
							if (windowopen.key.code == sf::Keyboard::Escape || windowopen.key.code == sf::Keyboard::Space)
							{
								window.setFramerateLimit(60);
								ship.setTexture(UFO, true);
								titlescreen = true;
								gamerunning = false;
								gameOverScreen = false;
								mainSelector = 0;
								menuMusic.play();
								break;
							}
						}
					}
					window.display();
				}
				continue;
			}

			point ++;
			points.setString(to_string(point));
			window.display();
		}//endOfGamerunningLoop

		while (recordScore)
		{
			if (playerNameString[0] == ' ')
				playerNameString.erase(playerNameString.begin());
			window.clear(sf::Color::White);
			if (backgroundY > 899)
			{
				backgroundY = 300;
			}
			background.setPosition(400, backgroundY);
			backgroundY++;
			window.draw(background);
			window.draw(score);
			window.draw(points);
			if (checkHighScore(point, difficultyIdentifier(difficultySelector), recordScore) == 1)
				window.draw(newHighScore);
			playerName.setString(playerNameString);
			textRect = playerName.getLocalBounds();
			singleTextResizing(playerName, 400, 350);
			
			window.draw(playerName);
			window.draw(enterName);
			
			while (window.pollEvent(windowopen))
			{
				if (windowopen.type == sf::Event::Closed)
				{
					window.close();
					break;
				}

				if (windowopen.type == sf::Event::KeyPressed)
				{
					if (windowopen.key.code == sf::Keyboard::Enter)
					{
						writeHighScore(point, playerNameString, difficultyIdentifier(difficultySelector));
						recordScore = false;
						leaderboard = true;
						titlescreen = false;
						leaderboardSelector = difficultySelector;
						playerNameString = string();
						selectSound.play();
						continue;
					}
					if (windowopen.key.code == sf::Keyboard::Backspace && playerNameString != string())
					{
						selectSound.play();
						playerNameString.pop_back();
					}
				}
				if (windowopen.type == sf::Event::TextEntered)
				{
					if ((windowopen.text.unicode <= 57 && windowopen.text.unicode >= 48) || (windowopen.text.unicode <= 90
						&& windowopen.text.unicode >= 65) || (windowopen.text.unicode <= 122 && windowopen.text.unicode >= 97)
						|| (windowopen.text.unicode == 32))
					{
						selectSound.play();
						playerNameString.append(convertToString(static_cast<char>(windowopen.text.unicode)));
					}
				}
			}
			window.display();

		}

	}//endOfWindowOpenLoop

	return EXIT_SUCCESS;
}

