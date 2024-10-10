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

vector<double> StraightMove(vector<vector<double>> matrix, const vector<double>& freeMemb1) {
    int n = matrix.size();
    vector<double> freeMemb(freeMemb1);
    vector<double> x(n);
 

    for (int k = 0; k < n; k++) {
        // Поиск максимального элемента для выбора ведущего
        double maxEl = abs(matrix[k][k]);
        int maxRow = k;

        for (int i = k + 1; i < n; i++) {
            if (abs(matrix[i][k]) > maxEl) {
                maxEl = abs(matrix[i][k]);
                maxRow = i;
            }
        }

        // Меняем местами текущую строку и строку с максимальным элементом
        swap(matrix[maxRow], matrix[k]);
        swap(freeMemb[maxRow], freeMemb[k]);

        // Нормализация текущей строки
        double leadingElement = matrix[k][k];
        assert(leadingElement != 0 && "Matrix is singular!");

        for (int j = 0; j < n; j++) {
            matrix[k][j] /= leadingElement;
        }
        freeMemb[k] /= leadingElement;

        // Обнуление элементов под ведущим
        for (int i = k + 1; i < n; i++) {
            double factor = matrix[i][k];
            for (int j = 0; j < n; j++) {
                matrix[i][j] -= factor * matrix[k][j];
            }
            freeMemb[i] -= factor * freeMemb[k];
        }
    }

    // Обратная подстановка для нахождения x
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

    // Вычисление нового свободного члена
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            freeMemb[j] += originalMatrix[j][i] * x_first[i];
        }
    }

    // Создание копии оригинальной матрицы для решения
    auto modifiedMatrix = originalMatrix;

    x_second = StraightMove(modifiedMatrix, freeMemb);

    double acc = 0;
    double dif = abs(x_second[0] - x_first[0]);
    double x_abs = abs(x_first[0]);

    for (int i = 1; i < n; i++) {
        dif = max(dif, abs(x_second[i] - x_first[i]));
        x_abs = max(x_abs, abs(x_first[i]));
    }

    acc = dif / x_abs;
    cout << "Accuracy: " << acc << endl;

    return acc;
}
