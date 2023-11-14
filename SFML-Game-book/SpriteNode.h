#pragma once
#include"SceneNode.h"
#include<SFML/Graphics/Texture.hpp>
#include<SFML/Graphics/Rect.hpp>
#include<SFML/Graphics/Sprite.hpp>


class SpriteNode : public SceneNode
{
public:
	explicit SpriteNode(const sf::Texture& texture);
	SpriteNode(const sf::Texture& texture, sf::IntRect& rect);

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Sprite mSprite;
};