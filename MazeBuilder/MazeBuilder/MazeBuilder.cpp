#define OLC_PGE_APPLICATION
#include <iostream>
#include <stack>
#include "olcPixelGameEngine.h"
using namespace olc;
using namespace std;

struct Cell
{
	//int x = 0;
	//int y = 0;
	bool N = false;
	bool E = false;
	bool S = false;
	bool W = false;
	bool Visited = false;
};

const int MazeLen = 30;
const int MazeWid = 30;

class MazeBuilder : public PixelGameEngine
{
public:
	MazeBuilder()
	{
		sAppName = "Maze Builder";
	}

	
	stack<Cell> Stack;
	Cell cells[MazeLen][MazeWid];
	int VisitedCells;
	int TileSize;

	bool OnUserCreate() override
	{
		VisitedCells = 0;
		TileSize = 2;

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		for (int x = 0; x < MazeLen; ++x)
		{
			for (int y = 0; y < MazeWid; ++y)
			{
				if (cells[x][y].Visited)
				{
					FillRect(x * 3 * TileSize, y * 3 * TileSize, 2 * TileSize, 2 * TileSize, CYAN);
				}
				else
				{
					FillRect(x * 3 * TileSize, y * 3 * TileSize, TileSize, TileSize, WHITE);
					FillRect(x * 3 * TileSize + 1, y * 3 * TileSize, TileSize, TileSize, WHITE);
					FillRect(x * 3 * TileSize, y * 3 * TileSize + 1, TileSize, TileSize, WHITE);
					FillRect(x * 3 * TileSize + 1, y * 3 * TileSize + 1, TileSize, TileSize, WHITE);
				}

				if (cells[x][y].E)
				{
					FillRect(x * 3 * TileSize + 2, y * 3 * TileSize, TileSize, TileSize, CYAN);
				}
				else
				{
					FillRect(x * 3 * TileSize + 2, y * 3 * TileSize, TileSize, TileSize, BLACK);

				}
				if (cells[x][y].S)
				{
					FillRect(x * 3 * TileSize, y * 3 * TileSize + 2, TileSize, TileSize, CYAN);
				}
				else
				{
					FillRect(x * 3 * TileSize, y * 3 * TileSize + 2, TileSize, TileSize, BLACK);
				}
			}
		}
		return true;
	}
};

int main()
{
	MazeBuilder mb;
	if (mb.Construct(320, 180, 4, 4))
		mb.Start();

	return 0;
}
