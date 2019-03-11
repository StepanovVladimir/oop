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

using Matrix3x3 = array<array<float, MATRIX_SIZE>, MATRIX_SIZE>;
using Matrix2x2 = array<array<float, SUBMATRIX_SIZE>, SUBMATRIX_SIZE>;

bool FillMatrix(const string &fileName, Matrix3x3 &matrix)
{
	ifstream fIn;
	fIn.open(fileName);
	if (!fIn.is_open())
	{
		return false;
	}
	
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

Matrix2x2 CreateSubmatrix(const Matrix3x3 &matrix, int matrixIndex1, int matrixIndex2)
{
	Matrix2x2 submatrix;
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

float GetDetOfMatrix2x2(const Matrix2x2 &matrix)
{
	return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

float GetDetOfMatrix3x3(const Matrix3x3 &matrix)
{
	float det = 0.f;
	Matrix2x2 submatrix;
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		submatrix = CreateSubmatrix(matrix, 0, i);
		if (i % 2 == 0)
		{
			det += matrix[0][i] * GetDetOfMatrix2x2(submatrix);
		}
		else
		{
			det -= matrix[0][i] * GetDetOfMatrix2x2(submatrix);
		}
	}
	return det;
}

Matrix3x3 CreateCofactorMatrix(const Matrix3x3 &matrix)
{
	Matrix3x3 cofactorMatrix;
	Matrix2x2 submatrix;
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			submatrix = CreateSubmatrix(matrix, i, j);
			if ((i + j) % 2 == 0)
			{
				cofactorMatrix[i][j] = GetDetOfMatrix2x2(submatrix);
			}
			else
			{
				cofactorMatrix[i][j] = -GetDetOfMatrix2x2(submatrix);
			}
		}
	}
	return cofactorMatrix;
}

void TransposeMatrix(Matrix3x3 &matrix)
{
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = i + 1; j < MATRIX_SIZE; j++)
		{
			swap(matrix[i][j], matrix[j][i]);
		}
	}
}

void DivMatrix(Matrix3x3 &matrix, float divider)
{
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			matrix[i][j] /= divider;
		}
	}
}

bool CalculateInverseMatrix(const Matrix3x3 &matrix, Matrix3x3 &inverseMatrix)
{
	float det = GetDetOfMatrix3x3(matrix);
	if (det == 0)
	{
		return false;
	}
	inverseMatrix = CreateCofactorMatrix(matrix);
	TransposeMatrix(inverseMatrix);
	DivMatrix(inverseMatrix, det);
	return true;
}

void PrintMatrix(const Matrix3x3 &matrix)
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

	Matrix3x3 matrix;
	if (!FillMatrix(argv[1], matrix))
	{
		cout << "Input error\n";
		return 1;
	}

	Matrix3x3 inverseMatrix;
	if (!CalculateInverseMatrix(matrix, inverseMatrix))
	{
		cout << "The determinant is 0, so the inverse matrix cannot be calculated.\n";
	}
	else
	{
		PrintMatrix(inverseMatrix);
	}

	return 0;
}