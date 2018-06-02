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
#include <unordered_map>

const double EPS = .00000001;

//prototype declaration
std::vector<std::pair<double, double>> forward_euler_method(std::function<double(double)> func, double start, double end, double step, double cycle);

enum class RKStage{
	RK1,
	RK2,
	RK4
};

class RunngeKutta{
public:
	RunngeKutta(RKStage stage);
	~RunngeKutta();

	std::vector<std::pair<double, double>> runge_kutta_method(std::function<double(double, double)> func, double start, double end, double step, double cycle);

private:
	// enum that determine which table should be use
	RKStage rk_stage;

	// actual using coeffs.
	std::unordered_map<std::string, std::vector<double>> rk_coeffs;

	// Butcher Table
	// key definition
	const static std::string RK_matrix,
		RK_weights,
		RK_nodes;
	// const static array
	// 1st-stage runnge-kutta(euler method)
	const static std::unordered_map<std::string, std::vector<double>> RK1;
	//2nd-stage runnge-kutta
	const static std::unordered_map<std::string, std::vector<double>> RK2;
	//4th-stage runnge-kutta
	const static std::unordered_map<std::string, std::vector<double>> RK4;
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

	const double start = 0.0,
				end = 10.0,
				step = 0.01,
				cycle = 1.0;
	RunngeKutta rk2(RKStage::RK2), rk4(RKStage::RK4);
	std::vector<std::pair<double, double>> euler_values = forward_euler_method(func_ff, start, end, step, cycle);
	auto rk2_values = rk2.runge_kutta_method(func_fff, start, end, step, cycle);
	auto rk4_values = rk4.runge_kutta_method(func_fff, start, end, step, cycle);
	printf("  X\t  Y\t\n");
	for(std::pair<double, double> point : euler_values){
		printf("%7.4lf %7.4lf\n", point.first, point.second);
	}
	printf("  X\t  Y\t\n");
	for(std::pair<double, double> point : rk2_values){
		printf("%7.4lf %7.4lf\n", point.first, point.second);
	}
	printf("  X\t  Y\t\n");
	for(std::pair<double, double> point : rk4_values){
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

const std::string RunngeKutta::RK_matrix = "RK_matrix",
		RunngeKutta::RK_weights = "weights",
		RunngeKutta::RK_nodes = "nodes";

// 1st-stage runnge-kutta(euler method)
const std::unordered_map<std::string, std::vector<double>> RunngeKutta::RK1 = {
		{RK_matrix, {0}},
		{RK_weights, {1}},
		{RK_nodes, {0}}
	};
//2nd-stage runnge-kutta
const std::unordered_map<std::string, std::vector<double>> RunngeKutta::RK2 = {
	{RK_matrix, {0, 1}},
	{RK_weights, {0.5, 0.5}},
	{RK_nodes, {0, 1}}
};
//4th-stage runnge-kutta
//FIXME maybe invalid..?
const std::unordered_map<std::string, std::vector<double>> RunngeKutta::RK4 = {
	{RK_matrix, {0, 0.5, 0.5, 1}},
	{RK_weights, {1/6, 1/3, 1/3, 1/6}},
	{RK_nodes, {0, 0.5, 0.5, 1}}
};

RunngeKutta::RunngeKutta(RKStage stage) {
	// init rk coeffs.
	switch(stage){
		case RKStage::RK1:
			rk_coeffs = RunngeKutta::RK1;
			break;
		case RKStage::RK2:
			rk_coeffs = RunngeKutta::RK2;
			break;
		case RKStage::RK4:
		default:
			rk_coeffs = RunngeKutta::RK4;
	}
}

RunngeKutta::~RunngeKutta(){
}

std::vector<std::pair<double, double>> RunngeKutta::runge_kutta_method(std::function<double(double, double)> func, double start, double end, double step, double cycle){
	double x = 0.0,
			y = 0.0,
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
		for(unsigned int i = 0; i < std::min(rk_coeffs[RK_matrix].size(), rk_coeffs[RK_nodes].size()); i++){
			double y_value =
				i == 0?
				y + step * rk_coeffs[RK_matrix][i]:
				y + step * rk_coeffs[RK_matrix][i] * approximations[i-1];
			approximations.push_back(func(x+step*rk_coeffs[RK_nodes][i], y_value));
		}
		// apply
		double sum = 0;
		for(unsigned int i = 0; i < rk_coeffs[RK_weights].size(); i++){
			sum += step * rk_coeffs[RK_weights][i] * approximations[i];
		}

		y += sum;
		x += step;
		approximations.clear();
	} while (x <= end);
	return values;
}
