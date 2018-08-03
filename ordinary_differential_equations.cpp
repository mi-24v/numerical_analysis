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

class RunngeKutta{
public:
	//RunngeKutta(RKStage stage);
	RunngeKutta(unsigned int stage, std::vector<std::vector<double>> rk_matrix, std::vector<double> rk_weights, std::vector<double> rk_nodes);
	~RunngeKutta();

	std::vector<std::pair<double, double>> runge_kutta_method(std::function<double(double, double)> func, double start, double end, double step, double cycle);

	// 1st-stage runnge-kutta(euler method)
	const static RunngeKutta RK1;
	//2nd-stage runnge-kutta
	const static RunngeKutta RK2;
	//4th-stage runnge-kutta
	const static RunngeKutta RK4;

private:
	// stage size.
	unsigned int rk_stage;

	// actual using coeffs.
	std::vector<std::vector<double>> rk_matrix;
	std::vector<double> rk_weights;
	std::vector<double> rk_nodes;

};

int main(int argc, char const *argv[]){
	std::function<double(double, double)> func_f = [](double x, double y){
		return (3.0 * y) / (1.0 + x);
	};
	std::function<double(double)> func_ff = [](double x){
		return 2.0 * x;
	};
	std::function<double(double, double)> func_fff = [](double x, double y){
		return 2.0 * x;
	};

	const double start = 1.0,
				end = 3.0,
				step = 0.01,
				cycle = 0.2;
	RunngeKutta rk1(RunngeKutta::RK1), rk2(RunngeKutta::RK2), rk4(RunngeKutta::RK4);
	//std::vector<std::pair<double, double>> euler_values = forward_euler_method(func_ff, start, end, step, cycle);
	std::vector<std::pair<double, double>> euler_values = rk1.runge_kutta_method(func_f, start, end, step, cycle);
	auto rk2_values = rk2.runge_kutta_method(func_f, start, end, step, cycle);
	auto rk4_values = rk4.runge_kutta_method(func_f, start, end, step, cycle);
	printf("[euler values]\n");
	printf("  X\t, Y\t\n");
	for(std::pair<double, double> point : euler_values){
		printf("%7.4lf,%7.4lf\n", point.first, point.second);
	}
	printf("[RK2 values]\n");
	printf("  X\t, Y\t\n");
	for(std::pair<double, double> point : rk2_values){
		printf("%7.4lf,%7.4lf\n", point.first, point.second);
	}
	printf("[RK4 values]\n");
	printf("  X\t, Y\t\n");
	for(std::pair<double, double> point : rk4_values){
		printf("%7.4lf,%7.4lf\n", point.first, point.second);
	}

	return 0;
}

std::vector<std::pair<double, double>> forward_euler_method(std::function<double(double)> func, double start, double end, double step, double cycle){
	double x = start,
			y = start,
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

// 1st-stage runnge-kutta(euler method)
const RunngeKutta RunngeKutta::RK1 = RunngeKutta(
		1,
		{{0}},//RK matrix
		{1},//RK weights
		{0}//RK nodes
	);
//2nd-stage runnge-kutta
const RunngeKutta RunngeKutta::RK2 = RunngeKutta(
		2,
		{{0,0},
		 {1,0}},
		{0.5, 0.5},
		{0, 1}
	);
//4th-stage runnge-kutta
constexpr double rk4_weight_1 = 1.0/6.0;
constexpr double rk4_weight_2 = 1.0/3.0;
const RunngeKutta RunngeKutta::RK4 = RunngeKutta(
		4,
		{{0, 0, 0,0},
		 {0.5,0,0,0},
		 {0,0.5,0,0},
		 {0, 0, 1,0}},
		{rk4_weight_1, rk4_weight_2, rk4_weight_2, rk4_weight_1},
		{0, 0.5, 0.5, 1}
	);

RunngeKutta::RunngeKutta(unsigned int stage, std::vector<std::vector<double>> rk_matrix, std::vector<double> rk_weights, std::vector<double> rk_nodes){
	this->rk_stage = stage;
	this->rk_matrix = rk_matrix;
	this->rk_weights = rk_weights;
	this->rk_nodes = rk_nodes;
}

RunngeKutta::~RunngeKutta(){
}

std::vector<std::pair<double, double>> RunngeKutta::runge_kutta_method(std::function<double(double, double)> func, double start, double end, double step, double cycle){
	double x = start,
			y = start,
			term = 0.0;
	std::vector<double> approximations;
	std::vector<std::pair<double, double>> values;

	do{
		if(x >= term - EPS){
			term += cycle;
			std::pair<double,double> point = std::make_pair(x,y);
			values.push_back(point);
		}
		// obtain approximations.
		for(unsigned int i = 0; i < rk_stage; i++){
			double approximation_sum = 0;
			for(unsigned int j = 1; j < i - 1; j++){
				if(j >= approximations.size())break;
				approximation_sum += rk_matrix[i][j] * approximations[j];
			}
			double x_value = x + step * rk_nodes[i];
			double y_value = y + step * approximation_sum;
			approximations.push_back(func(x_value, y_value));
		}
		// apply
		double sum = 0.0;
		for(unsigned int i = 0; i < rk_stage; i++){
			sum += step * rk_weights[i] * approximations[i];
		}

		y += sum;
		x += step;
		approximations.clear();
	} while (x <= end);
	return values;
}
