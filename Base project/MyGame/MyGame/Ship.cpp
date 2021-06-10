#include "ship.h"
#include "Laser.h"
#include "GameScene.h"
#include "Explosion.h"

const float SPEED = 0.3f;
const int FIRE_DELAY = 200;

void Ship::update(sf::Time& elapsed) {
	sf::Vector2f pos = sprite_.getPosition();
	float x = pos.x;
	float y = pos.y;
	int msElapsed = elapsed.asMilliseconds();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))     y -= SPEED * msElapsed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))   y += SPEED * msElapsed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))   x -= SPEED * msElapsed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))  x += SPEED * msElapsed;
		
	sprite_.setPosition(sf::Vector2f(x, y));

	if (fireTimer_ > 0)
	{
		fireTimer_ -= msElapsed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && fireTimer_ <= 0)
	{
		fireTimer_ = FIRE_DELAY;

		sf::FloatRect bounds = sprite_.getGlobalBounds();

		float laserx = x + bounds.width;
		float lasery = y + (bounds.height / 2.0f);

		LaserPtr laser = std:: make_shared <Laser> (sf::Vector2f(laserx, lasery));
		GAME.getCurrentScene().addGameObject(laser);
	}
}

Ship::Ship()
{
	sprite_.setTexture(GAME.getTexture("Resources/ship.png"));
	sprite_.setPosition(sf::Vector2f(100, 100));
	sprite_.setScale(sf::Vector2f(0.3, 0.3));
	assignTag("Ship");
	setCollisionCheckEnabled(true);
}

void Ship::draw()
{
	GAME.getRenderWindow().draw(sprite_);
}

sf::FloatRect Ship::getCollisionRect()
{
	return sprite_.getGlobalBounds();
}

void Ship::handleCollision(GameObject& otherGameObject)
{
	if (otherGameObject.hasTag("meteor")) {
		sf::Vector2f pos = sprite_.getPosition();
		GameScene& scene = (GameScene&)GAME.getCurrentScene();
		scene.decreaseLives();
	}
}

