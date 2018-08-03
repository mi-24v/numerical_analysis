//���O�����W���̕�Ԗ@
/**
 * 1.C++�W�����C�u�����֐��ɂ��N��sin�l����{�f�[�^�Ƃ���.
 * 2.��{�f�[�^�����Ƀ��O�����W���̕�Ԗ@��p����sin(0.923)�����߂�.
 * 3.�f�[�^�T�C�YN��ύX����1,2���J��Ԃ�,�o�͂��r����
 * 
 * ����:N>=3�Ȃ�Ώ����_�ȉ�7���ɂ����Đ��������ʂ��v�Z���邱�Ƃ��\.
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
