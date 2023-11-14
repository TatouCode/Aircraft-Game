#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include"World.h"

class Game
{
	public:
		Game();
		void run();
	private:
		void processEvents();
		void update(sf::Time deltaTime);
		void render();
		void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	private:
		sf::RenderWindow mWindow;
		sf::Texture mTexture;
		sf::Sprite mPlayer;
		World mWorld;
		bool mIsMovingUp;
		bool mIsMovingDown;
		bool mIsMovingLeft;
		bool mIsMovingRight;
};
int main()
{
	
	try {
		Game game;
		game.run();
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
	
}
