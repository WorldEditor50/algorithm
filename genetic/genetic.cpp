#include "genetic.h"

void Genetic::run(int iterate)
{
	this->init();
	for (int i = 0; i < iterate; i++) {
		this->select();
		this->crossover();
		this->mutate();
		this->eliminate();	
	}
	return;
}

void Genetic::eliminate()
{
	/* sort */
	unsigned char tmp[BINARY_LEN + 1];
	for (int i = 0; i < factorNum - 1; i++) {
		for (int j = i + 1; j < factorNum; j++) {
			if (group[i].fitness < group[j].fitness) {
				memcpy(tmp, group[i].binary, BINARY_LEN +1);
				memcpy(group[i].binary, group[j].binary, BINARY_LEN +1);
				memcpy(group[j].binary, tmp, BINARY_LEN +1);
			}
		}
	}
	/* eliminate */
	int k = rand() % (factorNum / 10);
	int x = 0;
	for (int i = factorNum - k; i < factorNum; i++) {
		x = rand() % k;
		memcpy(group[i].binary, group[x].binary, BINARY_LEN +1);
	}
	/* show */
	this->showOptimalValue(0);
	return;
}

void Genetic::select()
{
	int k = 0;
	int index[2];
	double p = 0;
	p = (double)(rand() % 1000) / 1000;
	this->calculateFitness();
	if (p <= group[0].accumulateFitness) {
		index[k] = 0;
		k++;
	} else {
		for (int i = 1; i < factorNum - 1; i++) {
			if (p > group[i].accumulateFitness && p <= group[i + 1].accumulateFitness) {
				index[k] = i + 1;
				k++;
				if (k == 2) {
					break;
				}
			}
		}
	}
	this->index1 = index[0];
	this->index2 = index[1];
	return;
}

void Genetic::crossover()
{
	int k = rand() % 100;
	if (k > 80 || k < 20) {
		return;
	}
	cout<<"cross over"<<endl;
	int begin = 0;
	int end = 0;
	begin = rand() % (BINARY_LEN + 1);
	end = rand() % (BINARY_LEN + 1);
	if (begin == end) {
		end = (begin + BINARY_LEN / 2) % (BINARY_LEN + 1);
	}
	if (begin > end) {
		int tmp = end;
		end = begin;
		begin = tmp;
	}
	for (int i = begin; i < end + 1; i++) {
		unsigned char bit = group[index1].binary[i];
		group[index1].binary[i] = group[index2].binary[i];
		group[index2].binary[i] = bit;
	}
	return;
}

void Genetic::mutate()
{
	int k = rand() % 1000;
	if (k > 50 && k < 950) {
		return;
	}
	cout<<"mutate"<<endl;
	this->inverse(index1);
	this->inverse(index2);
	return;
}

void Genetic::inverse(int index)
{
	int i = 0;
	i = rand() % (BINARY_LEN + 1);
	if (group[index].binary[i] == 1) {
		group[index].binary[i] = 0;
	} else {
		group[index].binary[i] = 1;
	}
	return;
}

void Genetic::calculateFitness()
{
	double sum = 0.0;
	double value = 0.0;
	/* calulate fitness */
	for (int i = 0; i < factorNum; i++) {
		value = decoding(group[i].binary);
		group[i].fitness = objectFunction(value);
		sum += group[i].fitness;
	}
	/* calulate relative fitness */
	for (int i = 0; i < factorNum; i++) {
		group[i].relativeFitness = group[i].fitness /sum;
	}
	/* calculate accumulate fitness */
	group[0].accumulateFitness = group[0].relativeFitness;
	for (int i = 1; i < factorNum; i++) {
		group[i].accumulateFitness = group[i - 1].accumulateFitness + group[i].relativeFitness;
	}
	return;
}

void Genetic::init()
{
	for (int i = 0; i < factorNum; i++) {
		for (int j = 0; j < BINARY_LEN + 1; j++) {
			group[i].binary[j] = (unsigned char)rand() % 2;
		}
		group[i].fitness = 0.0;	
		group[i].relativeFitness = 0.0;	
		group[i].accumulateFitness = 0.0;	
	}
	return;
}

double Genetic::decoding(unsigned char* binary)
{
	double value = 0.0;
	int mid = BINARY_LEN / 2;
	for (int i = 0; i < BINARY_LEN + 1; i++) {
		value += (double)binary[i] * pow(2, mid - i - 1);
	}
	if (binary[BINARY_LEN] == 1) {
		value = -1 * value;
	}
	return value;
}

double Genetic::objectFunction(double x)
{
	return 10 * x - x * x * x / 10000 - 1000;
}

Genetic::Genetic()
{
	this->factorNum = MAX_GROUP_NUM / 10;
	this->crossRate = 0.6;
	this->mutateRate = 0.3;
	this->index1 = 0;
	this->index2 = 1;
}

Genetic::~Genetic()
{

}

void Genetic::setFactorNum(int factorNum)
{
	this->factorNum = factorNum;
	return;
}

void Genetic::setMutateRate(double mutateRate)
{
	this->mutateRate = mutateRate;
	return;
}

void Genetic::setCrossRate(double crossRate)
{
	this->crossRate = crossRate;
	return;
}

void Genetic::showOptimalValue(int index)
{
	double value = 0.0;
	double fitness = 0.0;
	value = decoding(group[index].binary);
	fitness = objectFunction(value);
	cout <<"value = "<<value<<"    "<<"fitness = "<<fitness<<endl;
	return;
}
