#pragma once
#include "Math.h"

namespace GameCore
{
	class ViewSector
	{
	public:
		ViewSector(float viewAngle, float radius, MyMath::Vector2 direction);
		~ViewSector();

		float radius;
		float radiusSquared;

		MyMath::Vector2 sectorStart;
		MyMath::Vector2 sectorEnd;

		bool areClockwise(MyMath::Vector2 v1, MyMath::Vector2 v2);
		bool isWithinRadius(MyMath::Vector2 point);
		bool isInsideSector(MyMath::Vector2 point, MyMath::Vector2 center);
	};
}