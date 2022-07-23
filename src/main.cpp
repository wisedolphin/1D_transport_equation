#include "src/config/Config.h"
#include "src/zone/Zone.h"
#include <omp.h>

int main() 
{
	config config();
    omp_set_num_teams(config.Threads);


	return 0;
}
