/**
 * 常微分方程式
 * forward_euler_method : オイラー法(オイラーの前進公式)
 * runge_kutta_method : ルンゲ=クッタの公式
 * */

#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <numeric>
#include <iterator>
#include <utility>
#include <functional>

const double EPS = .00000001;

//prototype declaration
std::vector<std::pair<double, double>> forward_euler_method(std::function<double(double)> func, double start, double end, double step, double cycle);
double runge_kutta_method();

int main(int argc, char const *argv[]){
	std::function<double(double, double)> func_f = [](double x, double y){
		return (3.0 * y) / (1.0 + x);
	};
	std::function<double(double)> func_ff = [](double x){
		return 2.0 * x;
	};
	const double start = 0.0,
				end = 10.0,
				step = 0.01,
				cycle = 1.0;
	std::vector<std::pair<double, double>> euler_values = forward_euler_method(func_ff, start, end, step, cycle);
	printf("  X\t  Y\t\n");
	for(std::pair<double, double> point : euler_values){
		printf("%7.4lf %7.4lf\n", point.first, point.second);
	}
	return 0;
}

std::vector<std::pair<double, double>> forward_euler_method(std::function<double(double)> func, double start, double end, double step, double cycle){
	double x = 0.0,
			y = 0.0,
			term = 0.0;
	std::vector<std::pair<double, double>> values;
	do{
		if(x >= term - EPS){
			term += cycle;
			std::pair<double,double> point = std::make_pair(x,y);
			values.push_back(point);
		}
		y += step * func(x);
		x += step;
	} while (x <= end);
	return values;
}

double runge_kutta_method(){}
