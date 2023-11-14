#include"Game.h"
#include<iostream>

Game::Game()
	: mWindow(sf::VideoMode(640, 480), "SFML Application")
	, mWorld(mWindow)
	, mTexture()
	, mPlayer()
{

	if (!mTexture.loadFromFile("Media/Textures/Aigle.png")) {
		
	}
	mPlayer.setTexture(mTexture);
	mPlayer.setPosition(100.f, 100.f);
}
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
	while (mWindow.isOpen())
	{
		//sf::Time deltaTime = clock.restart();
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Z)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::Q)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;
}

void Game::update(sf::Time deltaTime)
{
	/*sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingUp)
		movement.y -= 200.f;
	if (mIsMovingDown)
		movement.y += 200.f;
	if (mIsMovingLeft)
		movement.x -= 200.f;
	if (mIsMovingRight)
		movement.x += 200.f;
	mPlayer.move(movement * deltaTime.asSeconds());
	*/
	mWorld.update(deltaTime);
	
	}

void Game::render()
{
	mWindow.clear();
	mWorld.draw();

	mWindow.setView(mWindow.getDefaultView());
	
	//mWindow.draw(mPlayer);
	mWindow.display();
}