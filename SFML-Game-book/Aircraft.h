#pragma once
#include"Entity.h"
#include"ResourceHolder.h"
#include<SFML/Graphics/Sprite.hpp>
#include<SFML/Graphics/RenderTarget.hpp>


using TextureHolder = ResourceHolder<sf::Texture, Textures::ID>;

class Aircraft : public Entity {
public:
	enum class Type
	{
		Eagle,
		Raptor
	};

public:
	explicit Aircraft(Type type, const TextureHolder& textures);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	Type mType;
	sf::Sprite mSprite;
};
