#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <cassert>

using namespace std;

void PrintMatrix(const vector<vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& value : row) {
            cout << "|" << setw(8) << value << "|";
        }
        cout << endl;
    }
}

vector<double> DoGaussMethod(vector<vector<double>> matrix, const vector<double>& freeMemb1) {
    int n = matrix.size();
    vector<double> freeMemb(freeMemb1);
    vector<double> x(n);
 

    for (int k = 0; k < n; k++) {
        // finding max elem
        double maxEl = abs(matrix[k][k]);
        int maxRow = k;

        for (int i = k + 1; i < n; i++) {
            if (abs(matrix[i][k]) > maxEl) {
                maxEl = abs(matrix[i][k]);
                maxRow = i;
            }
        }

        // swap current and max row
        swap(matrix[maxRow], matrix[k]);
        swap(freeMemb[maxRow], freeMemb[k]);

        // Normalization
        double leadingElement = matrix[k][k];
        assert(leadingElement != 0 && "IER = 1");

        for (int j = 0; j < n; j++) {
            matrix[k][j] /= leadingElement;
        }
        freeMemb[k] /= leadingElement;

        // zeroing the elements under the leading element
        for (int i = k + 1; i < n; i++) {
            double factor = matrix[i][k];
            for (int j = 0; j < n; j++) {
                matrix[i][j] -= factor * matrix[k][j];
            }
            freeMemb[i] -= factor * freeMemb[k];
        }
    }

    // reverse for finding x
    for (int k = n - 1; k >= 0; k--) {
        double sum = 0;
        for (int j = k + 1; j < n; j++) {
            sum += matrix[k][j] * x[j];
        }
        x[k] = freeMemb[k] - sum;
    }
    PrintMatrix(matrix);
    cout << "X:" << endl;
    for (const auto i : x) {
        cout << i << "   " ;
    }
    cout << endl;

    return x;
}

double FindAccuracy(const vector<vector<double>>& originalMatrix, const vector<double>& x_first) {
    int n = originalMatrix.size();
    vector<double> x_second(n);
    vector<double> freeMemb(n, 0.0);

    // calc of new free member
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            freeMemb[j] += originalMatrix[j][i] * x_first[i];
        }
    }

    auto modifiedMatrix = originalMatrix;

    x_second = DoGaussMethod(modifiedMatrix, freeMemb);

    double acc = 0;
    double dif = abs(x_second[0] - x_first[0]);
    double x_abs = abs(x_first[0]);
    acc = dif / x_abs;

    for (int i = 1; i < n; i++) {
        double curr_dif = abs(x_second[i] - x_first[i]);
        double curr_x_abs = abs(x_first[i]);
        double curr_acc = curr_dif / curr_x_abs;
        if (curr_acc > acc)
        {
            acc = curr_acc;
        }
    }

    cout << "Accuracy: " << acc << endl;

    return acc;
}
