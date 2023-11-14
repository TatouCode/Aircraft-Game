#include"SceneNode.h"
#include<cassert>

SceneNode::SceneNode()
{
	mParent = nullptr;
}

void SceneNode::attachChild(Ptr child)
{
	child->mParent = this;
	mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
	auto found = std::find_if(mChildren.begin(), mChildren.end(),
		[&](Ptr& p) -> bool { return p.get() == &node; });

	assert(found != mChildren.end());

	Ptr result = std::move(*found);
	result->mParent = nullptr;
	mChildren.erase(found);
	return result;
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform(); //absolute world transform
	drawCurrent(target, states);

	for (auto itr = mChildren.begin(); itr != mChildren.end(); ++itr)
	{
		(*itr)->draw(target, states);
	}

}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{}

void SceneNode::update(sf::Time dt)
{
	updateCurrent(dt);
	updateChildren(dt);
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;
	for (const SceneNode* node = this; node != nullptr; node = node->mParent)
		transform = node->getTransform() * transform;

	return transform;
}

sf::Vector2f SceneNode::getWorldPosition()
{
	return getWorldTransform() * sf::Vector2f();
}

void SceneNode::updateCurrent(sf::Time dt)
{
}

void SceneNode::updateChildren(sf::Time dt)
{
	for (auto itr = mChildren.begin(); itr != mChildren.end(); ++itr)
	{
		(*itr)->update(dt);
	}
}

