#ifndef _GENETIC_H
#define _GENETIC_H
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;
#define BINARY_LEN			16
#define MAX_GROUP_NUM		100
class Genetic {
	public:
		void setFactorNum(int factorNum);
		void setMutateRate(double mutateRate);
		void setCrossRate(double crossRate);
		void run(int iterate);
		void showOptimalValue(int index);
		Genetic();
		~Genetic();
	private:
		void init();
		void select();
		void crossover();
		void mutate();
		void eliminate();
		void inverse(int index);
		double objectFunction(double x);
		void calculateFitness();
		double decoding(unsigned char* binary);
		int num;
		int index1;
		int index2;
		char group[MAX_NUM][BINARY_LEN];
		double fitness[MAX_NUM];
		double CDF[MAX_NUM];
};
#endif // _GENETIC_H
