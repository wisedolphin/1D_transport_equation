#pragma once
#include <fstream>
#include <string>

struct config 
{
	
	double CFL_;
	double N_;
	double Length_;
	double lambda_;
	double dx_;
	double dt_;
	int Iter_number;
    int Threads;

	config(double CFL, double N, double Length, double lambda, int Iter_number) : CFL_(CFL), N_(N), Length_(Length), lambda_(lambda) 
	{
		dx_ = Length_ / N_;
		dt_ = dx_ * CFL_ / lambda;
	}
	void config_rff(std::string file_path)
	{
		std::ifstream file;
		file.exceptions(std::ifstream::badbit);
		try {
			file.open(file_path);
			file >> CFL_;
			file >> N_;
			file >> Length_;
			file >> lambda_;
			file >> Iter_number;
		}
		catch (const std::ifstream::failure& e) {
			std::cerr << "Exception opening/reading/closing file\n";
		}

	}
};
