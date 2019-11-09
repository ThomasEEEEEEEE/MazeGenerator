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

struct Coords
{
	int x = 0;
	int y = 0;
};

const int MazeLen = 80;
const int MazeWid = 45;

class MazeBuilder : public PixelGameEngine
{
public:
	MazeBuilder()
	{
		sAppName = "Maze Builder";
	}

	
	stack<Coords> Stack;
	Cell cells[MazeLen][MazeWid];
	int VisitedCells;
	int TileSize;
	bool Done = false;

	bool OnUserCreate() override
	{
		srand(clock());
		VisitedCells = 1;
		TileSize = 3;
		Coords c;
		c.x = 0;
		c.y = 0;
		Stack.push(c);
		cells[0][0].Visited = true;

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		//this_thread::sleep_for(10ms);
		Clear(BLACK);

		if (VisitedCells < MazeLen * MazeWid)
		{
			vector<Dir> temp;
			temp.clear();


			if (Stack.top().y > 0 && cells[Stack.top().x][Stack.top().y - 1].Visited == false)
			{
				temp.push_back(Dir::N);
			}

			if (Stack.top().x < MazeLen - 1 && cells[Stack.top().x + 1][Stack.top().y].Visited == false)
			{
				temp.push_back(Dir::E);
			}

			if (Stack.top().y < MazeWid - 1 && cells[Stack.top().x][Stack.top().y + 1].Visited == false)
			{
				temp.push_back(Dir::S);
			}

			if (Stack.top().x > 0 && cells[Stack.top().x - 1][Stack.top().y].Visited == false)
			{
				temp.push_back(Dir::W);
			}



			if (temp.empty())
			{
				Stack.pop();
			}
			else
			{
				int dir = rand() % temp.size();
				Dir d = temp[dir];
				Coords c;

				switch (d)
				{
				case Dir::N:
					c.x = Stack.top().x;
					c.y = Stack.top().y - 1;
					cells[Stack.top().x][Stack.top().y].N = true;
					Stack.push(c);
					cells[Stack.top().x][Stack.top().y].S = true;
					break;
				case Dir::E:
					c.x = Stack.top().x + 1;
					c.y = Stack.top().y;
					cells[Stack.top().x][Stack.top().y].E = true;
					Stack.push(c);
					cells[Stack.top().x][Stack.top().y].W = true;
					break;
				case Dir::S:
					c.x = Stack.top().x;
					c.y = Stack.top().y + 1;
					cells[Stack.top().x][Stack.top().y].S = true;
					Stack.push(c);
					cells[Stack.top().x][Stack.top().y].N = true;
					break;
				case Dir::W:
					c.x = Stack.top().x - 1;
					c.y = Stack.top().y;
					cells[Stack.top().x][Stack.top().y].W = true;
					Stack.push(c);
					cells[Stack.top().x][Stack.top().y].E = true;
					break;
				}
				cells[Stack.top().x][Stack.top().y].Visited = true;
				++VisitedCells;
			}
		}
		else
		{
			Done = true;
		}


		//Borders
		FillRect(0, 0, MazeLen * (TileSize + 1), 1, BLACK);
		FillRect(0, 0, 1, MazeWid * (TileSize + 1), BLACK);
		FillRect((MazeLen) * (TileSize + 1), 0, 1 * (TileSize + 1), (MazeWid) * (TileSize + 1), BLACK);
		FillRect(0, (MazeWid) * (TileSize + 1), (MazeLen) * (TileSize + 1), 1 * (TileSize + 1), BLACK);
		
		//Opening and ending
		FillRect(0, 1, 1, TileSize, WHITE);
		FillRect((MazeLen - 1) * (TileSize + 1), (MazeWid - 1) * (TileSize + 1) - TileSize, 1, TileSize, WHITE); //Doesnt work

		//Draw Maze
		for (int x = 0; x < MazeLen; ++x)
		{
			for (int y = 0; y < MazeWid; ++y)
			{
				if (Stack.top().x == x && Stack.top().y == y)
				{
					FillRect(Stack.top().x * (TileSize + 1) + 1, Stack.top().y * (TileSize + 1) + 1, TileSize, TileSize, GREEN);
				}
				else
				{
					if (cells[x][y].Visited)
					{
						FillRect(x * (TileSize + 1) + 1, y * (TileSize + 1) + 1, TileSize, TileSize, WHITE);
					}
					else
					{
						FillRect(x * (TileSize + 1) + 1, y * (TileSize + 1) + 1, TileSize, TileSize, BLUE);
					}

					if (cells[x][y].S == true)
					{
						FillRect(x * (TileSize + 1) + 1, y * (TileSize + 1) + TileSize + 1, 3, 1, WHITE);
					}
					else
					{
						FillRect(x * (TileSize + 1) + 1, y * (TileSize + 1) + TileSize + 1, 3, 1, BLACK);
					}

					if (cells[x][y].E == true)
					{
						FillRect(x * (TileSize + 1) + TileSize + 1, y * (TileSize + 1) + 1, 1, 3, WHITE);
					}
					else
					{
						FillRect(x * (TileSize + 1) + TileSize + 1, y * (TileSize + 1) + 1, 1, 3, BLACK);
					}
				}
			}
		}

		if (Done)
		{
			char ch;
			cin >> ch;
			return false;
		}
		
		return true;
	}
};

int main()
{
	MazeBuilder mb;
	if (mb.Construct(321, 181, 4, 4))
		mb.Start();

	return 0;
}
