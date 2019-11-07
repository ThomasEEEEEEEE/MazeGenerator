#define OLC_PGE_APPLICATION
#include <iostream>
#include <stack>
#include <vector>
#include "olcPixelGameEngine.h"
using namespace olc;
using namespace std;

enum Dir
{
	N = 0,
	E = 1,
	S = 2,
	W = 3
};

struct Cell
{
	bool N = false;
	bool E = false;
	bool S = false;
	bool W = false;
	bool Visited = false;
};

const int MazeLen = 70;
const int MazeWid = 40;

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
	int CurrentX;
	int CurrentY;

	bool OnUserCreate() override
	{
		srand(time(0));
		VisitedCells = 0;
		TileSize = 2;
		Cell Start;
		Stack.push(Start);
		CurrentX = 0;
		CurrentY = 0;

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		vector<Dir> temp;
		temp.clear();
		try
		{
			if (cells[CurrentX][CurrentY - 1].Visited == false)
			{
				temp.push_back(Dir::N);
			}
		}
		catch (exception) {}

		try
		{
			if (cells[CurrentX + 1][CurrentY].Visited == false)
			{
				temp.push_back(Dir::E);
			}
		}
		catch (exception) {}

		try
		{
			if (cells[CurrentX][CurrentY + 1].Visited == false)
			{
				temp.push_back(Dir::S);
			}
		}
		catch (exception) {}

		try
		{
			if (cells[CurrentX - 1][CurrentY].Visited == false)
			{
				temp.push_back(Dir::W);
			}
		}
		catch (exception) {}


		cells[CurrentX][CurrentY].Visited = true;

		if (temp.empty())
		{
			Stack.pop();
		}
		else
		{
			int dir = rand() % temp.size();
			Dir d = temp[dir];

			switch (d)
			{
			case Dir::N:
				Stack.push(cells[CurrentX][CurrentY + 1]);
				cells[CurrentX][CurrentY].N = true;
				++CurrentY;
				break;
			case Dir::E:
				Stack.push(cells[CurrentX + 1][CurrentY]);
				cells[CurrentX][CurrentY].E = true;
				++CurrentX;
				break;
			case Dir::S:
				Stack.push(cells[CurrentX][CurrentY - 1]);
				cells[CurrentX][CurrentY].S = true;
				--CurrentY;
				break;
			case Dir::W:
				Stack.push(cells[CurrentX - 1][CurrentY]);
				cells[CurrentX][CurrentY].W = true;
				--CurrentX;
				break;
			}
		}


		for (int x = 0; x < MazeLen; ++x)
		{
			for (int y = 0; y < MazeWid; ++y)
			{
				if (cells[x][y].Visited)
				{
					FillRect(x * 2 * TileSize, y * 2 * TileSize, 2 * TileSize, 2 * TileSize, CYAN);
				}
				else
				{
					FillRect(x * 2 * TileSize, y * 2 * TileSize, 2 * TileSize, 2 * TileSize, WHITE);
				}

				if (cells[x][y].E)
				{
					FillRect(x * 2 * TileSize + 1, y * 2 * TileSize, TileSize, TileSize * 2, CYAN);
				}
				else
				{
					FillRect(x * 2 * TileSize + 1, y * 2 * TileSize, TileSize, TileSize * 2, BLACK);

				}
				if (cells[x][y].S)
				{
					FillRect(x * 2 * TileSize, y * 2 * TileSize + 1, TileSize * 2, TileSize, CYAN);
				}
				else
				{
					FillRect(x * 2 * TileSize, y * 2 * TileSize + 1, TileSize * 2, TileSize, BLACK);
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
