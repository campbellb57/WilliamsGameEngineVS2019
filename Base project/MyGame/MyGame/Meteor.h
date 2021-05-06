#pragma once

#include "Engine/GameEngine.h"

class Meteor : public GameObject
{
public:
	Meteor(sf::Vector2f pos);
	void draw();
	void update(sf::Time& elapsed);

private:
	sf::Sprite sprite_;
};

typedef std::shared_ptr<Meteor> MeteorPtr;
