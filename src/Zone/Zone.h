#pragma once
#include <vector>
#include <exception>
#include <iostream>
#include "../config/Config.h"
#include <cmath>

//! Class for field and fluxes processing
/*!
    erge
*/
class Zone
{
    //! Real cells amount
    int N_;
    //! X-ccordinates for real cells only
	std::vector<double> X_;			// coordinates - only for real cells
    //! Variable field. The size is N_+2 - with fiction cells
	std::vector<double> field_;		// field - for real and fiction cells
    //! Fluxes on cells faces. The size is N_+1
	std::vector<double> flux_;		// fluxes - for real cells
public:
    //! Initial condition function
	using IC = double (*)(double x);
    //! Zone Constructor
    /*!
        \param N a real cells count
        \param lambda constant tranport coeffition
        \param IC_function initial conditions function(param X, result field value)
        \param left_bound_val a letf fiction cell boundary condition
        \param left_bound_val a right fiction cell boundary condition
    */
    Zone(int N, double const lambda, IC IC_function, double const& left_bound_val, double const& right_bound_val) :N_(N)
	{
		try {
			X_.resize(N_);
			field_.resize(N_ + 2);
			flux_.resize(N_ + 1);
		}
		catch (std::bad_alloc& e) {
			std::cout << e.what();
			throw;
		}
		IC_apply(IC_function);
		BC_apply(left_bound_val, right_bound_val);
		Fluxes_CIR(lambda);
	}

    //! Initial condition applying
    /*!
        \param IC initial conditions function(param X, result field value)
    */
    void IC_apply(IC IC);

    //! Boundaty condition applying
    /*!
        \param left_bound_val a letf fiction cell boundary condition
        \param left_bound_val a right fiction cell boundary condition
    */
	void BC_apply(double const& left_bound_val, double const& right_bound_val);

    //! Calculation of fluxes with CIR scheme
    /*!
        \param lambda constant tranport coeffition
    */
    void Fluxes_CIR(double const lambda);

    //! Calculation of fluxes with Muscule scheme (Kolgan reconstruction)
    /*!
        \param lambda constant tranport coeffition
        \param dx space discretization
    */
    void Fluxes_MUSCULE(double const lambda, double const dx);

    //! Next step calculation
    /*!
        \param dx space discretization
        \param dt time discretization
    */
	void calc_next_step(double dx, double dt);
};

