#pragma once
#include "Engine/GameEngine.h"
class Score : public GameObject
{
public:
	// Creates the Score instance.
	Score(sf::Vector2f pos);
	// Functions overriden from GameObject:
	void draw();
	void update(sf::Time& elapsed);
private:
	sf::Text text_;
};
typedef std::shared_ptr<Score> ScorePtr;
