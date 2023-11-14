#pragma once
#include <SFML/System/NonCopyable.hpp>
#include<SFML/Graphics/RenderWindow.hpp>
#include"SceneNode.h"
#include"Aircraft.h"
#include <array>
#include<SFML/Graphics/Texture.hpp>

class World : private sf::NonCopyable
{
public:
	explicit World(sf::RenderWindow& window);
	void update(sf::Time dt);
	void draw();

private:
	void loadTextures();
	void buildScene();

private:
	enum class Layer
	{
		Background,
		Air,
		LayerCount
	};

private:
	sf::RenderWindow& mWindow;
	sf::View mWorldView;
	TextureHolder mTextrures;
	SceneNode mSceneGraph;
	std::array<SceneNode*, (size_t)Layer::LayerCount> mSceneLayers;
	sf::FloatRect mWorldBounds;
	sf::Vector2f mSpawnPosition;
	float mScrollSpeed;
	Aircraft* mPlayerAircraft;
	
};
