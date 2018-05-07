//ラグランジュの補間法
/**
 * 1.C++標準ライブラリ関数によるN個のsin値を基本データとする.
 * 2.基本データを元にラグランジュの補間法を用いてsin(0.923)を求める.
 * 3.データサイズNを変更して1,2を繰り返し,出力を比較する
 * 
 * 結果:N>=3ならば小数点以下7桁において正しい結果を計算することが可能.
 * */
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>

#define N	1
#define MAXTRY 10
#define TARGET 0.923

using namespace std;

double lagrange(double xx, vector<double> x, vector<double> y);

int main(int argc, char **argv){
	//exact sin values container
	vector<double> x, y;
	for(int maxNumber = N; maxNumber < N+MAXTRY; maxNumber++){
		//set up exact sin values
		printf("|data size N = %d|\n", maxNumber);
		printf("[exact sin values]\nX\t\t\tY\n");
		for(int i=0; i < maxNumber; i++){
			x.push_back(0.92+0.01*i);
			y.push_back(sin(x[i]));
			printf(" %8.7lf\t%-8.7lf\n", x[i], y[i]);
		}
		printf("[exact sin(%4.3f) value]\n%8.7lf\n", TARGET, sin(TARGET));
		
		//calulate by lagrange method
		double yy = lagrange(TARGET, x, y);
		printf("[calculated sin(%4.3f) value]\n%8.7lf\n", TARGET, yy);
		
		//clear container
		x.clear();
		y.clear();
	}
	return 0;
}

double lagrange(double xx, vector<double> x, vector<double> y){
	vector<double> z(y.size(), 1.0);
	double yy = 0.0;

	for (size_t k = 0; k < y.size(); k++){
		for (size_t i = 0; i < x.size(); i++){
			if (i != k){
				z[k] *= (xx - x[i]) / (x[k] - x[i]);
			}
		}
		yy += y[k] * z[k];
	}
	return yy;
}
