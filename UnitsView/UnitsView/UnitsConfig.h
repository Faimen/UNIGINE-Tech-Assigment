#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include "Unit.h"

namespace GameCore
{
	class UnitsConfig
	{
	public:
		UnitsConfig();
		~UnitsConfig();

		const std::string loadPath = "../InputData.txt";
		const std::string savePath = "../SavedData.txt";

		void LoadConfig(std::vector<std::shared_ptr<GameCore::Unit>> &units, float& viewAngle, float& viewDistance);
		void SaveConfig(std::vector<std::shared_ptr<GameCore::Unit>> &units);
	};
}