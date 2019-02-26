#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>

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

void CreateFrame(Cell matrix[FIELD_SIZE + 2][FIELD_SIZE + 2])
{
	for (int8_t i = 0; i < FIELD_SIZE + 2; i++)
	{
		matrix[0][i].ch = '#';
		matrix[i][0].ch = '#';
		matrix[FIELD_SIZE + 1][i].ch = '#';
		matrix[i][FIELD_SIZE + 1].ch = '#';
	}
}

bool FillMatrix(istream &fIn, Cell matrix[FIELD_SIZE + 2][FIELD_SIZE + 2],
	Coordinate &beginCoordinate, Coordinate &endCoordinate)
{
	string str;
	for (int8_t i = 1; i <= FIELD_SIZE; i++)
	{
		for (int8_t j = 1; j <= FIELD_SIZE; j++)
		{
			if (fIn.get(matrix[i][j].ch))
			{
				if (matrix[i][j].ch == 'A')
				{
					if (beginCoordinate.x == -1)
					{
						matrix[i][j].shortestWay = 0;
						beginCoordinate.x = i;
						beginCoordinate.y = j;
					}
					else
					{
						return false;
					}
				}
				else if (matrix[i][j].ch == 'B')
				{
					if (endCoordinate.x == -1)
					{
						endCoordinate.x = i;
						endCoordinate.y = j;
					}
					else
					{
						return false;
					}
				}
				else if (matrix[i][j].ch != ' ' && matrix[i][j].ch != '#')
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		getline(fIn, str);
	}
	if (beginCoordinate.x == -1 || endCoordinate.x == -1)
	{
		return false;
	}
	return true;
}

void PassInNeighboringCell(Cell matrix[FIELD_SIZE + 2][FIELD_SIZE + 2], queue<Coordinate> &queueOfCoordinates,
	int8_t x, int8_t y, short shortesWay)
{
	if (matrix[x][y].ch != '#' && matrix[x][y].shortestWay == -1)
	{
		matrix[x][y].shortestWay = shortesWay + 1;
		queueOfCoordinates.push({ x, y });
	}
}

void WavePropagation(Cell matrix[FIELD_SIZE + 2][FIELD_SIZE + 2], Coordinate beginCoordinate, Coordinate endCoordinate)
{
	queue<Coordinate> queueOfCoordinates;
	queueOfCoordinates.push(beginCoordinate);
	Coordinate thisCoordinate;
	short shortestWay;
	while (matrix[endCoordinate.x][endCoordinate.y].shortestWay == -1 && !queueOfCoordinates.empty())
	{
		thisCoordinate = queueOfCoordinates.front();
		queueOfCoordinates.pop();
		shortestWay = matrix[thisCoordinate.x][thisCoordinate.y].shortestWay;
		PassInNeighboringCell(matrix, queueOfCoordinates, thisCoordinate.x, thisCoordinate.y - 1, shortestWay);
		PassInNeighboringCell(matrix, queueOfCoordinates, thisCoordinate.x - 1, thisCoordinate.y, shortestWay);
		PassInNeighboringCell(matrix, queueOfCoordinates, thisCoordinate.x, thisCoordinate.y + 1, shortestWay);
		PassInNeighboringCell(matrix, queueOfCoordinates, thisCoordinate.x + 1, thisCoordinate.y, shortestWay);
	}
}

bool CheckNeighboringCell(Cell matrix[FIELD_SIZE + 2][FIELD_SIZE + 2], short &shortestWay, int8_t x, int8_t y)
{
	if (matrix[x][y].ch != '#' && shortestWay - 1 == matrix[x][y].shortestWay)
	{
		matrix[x][y].ch = '.';
		shortestWay--;
		return true;
	}
	return false;
}

void PathRecovery(Cell matrix[FIELD_SIZE + 2][FIELD_SIZE + 2], Coordinate endCoordinate)
{
	Coordinate thisCoordinate;
	thisCoordinate = endCoordinate;
	short shortestWay = matrix[thisCoordinate.x][thisCoordinate.y].shortestWay;
	while (shortestWay > 1)
	{
		if (CheckNeighboringCell(matrix, shortestWay, thisCoordinate.x, thisCoordinate.y - 1))
		{
			thisCoordinate.y--;
			continue;
		}
		if (CheckNeighboringCell(matrix, shortestWay, thisCoordinate.x - 1, thisCoordinate.y))
		{
			thisCoordinate.x--;
			continue;
		}
		if (CheckNeighboringCell(matrix, shortestWay, thisCoordinate.x, thisCoordinate.y + 1))
		{
			thisCoordinate.y++;
			continue;
		}
		if (CheckNeighboringCell(matrix, shortestWay, thisCoordinate.x + 1, thisCoordinate.y))
		{
			thisCoordinate.x++;
			continue;
		}
	}
}

void PrintMatrix(Cell matrix[FIELD_SIZE + 2][FIELD_SIZE + 2], ostream &fOut)
{
	for (short i = 1; i <= FIELD_SIZE; i++)
	{
		for (short j = 1; j <= FIELD_SIZE; j++)
		{
			fOut << matrix[i][j].ch;
		}
		fOut << endl;
	}
}

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		cout << "Not all arguments are specified\n";
		return 1;
	}

	ifstream fIn;
	ofstream fOut;
	fIn.open(argv[1]);
	fOut.open(argv[2]);

	if (!fIn.is_open())
	{
		cout << "Failed to open input file\n";
		return 1;
	}
	if (!fOut.is_open())
	{
		cout << "Failed to open output file\n";
		return 1;
	}

	Cell matrix[FIELD_SIZE + 2][FIELD_SIZE + 2];
	Coordinate beginCoordinate, endCoordinate;

	if (!FillMatrix(fIn, matrix, beginCoordinate, endCoordinate))
	{
		cout << "Input error\n";
		return 1;
	}

	CreateFrame(matrix);
	WavePropagation(matrix, beginCoordinate, endCoordinate);

	if (matrix[endCoordinate.x][endCoordinate.y].shortestWay != -1)
	{
		PathRecovery(matrix, endCoordinate);
	}

	PrintMatrix(matrix, fOut);

	return 0;
}