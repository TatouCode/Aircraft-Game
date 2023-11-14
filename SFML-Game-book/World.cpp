#include"World.h"
#include"SpriteNode.h"
#include<SFML/System/Vector2.hpp>

World::World(sf::RenderWindow& window)
	: mWindow(window), mWorldView(window.getDefaultView())
	, mWorldBounds(
		0.f, //left x position
		0.f, // top y position
		mWorldView.getSize().x, // width
		2000.f) // height
	, mSpawnPosition(
		mWorldView.getSize().x / 2.f,
		mWorldBounds.height - mWorldView.getSize().y)
	, mPlayerAircraft(nullptr)
	, mScrollSpeed(-20.f)
	, mTextrures()
	, mSceneGraph()
	, mSceneLayers()
{
	loadTextures();
	buildScene();

	mWorldView.setCenter(mSpawnPosition);
}

void World::loadTextures()
{
	mTextrures.load(Textures::ID::Eagle, "Media/Textures/aigle.png");
	mTextrures.load(Textures::ID::Raptor, "Media/Textures/aigle.png");
	mTextrures.load(Textures::ID::Desert, "Media/Textures/desert.png");
}

void World::buildScene()
{
	for (std::size_t i = 0; i < (std::size_t)Layer::LayerCount; i++)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}

	sf::Texture& texture = mTextrures.get(Textures::ID::Desert);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	//ajout du desert
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[(std::size_t)Layer::Background]->attachChild(std::move(backgroundSprite));

	//ajout du joueur
	std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Type::Eagle, mTextrures));
	mPlayerAircraft = leader.get();
	mPlayerAircraft->setPosition(mSpawnPosition);
	mPlayerAircraft->setVelocity(40.f, mScrollSpeed);
	mSceneLayers[(std::size_t)Layer::Air]->attachChild(std::move(leader));

	//ajout des suiveurs
	std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Type::Raptor, mTextrures));
	leftEscort->setPosition(-80.f, 50.f);
	mPlayerAircraft->attachChild(std::move(leftEscort));
	std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::Type::Raptor, mTextrures));
	rightEscort->setPosition(80.f, 50.f);
	mPlayerAircraft->attachChild(std::move(rightEscort));

}

void World::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

void World::update(sf::Time dt)
{
	mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());

	sf::Vector2f position = mPlayerAircraft->getPosition();
	sf::Vector2f velocity = mPlayerAircraft->getVelocity();

	if (position.x <= mWorldBounds.left + 150 || position.x >= mWorldBounds.left + mWorldBounds.width - 150)
	{
		velocity.x = -velocity.x;
		mPlayerAircraft->setVelocity(velocity);
	}

	mSceneGraph.update(dt);
}