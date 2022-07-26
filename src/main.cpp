#include "Config/Config.h"
#include "Zone/Zone.h"
#include <string>
#include <omp.h>
#include <stdexcept>
#include <iostream>
#include <filesystem>


int main(int argc, char* argv[])
{
    //Geting working dir path
    std::string work_dir_path;
    if (argc!=2)
    {
        std::cout << "Pass working dir path as the first argument\n";
        std::cout << "Exapmle: ." << argv[0] << "application.exe \"/home/work_dir\"\n";
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
    while (iter < config.Timestep.NIter)
    {

    }


	return 0;
}
