#include "genetic.h"

int main()
{
	srand((unsigned int)time(NULL));
	Genetic g;
	g.setFactorNum(99);
	g.run(30);
	return 0;
}
