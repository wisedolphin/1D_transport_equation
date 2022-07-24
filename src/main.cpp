#include "Config/Config.h"
#include "Zone/Zone.h"
#include <string>
#include <omp.h>
#include <stdexcept>
#include <iostream>
#include <filesystem>

template <double Uval, double Xbound_left, double Xbound_right>
double initial(double X)
{
    if (X>Xbound_left && X<Xbound_right) {return Uval;}
    else {return 0;}
}

int main(int argc, char* argv[])
{
    //Geting working dir path
    std::string work_dir_path;
    try{
        work_dir_path = argv[1];
    }
    catch(std::logic_error &e){
        std::cout << "Pass working dir path as the first argument\n";
        std::cout << "Exapmle: \"./" << argv[0] << " /home/work_dir\n";
    }
    std::string config_file = "config.json";
    std::string config_path = work_dir_path + config_file;
    //Creating configuration from json-file
    config config(config_path);
    //setting number of omp threads
    omp_set_num_teams(config.Multiprocessing.threads_num);

    //Creating domain
    try {
        Zone zone(config.Domain.N,
                  config.Fluid.lambda,
                  &initial<config.IC.Uval,config.IC.Xstart,config.IC.Xend>,
                  config.BC.Uleft,
                  config.BC.Uright
                  );
    }  catch (std::exception& e) {
        std::cerr<<e.what();
    }  catch(...){
        std::cerr<<"Unknown error!";
        std::abort();
    }

    //iteration cycle
    int iter = 0;
    while (iter < config.Timestep.NIter)
    {

    }


	return 0;
}
