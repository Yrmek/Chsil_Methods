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

vector<double> StraightMove(vector<vector<double>> matrix, vector<double> freeMemb) {
	vector<double> x(matrix.size());
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
			for (int j = k ; j < matrix.size(); j++) {
				matrix[l][j] = matrix[l][j] - matrix[l][k] * matrix[M][j];
			}
			freeMemb[l] = freeMemb[l] - matrix[l][k] * freeMemb[M];
		}
		k++;
		
		if (k < matrix.size()) {
			continue;
		}
		else {
			assert(matrix[l][matrix.size() - 1] && "IER = 1");
			l = IOR[matrix.size() - 1];
			freeMemb[l] = freeMemb[l] / matrix[l][matrix.size() - 1];
			x[matrix.size() - 1] = freeMemb[l];
			break;
		}
	}
	PrintMatrix(matrix);
	for (auto i : freeMemb) {
		cout << i <<" ";
	}
	cout << endl;

	for ( k = matrix.size() - 1; k >= 0; k--) {
		int l = IOR[k];
		double sum = 0;
		for (int j = k + 1; j < matrix.size(); j++) {
			sum += matrix[l][j] * x[j];
		}
		x[k] = freeMemb[l] - sum;
	}

	for (auto i : x) {
		cout << i << " ";
	}

	return x;
}

double FindAccuracy(vector<vector<double>> matrix, vector<double> x_first)
{
	vector<double> x_second(x_first.size());
	vector<double> freeMemb(x_first.size());
	for (int j = 0; j < matrix.size() ; j++) {
		for (int i = 0; i < matrix.size(); i++) {
			freeMemb[j] += matrix[j][i] * x_first[i];
		}
	}
	x_second = StraightMove(matrix, freeMemb);
	double acc = 0;
	double dif = abs(x_second[0] - x_first[0]);
	double x_abs = abs(x_first[0]);
	for (int i = 1; i < x_first.size(); i++) {
		if (dif < abs(x_second[i] - x_first[i])) {
			dif = abs(x_second[i] - x_first[i]);
		}
		if (x_abs < abs(x_first[i])) {
			x_abs = abs(x_first[i]);
		}
	}

	acc = dif / x_abs;
	cout << "Accuracy: " << acc;
	return acc;
}


