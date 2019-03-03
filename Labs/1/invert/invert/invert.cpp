#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <sstream>
#include <iomanip>

using namespace std;

const int MATRIX_SIZE = 3;
const int SUBMATRIX_SIZE = MATRIX_SIZE - 1;

using Matrix = array<array<float, MATRIX_SIZE>, MATRIX_SIZE>;
using Submatrix = array<array<float, SUBMATRIX_SIZE>, SUBMATRIX_SIZE>;

bool FillMatrix(istream &fIn, Matrix &matrix)
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

Submatrix CreateSubmatrix(const Matrix &matrix, int matrixIndex1, int matrixIndex2)
{
	Submatrix submatrix;
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
	return submatrix;
}

float GetDetOfSubmatrix(const Submatrix &submatrix)
{
	return submatrix[0][0] * submatrix[1][1] - submatrix[0][1] * submatrix[1][0];
}

float GetDetOfMatrix(const Matrix &matrix)
{
	float det = 0.f;
	Submatrix submatrix;
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		submatrix = CreateSubmatrix(matrix, 0, i);
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

void TransposeMatrix(Matrix &matrix)
{
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = i + 1; j < MATRIX_SIZE; j++)
		{
			swap(matrix[i][j], matrix[j][i]);
		}
	}
}

Matrix CreateCofactorMatrix(const Matrix &matrix)
{
	Matrix cofactorMatrix;
	Submatrix submatrix;
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			submatrix = CreateSubmatrix(matrix, i, j);
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
	return cofactorMatrix;
}

void DivMatrix(Matrix &matrix, float divider)
{
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			matrix[i][j] /= divider;
		}
	}
}

void CalculateInverseMatrix(Matrix &matrix, float det)
{
	TransposeMatrix(matrix);
	matrix = CreateCofactorMatrix(matrix);
	DivMatrix(matrix, det);
}

void PrintMatrix(const Matrix &matrix)
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

	Matrix matrix;

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
		CalculateInverseMatrix(matrix, det);
		PrintMatrix(matrix);
	}

	return 0;
}