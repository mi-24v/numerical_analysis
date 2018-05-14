#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <algorithm>

const double EPS = .001;

std::vector<std::vector<double>> gauss_jordan(std::vector<std::vector<double>> coeffs, std::vector<std::vector<double>> values){
	unsigned int min_loop = std::min(coeffs.size(), values.size());
	// for debug
	// printf("min_loop:%d\n", min_loop);
	for(unsigned int i=0; i < coeffs.size(); i++){
		double pivot = coeffs[i][i];
		if(abs(pivot) < EPS){
			printf("ERROR: too small pivot.\n");
			return {};
		}
		// normalize
		for(unsigned int j=0; j < min_loop; j++){
			coeffs[i][j] /= pivot;
			values[i][j] /= pivot;
		}
		// hakidashi
		for(unsigned int k=0; k < coeffs.size(); k++){
			double delta = coeffs[k][i];
			for(unsigned int l=0; l < min_loop; l++){
				if(k != i){
					coeffs[k][l] -= delta * coeffs[i][l];
					values[k][l] -= delta * values[i][l];
				}
			}
		}
	}
	// concat vector
	// if(coeffs.size() < values.size()){
	// 	coeffs.reserve(values.size());
	// }
	// std::copy(values.begin(), values.end(), std::back_inserter(coeffs));
	// return coeffs;
	return values;
}

int main(int argc, char* argv[]){
	std::vector<std::vector<double>> c = {
		{2,1,3},
		{1,3,2},
		{3,2,1}
	};
	// for solve
	std::vector<std::vector<double>> v1 = {
		{13,0,0},
		{13,0,0},
		{10,0,0}
	};
	// for inverse matrix
	std::vector<std::vector<double>> v2 = {
		{1,0,0},
		{0,1,0},
		{0,0,1}
	};
	std::vector<std::vector<double>> ans = gauss_jordan(c,v1);
	std::vector<std::vector<double>> inverse_matrix = gauss_jordan(c,v2);
	printf("result is:\n");
	for (unsigned int i = 0; i < ans.size(); i++){
		printf("x%d = %6.2lf\n", i, ans[i][0]);
	}
	printf("inverse matrix is:\n");
	for(std::vector<double> v : inverse_matrix){
		printf("[");
		for(double a : v){
			printf(" %6.10lf ",a);
		}
		printf("]\n");
	}
	return 0;
}
