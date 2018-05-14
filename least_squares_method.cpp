#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <numeric>

const double EPS = .0001;
const unsigned int MAX_ORDER = 10;

// prototype declaration
std::vector<std::vector<double>> gauss_jordan(std::vector<std::vector<double>> coeffs, std::vector<std::vector<double>> values);
std::vector<double> least_squares(std::vector<std::vector<double>> points, unsigned int order);
double coeffs_determination(std::vector<std::vector<double>> points, std::vector<double> predicted_points);

int main(int argc, char const *argv[])
{
	std::vector<std::vector<double>> p = {
		{0.0,1.0},
		{1.0,2.0},
		{2.0,1.0},
		{3.0,0.0},
		{4.0,4.0}
	};
	for (unsigned int order = 0; order < MAX_ORDER; order++){
		printf("[order is %d]\n", order);
		std::vector<double> ans = least_squares(p, order);
		for (unsigned int i = 0; i < ans.size(); i++){
			printf("A %d = %6.3lf\n", i, ans[i]);
		}
		printf("R2 = %6.7lf\n", coeffs_determination(p, ans));
	}
	return 0;
}

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

std::vector<double> least_squares(std::vector<std::vector<double>> points, unsigned int order){
	std::vector<std::vector<double>> coeffs(order + 1, std::vector<double>(order + 1));
	std::vector<std::vector<double>> values(order + 1, std::vector<double>(order + 1));
	// create equation
	for(unsigned int i = 0; i < order + 1; ++i){
		for(unsigned int j = 0; j < order + 1; j++){
			for(std::vector<double> p : points){
				coeffs[j][i] += std::pow(p[0], (double)(i+j));
				values[j][i] += p[1] * std::pow(p[0], (double)j);
			}
		}
	}
	// solve
	std::vector<std::vector<double>> answers = gauss_jordan(coeffs, values);
	if(answers.empty()){
		return {};
	}else{
		std::vector<double> ans;
		for (unsigned int i = 0; i < answers.size(); i++){
			ans.push_back(answers[i][0]);
		}
		return ans;
	}
}

double coeffs_determination(std::vector<std::vector<double>> points, std::vector<double> predicted_points){
	std::vector<double> v1,v2;
	unsigned int min_loop = std::min(points.size(), predicted_points.size());
	double average;
	for (unsigned int i = 0; i < points.size(); i++){
		average += points[i][1];
	}
	average /= points.size();

	// get something like variance
	for (unsigned int i = 0; i < min_loop; i++){
		v1.push_back(std::pow(points[i][1] - predicted_points[i], 2));
		v2.push_back(std::pow(points[i][1] - average, 2));
	}
	return 1 - (std::accumulate(v1.begin(), v1.end(), 0.0) / std::accumulate(v2.begin(), v2.end(), 0.0));
}
