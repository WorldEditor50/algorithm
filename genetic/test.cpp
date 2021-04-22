#include "genetic.h"

int main()
{
	srand((unsigned int)time(NULL));
	Genetic g(0.6, 0.1, 100, 32);
	g.run(OPT_MAX, 1000);
	return 0;
}
