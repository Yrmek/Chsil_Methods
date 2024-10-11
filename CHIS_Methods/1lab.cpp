// 3var;

#include "methods.h"

int main() {
	vector<vector<double>> matrix{  {2.3 , 5.7 , -0.8} ,
									{3.5, -2.7 , 5.3 },
									{1.7 , 2.3 , -1.8 } };
	vector<double> freeMemb{ -6.49 , 19.20, -5.09 };
 	cout << matrix.size();
PrintMatrix(matrix);
cout << endl;
vector<double> x = DoGaussMethod(matrix, freeMemb);

FindAccuracy(matrix, x);
	return 0;
}