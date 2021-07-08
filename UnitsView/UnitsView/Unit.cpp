#include "Unit.h"

GameCore::Unit::Unit(MyMath::Vector2 pos, MyMath::Vector2 dir, float viewAngle, float viewDistance) : viewSector(viewAngle, viewDistance, dir.Normalized())
{
	position = pos;
	direction = dir.Normalized();
}

GameCore::Unit::~Unit() {}
