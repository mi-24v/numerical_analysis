/**
 * 数値積分
 * trapezoidalRule : 台形公式による数値積分
 * simpsonRule : シンプソンの公式による数値積分
 * */

#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <numeric>
#include <iterator>
#include <functional>

const unsigned int MIN_TRY = 5;
const unsigned int MAX_TRY = 16;

//prototype declaration
double trapezoidalRule(std::function<double(double)> func, double start, double end, unsigned int numberInterval); // 台形公式
double simpsonRule(std::function<double(double)> func, double start, double end, unsigned int numberInterval); // シンプソンの公式

int main(int argc, char const *argv[]){
	//input function
	std::function<double(double)> func_y = [](double x){
		return 1.0 / x;
	};
	const double xa = 1.0,
				xb = 2.0;
	double trapezoidalValue = 0.0,
				simpsonValue = 0.0;
	for(unsigned int N = MIN_TRY; N <= MAX_TRY; N++){
		printf("[step N=%d]\n", N);
		trapezoidalValue = trapezoidalRule(func_y, xa, xb, std::pow(2, N));
		simpsonValue = simpsonRule(func_y, xa, xb, std::pow(2, N));
		printf("trapezoidal rule ans:%11.10lf\n", trapezoidalValue);
		printf("Simpson's rule ans:%11.10lf\n", simpsonValue);
	}
	return 0;
}

double trapezoidalRule(std::function<double(double)> func, double start, double end, unsigned int numberInterval){
	// number of steps
	double step = (end - start) / numberInterval;
	// get function plots
	std::vector<double> points;
	for (unsigned int i = 0; i <= numberInterval; ++i){
		double in = start + step * (double)i; // x point
		points.push_back(func(in)); // y point
	}

	// get height sum
	double height = std::accumulate(std::next(points.begin()), std::prev(points.end()), 0.0, [](double init, double x){
		return init + x * 2.0;
	});
	// get area sum (= numerical integral)
	return (step / 2.0) * ( points.front() + height + points.back() );
}

double simpsonRule(std::function<double(double)> func, double start, double end, unsigned int numberInterval){
	// number of steps
	double step = (end - start) / numberInterval;
	// get function plots
	std::vector<double> points;
	for (unsigned int i = 0; i <= numberInterval; ++i){
		double in = start + step * (double)i; // x point
		points.push_back(func(in)); // y point
	}

	// get height sum (odds)
	double heightOdd = 0.0;
	for (unsigned int i = 1; i < points.size() - 1; i+= 2){
		heightOdd += 4.0 * points[i];
	}
	// get height sum (evens)
	double heightEven = 0.0;
	for (unsigned int i = 2; i < points.size() - 1; i+= 2){
		heightEven += 2.0 * points[i];
	}
	// get area sum (= numerical integral)
	return (step / 3.0) * ( points.front() + heightOdd + heightEven + points.back() );
}
