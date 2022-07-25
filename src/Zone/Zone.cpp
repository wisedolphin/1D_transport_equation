#include "Zone.h"
template <typename T>
typename std::enable_if<std::is_unsigned<T>::value, int>::type
inline constexpr sgn(T const x) {
    return T(0) < x;
}

template <typename T>
typename std::enable_if<std::is_signed<T>::value, int>::type
inline constexpr sgn(T const x) {
    return (T(0) < x) - (x < T(0));
}
double minmod(double first, double second)
{
    return(1/2 * sgn(first+second)*std::min(std::abs(first), std::abs(second)));
}

void Zone::IC_apply(IC_s IC)
{
    // since 0 index in field_ is the left fiction cell
    // and X_[0] the first real cell
    // offset in field by 1
    size_t i;
//#pragma omp for default(none) private(i) shared(field_, X_) schedule(dynamic)
    for (i = 0; i != N_; ++i)
	{
        field_.at(i + 1) =  IC.apply_IC(X_.at(i));
	}
}

void Zone::BC_apply(double const& left_bound_val, double const& right_bound_val)
{
	field_.at(0) = left_bound_val;
	field_.at(N_ + 1) = right_bound_val;
}

void Zone::Fluxes_CIR(double const lambda)
{
	for (int i = 0; i != N_ + 1; ++i)
	{
        flux_.at(i) = 0.5 * (lambda * (field_.at(i + 1) + field_.at(i)) -
            std::abs(lambda) * (field_.at(i + 1) - field_.at(i)));
	}
}

void Zone::Fluxes_MUSCL(double const lambda, double const dx)
{
    std::vector<double> field_face(2*N_+1);
    field_face.front() = field_.back();
    field_face.back() = field_.back();
    for (int i = 1; i != N_ + 1; ++i)
    {
        double derivetive = minmod((field_.at(i) - field_.at(i-1)) / dx,
                                    (field_.at(i+1) - field_.at(i)) / dx);
        field_face.at(2*i - 1)  = field_.at(i) + dx/2 * derivetive;
        field_face.at(2*i)      = field_.at(i) - dx/2 * derivetive;
    }
    for (int i = 0; i != N_+1; ++i)
    {
        flux_.at(i) = 0.5 * (lambda * (field_face.at(2*i+1) + field_face.at(2*i)) -
            std::abs(lambda) * (field_.at(2*i+1) - field_.at(2*i)));
    }
}

void Zone::calc_next_step(double dx, double dt)
{
    // making a new field
    // remeber to apply BC after this method
    std::vector<double> next_field(N_ + 2);
	for (int i = 0; i != N_ + 1; ++i)
	{
		next_field.at(i + 1) = field_.at(i + 1) - dt / dx * (flux_.at(i + 1) - flux_.at(i));
	}
	std::swap(next_field, field_);
}












