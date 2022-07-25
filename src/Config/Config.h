#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;


struct Fluid_property_s
{
    double lambda;
};
struct Domain_settings_s
{
    int N;
    double L;
};
struct Time_step_settings_s
{
    double CFL;
    double NIter;
};
struct BC_s
{
    double Uleft;
    double Uright;
};
struct IC_s
{
    double Uval;
    double Xstart;
    double Xend;
    double apply_IC(double X)
    {
        if (X>Xstart && X<Xend) {return Uval;}
        else {return 0.0;}
    }
};
struct Result_s
{
    int Save_freq;
};
struct Scheme_s
{
    std::string scheme_name;
};
struct Multiprocessing_s
{
    int threads_num;
};

//! Calculation configuration loading class
/*!
Configuration file exaple config.json:
{
    "Fluid properties" :
    {
        "Tranport coeffition" : 0.5
    }
    "Domain settings" :
    {
        "Number of real cells" : 1000,
        "Calculation domain length" : 100
    }
    "Time step settings" :
    {
        "CFL number" : 0.5,
        "Iteration number" : 100
    }
    "BC settings" :
    {
        "Leftside value" : 0,
        "Rightside value" : 0
    }
    "IC settings" :
    {
        "U value": 1.0,
        "Start cooordinate" : 10,
        "End coordinate" : 20
    }
    "Result settings" :
    {
        "Data saving frequency" : 10
    }
    "Schemes settings" :
    {
        "Fluxes approximation scheme": "CIR"
    }
    "Multiprocessing settings" :
    {
        "Treads number" : 2
    }
}
*/
struct config 
{
    Fluid_property_s Fluid;;
    Domain_settings_s Domain;
    Time_step_settings_s Timestep;
    BC_s BC;
    IC_s IC;
    Result_s Result;
    Scheme_s Scheme;
    Multiprocessing_s Multiprocessing;

    config(std::string abs_filepath)
	{
        //cheking if file exists
        std::ifstream file;
        file.open(abs_filepath, std::ifstream::in);
        if(file.fail())
        {
            std::cerr<<"File "<< abs_filepath<< " doesnt exists!\n";
            std::cerr<<"Aborting!\n";
            std::abort();
        }
        else{file.close();}
        //Parsing config file
        pt::ptree json_tree;
        try{
            pt::json_parser::read_json(abs_filepath, json_tree);
        }
        catch(pt::json_parser::json_parser_error &e){
            std::cerr << e.what(); //if jsonfile isnt valid abort
            std::abort();
        }
        Fluid.lambda = json_tree.get("Fluid properties.Tranport coeffition", -1.0);
        if (Fluid.lambda < 0) {throw std::logic_error("Lambda has non-physical meaning");}
        Domain.L = json_tree.get("Domain settings.Calculation domain length", -1.0);
        Domain.N = json_tree.get("Domain settings.Number of real cells", -1);
        if (Domain.L < 0 || Domain.N < 0) {throw std::logic_error("Domain settings has non-physical meaning");}
        Timestep.CFL = json_tree.get("Time step settings.CFL number", -1.0);
        Timestep.NIter = json_tree.get("Time step settings.Iteration number", -1);
        if (Timestep.CFL < 0 || Timestep.NIter < 0) {throw std::logic_error("Timestep settings has non-physical meaning");}
        BC.Uleft = json_tree.get("BC settings.Leftside value", -1.0);
        BC.Uright = json_tree.get("BC settings.Rightside value", -1.0);
        if (BC.Uleft < 0 || BC.Uright < 0) {throw std::logic_error("BC settings has non-physical meaning");}
        IC.Uval = json_tree.get("IC settings.U value", -1.0);
        IC.Xstart = json_tree.get("IC settings.Start cooordinate", -1.0);
        IC.Xend = json_tree.get("IC settings.End coordinate", -1.0);
        if ((IC.Xstart - IC.Xend > Domain.L) || IC.Uval < 0) {throw std::logic_error("IC settings has non-physical meaning");}
        Result.Save_freq = json_tree.get("Result settings.Data saving frequency", -1);
        if (Result.Save_freq < 0){throw std::logic_error("Result settings has non-physical meaning");}
        Scheme.scheme_name = json_tree.get("Schemes settings.Fluxes approximation scheme", "CIR");
        Multiprocessing.threads_num = json_tree.get("Multiprocessing settings.Treads number", 1);
	}
};
