#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <cassert>

using namespace std;

void PrintMatrix(vector<vector<double>> matrix)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix.size(); j++)
		{
			cout << "|" << setw(3) << matrix[i][j] << "|";
		}
		cout << endl;
	}
}

vector<vector<double>> StraightMove(vector<vector<double>> matrix, vector<double> freeMemb) {

	vector<double> IOR(matrix.size());
	for (int k = 0; k < matrix.size(); k++) {
		IOR[k] = k;
	}
	int k = 0;
	int p = 0;
	int M = 0;
	while (true) {

		double AKK = 0;
		int l = 0;

		for (int i = k; i < matrix.size(); i++) {
			l = IOR[i];
			if (matrix[l][k] < AKK) {
				continue;
			}
			else {
				M = l;
				p = i;
				AKK = abs(matrix[l][k]);
				break;
			}
		}

		if (p != k) {
			IOR[p] = IOR[k];
			IOR[k] = M;
		}

		double AMAIN = matrix[M][k];
		assert(AMAIN && "IER = 1");

		for (int j = 0; j < matrix.size(); j++) {
			matrix[M][j] = matrix[M][j] / AMAIN;
		}

		freeMemb[M] = freeMemb[M] / AMAIN;

		for (int i = k + 1; i < matrix.size(); i++) {
			l = IOR[i];
			for (int j = k + 1; j < matrix.size(); j++) {
				matrix[l][j] = matrix[l][j] - matrix[l][k] * matrix[M][j];
			}
			freeMemb[l] = freeMemb[l] - matrix[l][k] * freeMemb[M];
		}
		k++;
		assert(matrix[l][matrix.size() - 1] && "IER = 1");
		if (k < matrix.size()) {
			continue;
		}
		else {
			break;
		}
	}
	PrintMatrix(matrix);
	return matrix;
}

