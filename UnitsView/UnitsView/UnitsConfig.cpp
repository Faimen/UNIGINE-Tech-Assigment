#include "UnitsConfig.h"

GameCore::UnitsConfig::UnitsConfig(){}
GameCore::UnitsConfig::~UnitsConfig(){}

void GameCore::UnitsConfig::LoadConfig(std::vector<std::shared_ptr<GameCore::Unit>> &units, float &viewAngle, float &viewDistance)
{
	std::ifstream inputFile(loadPath);
	if (inputFile.is_open())
	{
		std::string line;

		int lineOrder = 0;

		while (getline(inputFile, line))
		{
			if (line[0] == '#' || line.empty()) continue;

			switch (lineOrder)
			{
			case 0:
				viewAngle = std::stof(line);
				break;
			case 1:
				viewDistance = std::stof(line);
				break;
			default:

				float posX, posY, dirX, dirY;

				int delimiter = line.find('=');

				std::string valueLine = line.substr(delimiter + 1, line.length() - delimiter);
				posX = std::stof(valueLine);

				for (size_t i = 0; i < 3; i++)
				{
					getline(inputFile, line);
					delimiter = line.find('=');

					switch (i)
					{
					case 0:
						valueLine = line.substr(delimiter + 1, line.length() - delimiter);
						posY = std::stof(valueLine);
						break;
					case 1:
						valueLine = line.substr(delimiter + 1, line.length() - delimiter);
						dirX = std::stof(valueLine);
						break;
					case 2:
						valueLine = line.substr(delimiter + 1, line.length() - delimiter);
						dirY = std::stof(valueLine);
						break;
					}
				}

				units.push_back(std::make_shared<GameCore::Unit>(MyMath::Vector2(posX, posY), MyMath::Vector2(dirX, dirY), viewAngle, viewDistance));
				break;
			}

			lineOrder++;
		}
	}
	inputFile.close();
}

void GameCore::UnitsConfig::SaveConfig(std::vector<std::shared_ptr<GameCore::Unit>> &units)
{
	std::ofstream saveStream;          
	saveStream.open(savePath);
	if (saveStream.is_open())
	{
		for (size_t i = 0; i < units.size(); i++)
		{
			saveStream << "Unit " << i + 1 << ": see " << units[i]->viewUnits.size() << std::endl;
		}
	}
}
