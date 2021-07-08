#define OLC_PGE_APPLICATION
#include "Plugins/olcPixelGameEngine.h"
#include <mutex>
#include <thread>
#include <ctime>
#include "Unit.h"
#include "UnitsConfig.h"

std::mutex  mtx;
static int unitOrder = 0;
std::vector<std::shared_ptr<GameCore::Unit>> units;

//2d Graphic class
class Visualizer : public olc::PixelGameEngine
{
public:
	Visualizer()
	{
		sAppName = "Units View";
	}

public:
	std::shared_ptr<GameCore::Unit> selectedUnit;

	void DrawUnits()
	{
		float xOffset = ScreenWidth() / 2;
		float yOffset = ScreenHeight() / 2;

		Clear(olc::BLACK);

		auto selectedPos = olc::vi2d(selectedUnit->position.x + xOffset, -selectedUnit->position.y + yOffset);

		for (auto& unit : units)
		{
			Draw(unit->position.x + xOffset, -unit->position.y + yOffset, unit.get() != selectedUnit.get() ? olc::BLUE : olc::RED);
		}

		for (auto& visibleUnit : selectedUnit->viewUnits)
		{
			Draw(visibleUnit->position.x + xOffset, -visibleUnit->position.y + yOffset, olc::GREEN);
		}
	}

	bool OnUserCreate() override
	{
		selectedUnit = units[0];

		DrawUnits();
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		if (GetMouse(0).bPressed)
		{
			float mouseX = GetMouseX();
			float mouseY = GetMouseY();
			float xOffset = ScreenWidth() / 2;
			float yOffset = ScreenHeight() / 2;
			auto res = std::find_if(units.begin(), units.end(), [mouseX, mouseY, xOffset, yOffset](const std::shared_ptr<GameCore::Unit>& u)
				{
					int32_t x = u->position.x + xOffset;
					int32_t y = -u->position.y + yOffset;

					return  x == mouseX && y == mouseY;
				});

			if (res != units.end())
			{
				selectedUnit = res[0];

				DrawUnits();
			}
		}

		return true;
	}

	bool OnUserDestroy() override
	{
		//Clear memory
		units.clear();

		return true;
	}
};

void thread_VisionCheck(int tnum, int unitsCount) {
	for (;;) {
		{
			std::unique_lock<std::mutex> lock(mtx);
			if (unitOrder == unitsCount - 1)
				break;
			int ctr_val = ++unitOrder;

			for (auto& unit : units)
			{
				if (unit.get() != units[ctr_val].get())
				{
					if (units[ctr_val]->viewSector.isInsideSector(unit->position, units[ctr_val]->position))
					{
						units[ctr_val]->viewUnits.push_back((unit));
					}
				}
			}

			std::cout << "Unit " << ctr_val + 1 << ": see " << units[ctr_val]->viewUnits.size() << std::endl;
		}
		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}
}

int main()
{
	float viewAngle;
	float viewDistance;

	std::cout << "Wait, I'm working on it ... /\\.(:_:)./\\" << std::endl;

	GameCore::UnitsConfig config;
	//Read units data from config
	config.LoadConfig(units, viewAngle, viewDistance);

	//Пытался использовать многопоточность, работал с ней впервые и получилось хуже чем обычный алгоритм
#pragma region Thread attemp
	//Thread	
	//std::vector<std::thread> threads;

	//int nthreads = std::thread::hardware_concurrency();
	//if (nthreads == 0) nthreads = 2;


	//for (int i = 0; i < nthreads; i++) {
	//	std::thread thr(thread_VisionCheck, i, units.size());
	//	threads.emplace_back(std::move(thr));
	//}

	//for (auto& thr : threads) {
	//	thr.join();
	//}
#pragma endregion

#pragma region Default Logic
	// Check logic
	for (auto& unitCheker : units)
	{
		for (auto& unit : units)
		{
			if (unit.get() != unitCheker.get())
			{
				if (unitCheker->viewSector.isInsideSector(unit->position, unitCheker->position))
				{
					unitCheker->viewUnits.push_back((unit));
				}
			}
		}
	}

	for (size_t i = 0; i < units.size(); i++)
	{
		std::cout << "Unit " << i + 1 << ": see " << units[i]->viewUnits.size() << std::endl;
	}
#pragma endregion

	//Save result data
	config.SaveConfig(units);

	//Visualizer window;
	Visualizer window;
	if (window.Construct(200, 200, 4, 4))
		window.Start();

	return 0;
}