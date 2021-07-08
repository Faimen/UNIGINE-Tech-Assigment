#include "UnitsView.h"

GameCore::ViewSector::ViewSector(float viewAngle, float radius, MyMath::Vector2 direction)
{
	this->radius = radius;
	radiusSquared = powf(radius, 2);

	//Calculate sector end && start
	float dirYSquared = powf(direction.y, 2);
	float dirXSquared = powf(direction.x, 2);

	float x1, x2, y1, y2;

	if (direction.x == 0)
	{
		y1 = y2 = (MyMath::Sqrt(dirYSquared) * cosf(viewAngle / 2.0f * MyMath::pi / 180.0f)) / direction.y;

		x1 = MyMath::Sqrt(1 - powf(y1, 2));
		x2 = -x1;
	}
	else if (direction.y == 0)
	{
		x1 = x2 = (MyMath::Sqrt(dirXSquared) * cosf(viewAngle / 2.0f * MyMath::pi / 180.0f)) / direction.x;

		y1 = MyMath::Sqrt(1 - powf(x1, 2));
		y2 = -y1;
	}
	else
	{
		float w = (MyMath::Sqrt(dirXSquared + dirYSquared) * cosf(viewAngle / 2.0f * MyMath::pi / 180.0f)) / direction.x;

		float a = (1.0f + dirYSquared / dirXSquared);
		float b = (-2.0f * w * direction.y) / direction.x;

		y1 = (-b + MyMath::Sqrt(powf(b, 2) - 4.0f * a * (powf(w, 2) - 1))) / (2.0f * a);
		y2 = (-b - MyMath::Sqrt(powf(b, 2) - 4.0f * a * (powf(w, 2) - 1))) / (2.0f * a);

		x1 = w - (direction.y * y1) / direction.x;
		x2 = w - (direction.y * y2) / direction.x;
	}
	//End calculating

	sectorStart = MyMath::Vector2(x1, y1);
	sectorEnd = MyMath::Vector2(x2, y2);

	//Checking who's the starter 
	if (areClockwise(sectorStart, direction))
	{
		auto tmp = sectorStart;
		sectorStart = sectorEnd;
		sectorEnd = tmp;
	}
}

GameCore::ViewSector::~ViewSector()
{
}

/// <summary>
/// По направлени часовой стрелки ли лежит точка от вектора
/// </summary>
/// <param name="v1">Направление</param>
/// <param name="v2">Точка</param>
bool GameCore::ViewSector::areClockwise(MyMath::Vector2 v1, MyMath::Vector2 v2)
{
	return -v1.x * v2.y + v1.y * v2.x > 0;
}

/// <summary>
/// В радиусе ли точка 
/// </summary>
bool GameCore::ViewSector::isWithinRadius(MyMath::Vector2 point)
{
	return point.x * point.x + point.y * point.y <= radiusSquared;
}

/// <summary>
/// Находится ли точка в области видимости
/// </summary>
bool GameCore::ViewSector::isInsideSector(MyMath::Vector2 point, MyMath::Vector2 center)
{
	MyMath::Vector2 relPoint(point.x - center.x, point.y - center.y);

	if (!isWithinRadius(relPoint)) return false;

	return !areClockwise(sectorStart, relPoint) &&
		areClockwise(sectorEnd, relPoint);
}
