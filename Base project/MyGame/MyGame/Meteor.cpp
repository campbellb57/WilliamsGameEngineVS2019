#include "Meteor.h"
#include "Explosion.h"
#include "GameScene.h"

const float SPEED = 1.2f;

Meteor::Meteor(sf::Vector2f pos)
{
	sprite_.setTexture(GAME.getTexture("Resources/meteor.png"));
	sprite_.setPosition(pos);
	sprite_.setScale(sf::Vector2f(0.24, 0.24));
	sprite_.setRotation(12);
	assignTag("meteor");
	setCollisionCheckEnabled(true);
}

void Meteor::draw()
{
	GAME.getRenderWindow().draw(sprite_);
}

void Meteor::update(sf::Time& elapsed)
{
	int msElapsed = elapsed.asMilliseconds();
	sf::Vector2f pos = sprite_.getPosition();

	if (pos.x < sprite_.getGlobalBounds().width * -1)
	{
		GameScene& scene = (GameScene&)GAME.getCurrentScene();
		scene.increaseScore();
		makeDead();
	}
	else
	{
		sprite_.setPosition(sf::Vector2f(pos.x - SPEED * msElapsed, pos.y));
	}
}

sf::FloatRect Meteor::getCollisionRect()
{
	return sprite_.getGlobalBounds();
}



void Meteor::handleCollision(GameObject& otherGameObject)
{
	if (otherGameObject.hasTag("Laser"))
	{
		sf::Vector2f pos = sprite_.getPosition();
		ExplosionPtr explosion = std::make_shared<Explosion>(pos);
		GAME.getCurrentScene().addGameObject(explosion);
		GameScene& scene = (GameScene&)GAME.getCurrentScene();
		scene.increaseScore();
		otherGameObject.makeDead();
	}

	if (otherGameObject.hasTag("Ship"))
	{
		sf::Vector2f pos = sprite_.getPosition();
		ExplosionPtr explosion = std::make_shared<Explosion>(pos);
		GAME.getCurrentScene().addGameObject(explosion);
		GameScene& scene = (GameScene&)GAME.getCurrentScene();
		//scene.decreaseLives();
		//otherGameObject.makeDead();
	}

	makeDead();
}
