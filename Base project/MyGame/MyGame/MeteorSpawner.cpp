#include "MeteorSpawner.h"

const int SPAWN_DELAY = 1000;

void MeteorSpawner::update(sf::Time& elapsed)
{
	int msElapsed = elapsed.asMilliseconds();
	timer_ -= msElapsed;

	if (timer_ <= 0)
	{
		timer_ = SPAWN_DELAY;

		sf::Vector2u size = GAME.getRenderWindow().getSize();

		float meteorx = (float)(size.x + 100);
		float meteory = (float)((rand() % size.y - 100) + 50);

		MeteorPtr meteor = std::make_shared<Meteor>(sf::Vector2f(meteorx, meteory));
		GAME.getCurrentScene().addGameObject(meteor);
	}

}