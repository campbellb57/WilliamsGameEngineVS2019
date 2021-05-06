#include "GameScene.h"
#include "ship.h"

GameScene::GameScene()
{
	ShipPtr ship = std::make_shared<Ship>();
	addGameObject(ship);
}
