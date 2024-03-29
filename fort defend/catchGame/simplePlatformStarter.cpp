// platform game.....
//

#include "stdafx.h"

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h> 
#include <time.h> 
#include <string>
class Player
{
public:
	sf::RectangleShape shape;
	sf::Vector2f velocity;
	sf::Vector2f lookDirection;
	int waitToFireCounter;
	float angle = 0.0f;
	float speed = 1;
	sf::RectangleShape topBit;
	 float friction = -1.0;

	Player();

};

Player::Player()
{
	shape.setSize(sf::Vector2f(10, 10));
	shape.setPosition(160, -20);
	float velocityX = 0, velocityY = 0, gravity = 0.3;
	int maxSpeed = 10;

	waitToFireCounter = 10;
	velocity = { 0,0 };
	lookDirection = { 0,-1 };

	shape.setOrigin(7.5, 2.5);

	shape.setSize(sf::Vector2f(20, 10));
	shape.setFillColor(sf::Color::Magenta);
	shape.setPosition(rand() % 780, rand() % 580);

	topBit.setSize(sf::Vector2f(5, 5));
	topBit.setFillColor(sf::Color::Cyan);
}

class Bullet
{
public:
	sf::RectangleShape shape;
	sf::Vector2f velocity;


};
class Apple
{
public:
	sf::RectangleShape shape;
	int health = 3;
	float speed = 1.0f;
};
int main()
{

	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		// error...
	}
	
	int kills = 0;
	int score = 0;

	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setString("Score: " + std::to_string(score));
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::White);

	sf::Text scoreTextTwo;
	scoreTextTwo.setFont(font);
	scoreTextTwo.setPosition(690, 0);
	scoreTextTwo.setString("kills: " + std::to_string(kills));
	scoreTextTwo.setCharacterSize(24);
	scoreTextTwo.setFillColor(sf::Color::White);

	sf::Text death;
	death.setFont(font);
	death.setPosition(690, 0);
	death.setString("score: " + std::to_string(score));
	death.setCharacterSize(24);
	death.setFillColor(sf::Color::White);



	//create Window
	sf::RenderWindow window(sf::VideoMode(800, 600), "platform game");
	//do this once to "seed" the random number generator
	srand(time(NULL));
	sf::View view = window.getDefaultView();
	float randomNum;

	const int numOfApples = 15;
	Apple apples[numOfApples];
	Player player;
	Player playerTwo;

	sf::CircleShape trophy;
	trophy.setRadius(3);
	trophy.setPosition(400, 300);
	trophy.setFillColor(sf::Color::White);

	playerTwo.shape.setFillColor(sf::Color::Blue);

	sf::Sprite backgroundSprite;
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("ASSETS/IMAGES/grass.png"))
	{
		std::cout << "error with grass image file";
	}
	backgroundSprite.setTexture(backgroundTexture);

	sf::Sprite trackSprite;
	sf::Texture trackTexture;
	if (!trackTexture.loadFromFile("ASSETS/IMAGES/track.png"))
	{
		std::cout << "error with grass image file";
	}
	trackSprite.setTexture(trackTexture);
	

	sf::Vector2f startPosition;

	

	const int numBullets = 10;

	sf::RectangleShape onScreenArea;
	onScreenArea.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));

	Bullet bullets[numBullets];
	for (int i = 0; i < numBullets; i++)
	{
		bullets[i].shape.setSize(sf::Vector2f(4, 4));
		bullets[i].shape.setPosition(-2000, -2000);
		bullets[i].shape.setFillColor(sf::Color::Yellow);

		bullets[i].velocity.x = 0;
		bullets[i].velocity.y = 0;
	}

	Bullet bullets2[numBullets];
	for (int i = 0; i < numBullets; i++)
	{
		bullets2[i].shape.setSize(sf::Vector2f(4, 4));
		bullets2[i].shape.setPosition(-2000, -2000);
		bullets2[i].shape.setFillColor(sf::Color::Yellow);

		bullets2[i].velocity.x = 0;
		bullets2[i].velocity.y = 0;
	}


	for (int appleIndex = 0; appleIndex < numOfApples; appleIndex++)
	{
		apples[appleIndex].shape.setSize(sf::Vector2f(20, 20));
	
			if (apples[appleIndex].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
			{
				int random = rand() % 4 + 1;
				switch (random)
				{
				case 1:
					apples[appleIndex].shape.setPosition(-199, -199);
					break;

				case 2:
					apples[appleIndex].shape.setPosition(1000, -199);
					break;

				case 3:
					apples[appleIndex].shape.setPosition(-199, 800);
					break;
				case 4:
					apples[appleIndex].shape.setPosition(1000, 800);
					break;
				}
			}
		
		apples[appleIndex].shape.setFillColor(sf::Color::Blue);
	}

	
	bool appleWin = false;
	bool rotatingView = false;
	randomNum = rand() % 750 + 0;
	const int numRows = 15;
	const int numCols = 20;
	int levelData[numRows][numCols] = {
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,5,5,5,5,5,5,5,5,5,0,0,0,0,5,0 },
	{ 0,0,0,0,0,5,0,0,0,0,0,0,0,5,0,0,0,0,0,0 },
	{ 0,0,0,0,0,5,0,0,0,0,0,0,0,5,0,0,0,0,0,0 },
	{ 0,0,0,0,0,5,0,0,0,0,0,0,0,5,0,0,0,0,0,0 },
	{ 0,0,0,0,0,5,0,0,0,0,0,0,0,5,0,0,0,0,0,0 },
	{ 0,0,0,0,0,5,0,0,0,0,0,0,0,5,0,0,0,0,0,0 },
	{ 0,0,0,0,0,5,5,5,5,5,5,5,5,5,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 } };

	sf::RectangleShape level[numRows][numCols]; //rectangle shape
	int wallHealth[numRows][numCols];
	for (int row = 0; row < numRows; row++)
	{

		for (int col = 0; col < numCols; col++)
		{
			wallHealth[row][col] = 60;
		}
	}


	for (int row = 0; row < numRows; row++)
	{
		
		for (int col = 0; col < numCols; col++)
		{
			level[row][col].setSize(sf::Vector2f(35,35));
			level[row][col].setPosition(col * 40, row * 40);
			std::cout << levelData[row][col];
			if (levelData[row][col] == 5)
			{
				level[row][col].setFillColor(sf::Color::Green);
			}
			if (levelData[row][col] == 0)
			{
				level[row][col].setFillColor(sf::Color::Black);
			}
		}
		std::cout << std::endl;
	}


	// set timePerFrame to 1 60th of a second. 60 frames per second

	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);


	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	// the clock object keeps the time.
	sf::Clock clock;

	clock.restart();

	while (window.isOpen())
	{
		// check if the close window button is clicked on.
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//add to the time since last update and restart the clock
		timeSinceLastUpdate += clock.restart();

		//update every 60th of a second
		//only when the time since last update is greater than 1/60 update the world.

		if (timeSinceLastUpdate > timePerFrame)
		{


			// get keyboard input.

			// get keyboard input.
			for (int i = 0; i < 2; i++)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					//player.angle = player.shape.getRotation() * (3.14159 / 100);
					player.angle -= .01;

				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					player.angle += .01;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					player.shape.move(player.velocity);
					player.topBit.move(player.velocity);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					player.shape.move(-player.velocity);
					player.topBit.move(-player.velocity);

				}
				for (int row = 0; row < numRows; row++)
				{
					for (int col = 0; col < numCols; col++)
					{
						if (levelData[row][col] == 0)
						{
							if (player.shape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
							{
								player.friction = { 1.0 };
							}
						}
						if (levelData[row][col] == 0)
						{
							if (playerTwo.shape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
							{
								playerTwo.friction = { 1.0 };
							}
						}
						else
						{
							playerTwo.speed = 1;
						}
					}
				}

				player.velocity *= player.friction;
				playerTwo.velocity *= playerTwo.friction;

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					playerTwo.angle -= .01;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					playerTwo.angle += .01;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					playerTwo.shape.move(playerTwo.velocity);
					playerTwo.topBit.move(playerTwo.velocity);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					playerTwo.shape.move(-playerTwo.velocity);
					playerTwo.topBit.move(-playerTwo.velocity);

				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					if (player.waitToFireCounter == 0)
					{
						for (int i = 0; i < numBullets; i++)
						{
							if (bullets[i].shape.getPosition().x == -2000)
							{
								bullets[i].shape.setPosition(player.topBit.getPosition());
								bullets[i].velocity = player.velocity;
								bullets[i].velocity.x *= 2;
								bullets[i].velocity.y *= 2;

								player.waitToFireCounter = 10;
								break;
							}

						}
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
				{
					if (playerTwo.waitToFireCounter == 0)
					{
						for (int i = 0; i < numBullets; i++)
						{
							if (bullets2[i].shape.getPosition().x == -2000)
							{
								bullets2[i].shape.setPosition(playerTwo.topBit.getPosition());
								bullets2[i].velocity = playerTwo.velocity;
								bullets2[i].velocity.x *= 2;
								bullets2[i].velocity.y *= 2;

								playerTwo.waitToFireCounter = 10;
								break;
							}

						}
					}

				}

				player.topBit.setPosition(player.shape.getPosition());

				player.lookDirection.x = cos(player.angle);
				player.lookDirection.y = sin(player.angle);

				player.velocity = player.lookDirection * 2.0f;


				player.shape.setRotation(player.angle * (180 / 3.14159));
				player.topBit.setRotation(player.angle * (180 / 3.14159));
				player.velocity *= player.friction;

				playerTwo.topBit.setPosition(playerTwo.shape.getPosition());

				playerTwo.lookDirection.x = cos(playerTwo.angle);
				playerTwo.lookDirection.y = sin(playerTwo.angle);

				playerTwo.velocity = playerTwo.lookDirection * 2.0f;
				playerTwo.velocity *= playerTwo.friction;


				playerTwo.shape.setRotation(playerTwo.angle * (180 / 3.14159));
				playerTwo.topBit.setRotation(playerTwo.angle * (180 / 3.14159));

				for (int i = 0; i < numBullets; i++)
				{
					if (bullets[i].shape.getPosition().x != -2000)
					{
						bullets[i].shape.move(bullets[i].velocity);
						if (!onScreenArea.getGlobalBounds().intersects(bullets[i].shape.getGlobalBounds()))
						{
							bullets[i].shape.setPosition(-2000, -2000);
							bullets[i].velocity.x = 0;
							bullets[i].velocity.y = 0;


						}
					}
				}

				for (int i = 0; i < numBullets; i++)
				{
					if (bullets2[i].shape.getPosition().x != -2000)
					{
						bullets2[i].shape.move(bullets2[i].velocity);
						if (!onScreenArea.getGlobalBounds().intersects(bullets2[i].shape.getGlobalBounds()))
						{
							bullets2[i].shape.setPosition(-2000, -2000);
							bullets2[i].velocity.x = 0;
							bullets2[i].velocity.y = 0;


						}
					}
				}



				if (player.waitToFireCounter > 0)
				{
					player.waitToFireCounter--;

				}
				if (playerTwo.waitToFireCounter > 0)
				{
					playerTwo.waitToFireCounter--;

				}
			}
			for (int i = 0; i < numOfApples; i++)
			{
				if (apples[i].shape.getPosition().x != -200)
				{
					apples[i].shape.move(rand() % 7 - 3, rand() % 7 - 3);
					sf::Vector2f distance = trophy.getPosition() - apples[i].shape.getPosition(); //get the distance between the two sprites (follower - player)
					float magnitudeOfDistance = sqrt(distance.x * distance.x + distance.y * distance.y); //magnitude of distance 
					sf::Vector2f moveDirection = distance / magnitudeOfDistance; //move the follower in the direction of player

					if (magnitudeOfDistance > 40) //if more than 90 away, move to player
					{
						apples[i].shape.move(moveDirection * static_cast<float>(apples[i].speed));
					}
				}
			}

			//collision detection
			for (int row = 0; row < numRows; row++)
			{
				for (int col = 0; col < numCols; col++)
				{
					for (int i = 0; i < numOfApples; i++)
					{
						if (apples[i].shape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
						{
							if (levelData[row][col]!= 0)
							{
								levelData[row][col]--;
								int random = rand() % 4 + 1;
								switch (random)
								{
								case 1:
									apples[i].shape.setPosition(-199, -199);
									break;

								case 2:
									apples[i].shape.setPosition(900, -199);
									break;

								case 3:
									apples[i].shape.setPosition(-199, 700);
									break;
								case 4:
									apples[i].shape.setPosition(900, 700);
									break;
								}
							
							}
						}
					}
				}
			}
			for (int i = 0; i < numOfApples; i++)
			{
				if (apples[i].shape.getGlobalBounds().intersects(trophy.getGlobalBounds()))
				{
					appleWin = true;
				}
			}
			

			for (int appleIndex = 0; appleIndex < numOfApples; appleIndex++)
			{
				if (apples[appleIndex].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
				{
					score++;
					kills++;
					int random = rand() % 4 + 1;
					switch (random)
					{
					case 1:
						apples[appleIndex].shape.setPosition(-199, -199);
						break;

					case 2:
						apples[appleIndex].shape.setPosition(900, -199);
						break;

					case 3:
						apples[appleIndex].shape.setPosition(-199, 790);
						break;
					case 4:
						apples[appleIndex].shape.setPosition(900, 700);
						break;
					}
				}
				if (apples[appleIndex].shape.getGlobalBounds().intersects(playerTwo.shape.getGlobalBounds()))
				{
					score++;
					kills++;
					int random = rand() % 4 + 1;
					switch (random)
					{
					case 1:
						apples[appleIndex].shape.setPosition(-199, -199);
						break;

					case 2:
						apples[appleIndex].shape.setPosition(900, -199);
						break;

					case 3:
						apples[appleIndex].shape.setPosition(-199, 790);
						break;
					case 4:
						apples[appleIndex].shape.setPosition(900, 700);
						break;
					}
				}
				for (int bulletIndex = 0; bulletIndex < numBullets; bulletIndex++)
				{
					if (apples[appleIndex].shape.getGlobalBounds().intersects(bullets[bulletIndex].shape.getGlobalBounds()))
					{
						apples[appleIndex].health--;
						if (apples[appleIndex].health <= 0)
						{
							kills++;
							score += 10;
							apples[appleIndex].health = 4;
							int random = rand() % 4 + 1;
							switch (random)
							{
							case 1:
								apples[appleIndex].shape.setPosition(-199, -199);
								break;

							case 2:
								apples[appleIndex].shape.setPosition(900, -199);
								break;

							case 3:
								apples[appleIndex].shape.setPosition(-199, 700);
								break;
							case 4:
								apples[appleIndex].shape.setPosition(900, 700);
								break;
							}
						}
						bullets[bulletIndex].shape.setPosition(-2000, -2000);
						bullets[bulletIndex].velocity.x = 0;
						bullets[bulletIndex].velocity.y = 0;

						//score++;

					}
				
					if (apples[appleIndex].shape.getGlobalBounds().intersects(bullets2[bulletIndex].shape.getGlobalBounds()))
					{
						apples[appleIndex].health--;
							if (apples[appleIndex].health <= 0)
						{
							kills++;
							score += 10;
							apples[appleIndex].health = 4;
							int random = rand() % 4 + 1;
							switch (random)
							{
							case 1:
								apples[appleIndex].shape.setPosition(-199, -199);
								break;

							case 2:
								apples[appleIndex].shape.setPosition(900, -199);
								break;

							case 3:
								apples[appleIndex].shape.setPosition(-199, 700);
								break;
							case 4:
								apples[appleIndex].shape.setPosition(900, 700);
								break;
								}
						}
						bullets2[bulletIndex].shape.setPosition(-2000, -2000);
						bullets2[bulletIndex].velocity.x = 0;
						bullets2[bulletIndex].velocity.y = 0;


					//score++;

				
			}
			}
				
			}

			// std::cout << "hat " + std::to_string( apples[4].shape.getPosition().x) + std::to_string(apples[4].shape.getPosition().y) + "\n";
			 scoreText.setString("Score: " + std::to_string(score));
			 
			 scoreTextTwo.setString("kills: " + std::to_string(kills));
			
			for (int row = 0; row < numRows; row++)
			{
				for (int col = 0; col < numCols; col++)
				{
					if (levelData[row][col] == 5)
					{
						level[row][col].setFillColor(sf::Color::Green);
					}
					if (levelData[row][col] == 4)
					{
						level[row][col].setFillColor(sf::Color::Cyan);
					}
					if (levelData[row][col] == 3)
					{
						level[row][col].setFillColor(sf::Color::Yellow);
					}
					if (levelData[row][col] == 2)
					{
						level[row][col].setFillColor(sf::Color::Magenta);
					}
					if (levelData[row][col] == 1 )
					{
						level[row][col].setFillColor(sf::Color::Red);
					}
					if (levelData[row][col] == 0)
					{
						level[row][col].setFillColor(sf::Color::Black);
					}
				}
			}

			//clear the screen and draw the shapes.
			window.clear();

			if (appleWin == false)
			{
				for (int row = 0; row < numRows; row++)
				{
					for (int col = 0; col < numCols; col++)
					{

						window.draw(level[row][col]);

					}
				}
				window.draw(trophy);
				window.draw(scoreTextTwo);
				window.draw(scoreText);
				window.draw(player.shape);
				window.draw(player.topBit);
				window.draw(playerTwo.shape);
				window.draw(playerTwo.topBit);
				window.draw(bullets->shape);
				for (int i = 0; i < numOfApples; i++)
				{
					window.draw(apples[i].shape);
				}
				for (int i = 0; i < numBullets; i++)
				{
					window.draw(bullets[i].shape);
				}
				for (int i = 0; i < numBullets; i++)
				{
					window.draw(bullets2[i].shape);
				}
			}
			if (appleWin == true)
			{
				death.setPosition(150, 200);
				death.setString("The enemy have our trophy. How will we rebuild? \n               Kills:  " + std::to_string(kills) + "\n               Score:"+std::to_string(score));

				window.draw(death);
			}
			//tell SFML  to display everything 
			window.display();

			// reset the timeSinceLastUpdate to 0 
			timeSinceLastUpdate = sf::Time::Zero;
		}
	}

	return 0;
}


