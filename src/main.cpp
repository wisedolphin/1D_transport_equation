#include "Config/Config.h"
#include "Zone/Zone.h"
#include <string>
#include <omp.h>
#include <iostream>



int main(int argc, char* argv[])
{
    //Geting working dir path
    std::string work_dir_path;
    if (argc!=2)
    {
        std::cout << "Pass working dir path as the first argument\n";
        std::cout << "Exapmle: .\\" << argv[0] << " \"/home/work_dir\"\n";
        exit(-1);

    }
    work_dir_path = argv[1];
    //Creating path to config.json
    std::string config_file = "config.json";
    std::string config_path = work_dir_path + config_file;
    //Creating configuration from json-file
    config config(config_path);
    //setting number of omp threads
    omp_set_num_threads(config.Multiprocessing.threads_num);
    //Creating Zone
    Zone zone(config.Domain.N,
              config.Domain.L,
              config.Fluid.lambda,
              config.IC,
              config.BC.Uleft,
              config.BC.Uright
              );
    //iteration cycle
    int iter = 0;
    zone.save_field(work_dir_path, iter);
    while (iter < config.Timestep.NIter)
    {
        ++iter;
        // TODO choose fluxes approx through config
        //zone.Fluxes_CIR(config.Fluid.lambda);
        zone.Fluxes_MUSCL(config.Fluid.lambda, config.Domain);
        zone.calc_next_step(config.Domain, config.Fluid, config.Timestep);
        if (iter % config.Result.Save_freq == 0)
        {
            zone.save_field(work_dir_path, iter);
        }
        zone.BC_apply(config.BC.Uleft, config.BC.Uright);
    }
    std::cout << "All done!";

	return 0;
}
