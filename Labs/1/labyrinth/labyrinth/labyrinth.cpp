#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <array>

using namespace std;

const short FIELD_SIZE = 100;

struct Coordinate
{
	int8_t x = -1;
	int8_t y = -1;
};

struct Cell
{
	char ch;
	short shortestWay = -1;
};

using Matrix = array<array<Cell, FIELD_SIZE + 2>, FIELD_SIZE + 2>;

void CreateFrame(Matrix &matrix)
{
	for (int8_t i = 0; i < FIELD_SIZE + 2; i++)
	{
		matrix[0][i].ch = '#';
		matrix[i][0].ch = '#';
		matrix[FIELD_SIZE + 1][i].ch = '#';
		matrix[i][FIELD_SIZE + 1].ch = '#';
	}
}

bool FillMatrix(const string &inFileName, Matrix &matrix, Coordinate &beginCoordinate, Coordinate &endCoordinate)
{
	ifstream fIn;
	fIn.open(inFileName);
	if (!fIn.is_open())
	{
		return false;
	}

	char ch;
	string str;
	for (int8_t i = 1; i <= FIELD_SIZE; i++)
	{
		for (int8_t j = 1; j <= FIELD_SIZE; j++)
		{
			if (!fIn.get(ch))
			{
				return false;
			}
			if (ch == 'A')
			{
				if (beginCoordinate.x != -1)
				{
					return false;
				}
				matrix[i][j].shortestWay = 0;
				beginCoordinate.x = i;
				beginCoordinate.y = j;
			}
			else if (ch == 'B')
			{
				if (endCoordinate.x != -1)
				{
					return false;
				}
				endCoordinate.x = i;
				endCoordinate.y = j;
			}
			else if (ch != ' ' && ch != '#')
			{
				return false;
			}
			matrix[i][j].ch = ch;
		}
		getline(fIn, str);
	}
	if (beginCoordinate.x == -1 || endCoordinate.x == -1)
	{
		return false;
	}
	CreateFrame(matrix);
	return true;
}

void PassInCell(Matrix &matrix, queue<Coordinate> &queueOfCoordinates, short shortesWay, int8_t x, int8_t y)
{
	if (matrix[x][y].ch != '#' && matrix[x][y].shortestWay == -1)
	{
		matrix[x][y].shortestWay = shortesWay + 1;
		queueOfCoordinates.push({ x, y });
	}
}

void WavePropagation(Matrix &matrix, const Coordinate &beginCoordinate, const Coordinate &endCoordinate)
{
	queue<Coordinate> queueOfCoordinates;
	queueOfCoordinates.push(beginCoordinate);
	Coordinate curCoordinate;
	short shortestWay;
	while (matrix[endCoordinate.x][endCoordinate.y].shortestWay == -1 && !queueOfCoordinates.empty())
	{
		curCoordinate = queueOfCoordinates.front();
		queueOfCoordinates.pop();
		shortestWay = matrix[curCoordinate.x][curCoordinate.y].shortestWay;
		PassInCell(matrix, queueOfCoordinates, shortestWay, curCoordinate.x, curCoordinate.y - 1);
		PassInCell(matrix, queueOfCoordinates, shortestWay, curCoordinate.x - 1, curCoordinate.y);
		PassInCell(matrix, queueOfCoordinates, shortestWay, curCoordinate.x, curCoordinate.y + 1);
		PassInCell(matrix, queueOfCoordinates, shortestWay, curCoordinate.x + 1, curCoordinate.y);
	}
}

bool CheckCell(Matrix &matrix, short &shortestWay, int8_t x, int8_t y)
{
	if (matrix[x][y].ch != '#' && shortestWay - 1 == matrix[x][y].shortestWay)
	{
		matrix[x][y].ch = '.';
		shortestWay--;
		return true;
	}
	return false;
}

void PathRecovery(Matrix &matrix, const Coordinate &endCoordinate)
{
	Coordinate curCoordinate = endCoordinate;
	short shortestWay = matrix[curCoordinate.x][curCoordinate.y].shortestWay;
	while (shortestWay > 1)
	{
		if (CheckCell(matrix, shortestWay, curCoordinate.x, curCoordinate.y - 1))
		{
			curCoordinate.y--;
			continue;
		}
		if (CheckCell(matrix, shortestWay, curCoordinate.x - 1, curCoordinate.y))
		{
			curCoordinate.x--;
			continue;
		}
		if (CheckCell(matrix, shortestWay, curCoordinate.x, curCoordinate.y + 1))
		{
			curCoordinate.y++;
			continue;
		}
		if (CheckCell(matrix, shortestWay, curCoordinate.x + 1, curCoordinate.y))
		{
			curCoordinate.x++;
			continue;
		}
	}
}

void FindShortestWay(Matrix &matrix, const Coordinate &beginCoordinate, const Coordinate &endCoordinate)
{
	WavePropagation(matrix, beginCoordinate, endCoordinate);
	if (matrix[endCoordinate.x][endCoordinate.y].shortestWay != -1)
	{
		PathRecovery(matrix, endCoordinate);
	}
}

bool PrintMatrix(const Matrix &matrix, const string &outFileName)
{
	ofstream fOut;
	fOut.open(outFileName);
	if (!fOut.is_open())
	{
		return false;
	}

	for (short i = 1; i <= FIELD_SIZE; i++)
	{
		for (short j = 1; j <= FIELD_SIZE; j++)
		{
			fOut << matrix[i][j].ch;
		}
		fOut << endl;
	}

	return true;
}

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		cout << "Not all arguments are specified.\n";
		cout << "The command line must be in the following format:\n";
		cout << "labyrinth.exe <input file> <output file>\n";
		return 1;
	}

	Matrix matrix;
	Coordinate beginCoordinate, endCoordinate;
	if (!FillMatrix(argv[1], matrix, beginCoordinate, endCoordinate))
	{
		cout << "Input error\n";
		return 1;
	}

	FindShortestWay(matrix, beginCoordinate, endCoordinate);

	if (!PrintMatrix(matrix, argv[2]))
	{
		cout << "Failed to open output file\n";
		return 1;
	}

	return 0;
}
