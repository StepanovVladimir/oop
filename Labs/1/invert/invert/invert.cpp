#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

const int MATRIX_SIZE = 3;
const int SUBMATRIX_SIZE = MATRIX_SIZE - 1;

bool FillMatrix(istream &fIn, float matrix[MATRIX_SIZE][MATRIX_SIZE])
{
	string str;
	float f;
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			fIn >> str;
			if (fIn.eof())
			{
				return false;
			}
			istringstream strm(str);
			strm >> f;
			if (!strm)
			{
				return false;
			}
			matrix[i][j] = f;
		}
	}
	return true;
}

void CreateSubmatrix(float matrix[MATRIX_SIZE][MATRIX_SIZE], float submatrix[SUBMATRIX_SIZE][SUBMATRIX_SIZE],
	int matrixIndex1, int matrixIndex2)
{
	int submatrixIndex1 = 0;
	int submatrixIndex2 = 0;
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		if (i != matrixIndex1)
		{
			for (int j = 0; j < MATRIX_SIZE; j++)
			{
				if (j != matrixIndex2)
				{
					submatrix[submatrixIndex1][submatrixIndex2] = matrix[i][j];
					submatrixIndex2++;
				}
			}
			submatrixIndex1++;
			submatrixIndex2 = 0;
		}
	}
}

float GetDetOfSubmatrix(float matrix[SUBMATRIX_SIZE][SUBMATRIX_SIZE])
{
	return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

float GetDetOfMatrix(float matrix[MATRIX_SIZE][MATRIX_SIZE])
{
	float det = 0.f;
	float submatrix[SUBMATRIX_SIZE][SUBMATRIX_SIZE];
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		CreateSubmatrix(matrix, submatrix, 0, i);
		if (i % 2 == 0)
		{
			det += matrix[0][i] * GetDetOfSubmatrix(submatrix);
		}
		else
		{
			det -= matrix[0][i] * GetDetOfSubmatrix(submatrix);
		}
	}
	return det;
}

void TransposeMatrix(float matrix[MATRIX_SIZE][MATRIX_SIZE], float transposedMatrix[MATRIX_SIZE][MATRIX_SIZE])
{
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			transposedMatrix[i][j] = matrix[j][i];
		}
	}
}

void CreateCofactorMatrix(float matrix[MATRIX_SIZE][MATRIX_SIZE], float cofactorMatrix[MATRIX_SIZE][MATRIX_SIZE])
{
	float submatrix[SUBMATRIX_SIZE][SUBMATRIX_SIZE];
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			CreateSubmatrix(matrix, submatrix, i, j);
			if ((i + j) % 2 == 0)
			{
				cofactorMatrix[i][j] = GetDetOfSubmatrix(submatrix);
			}
			else
			{
				cofactorMatrix[i][j] = -GetDetOfSubmatrix(submatrix);
			}
		}	
	}
}

void DivMatrix(float matrix[MATRIX_SIZE][MATRIX_SIZE], float divider)
{
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			matrix[i][j] /= divider;
		}
	}
}

void CalculateInverseMatrix(float matrix[MATRIX_SIZE][MATRIX_SIZE], float inverseMatrix[MATRIX_SIZE][MATRIX_SIZE],
	float det)
{
	float transposedMatrix[MATRIX_SIZE][MATRIX_SIZE];
	TransposeMatrix(matrix, transposedMatrix);
    CreateCofactorMatrix(transposedMatrix, inverseMatrix);
	DivMatrix(inverseMatrix, det);
}

void PrintMatrix(float matrix[MATRIX_SIZE][MATRIX_SIZE])
{
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			ostringstream strm;
			strm << fixed << setprecision(3) << matrix[i][j];
			cout << strm.str() << "  ";
		}
		cout << endl;
	}
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cout << "You have not entered input file\n";
		return 1;
	}

	ifstream fIn;
	fIn.open(argv[1]);

	if (!fIn.is_open())
	{
		cout << "Failed to open input file\n";
		return 1;
	}

	float matrix[MATRIX_SIZE][MATRIX_SIZE];

	if (!FillMatrix(fIn, matrix))
	{
		cout << "Input error\n";
		return 1;
	}

	float det = GetDetOfMatrix(matrix);

	if (det == 0)
	{
		cout << "The determinant is 0, so the inverse matrix cannot be calculated.\n";
	}
	else
	{
		float inverseMatrix[MATRIX_SIZE][MATRIX_SIZE];
		CalculateInverseMatrix(matrix, inverseMatrix, det);
		PrintMatrix(inverseMatrix);
	}

	return 0;
}