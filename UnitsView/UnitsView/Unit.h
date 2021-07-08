#pragma once
#include "Math.h"
#include "UnitsView.h"
#include <vector>
#include <iostream>

namespace GameCore
{
	class Unit
	{
	public:
		Unit(MyMath::Vector2 pos, MyMath::Vector2 dir, float viewAngle, float viewDistance);
		~Unit();

		std::vector<std::shared_ptr<Unit>> viewUnits;
		GameCore::ViewSector viewSector;

		MyMath::Vector2 position;
		MyMath::Vector2 direction;
	};
}