#ifndef BATCH_GRADIENT_DESCENT_HPP
#define BATCH_GRADIENT_DESCENT_HPP

/*
	Calculate the derivate term by which to multiply the learning rate for a linear function
	With cost function 1/2m * sum((hypothesis(x^i) - y^i)^2)
	For term theta zero
	
	We suppose Container supports .size() and random access
	We suppose the number of x values is the same as y values
*/

#include "data_point.hpp"

namespace corneau {
	
	template<typename PrecisionType,
				typename T, 
				template<typename, typename = std::allocator<corneau::data_point<T>>> typename Container,
				typename LinearFunction>
	T calculate_theta_zero(const Container<corneau::data_point<T>>& values, LinearFunction hypothesis)
	{
		PrecisionType constant_term = 1 / (PrecisionType)values.size();
			
		T sum = 0;
		
		for(std::size_t i = 0; i < values.size(); ++i)
			sum += (hypothesis(values[i].x)) - values[i].y;
			
		return constant_term * sum;
	}

	template<typename PrecisionType,
				typename T,
				template<typename, typename = std::allocator<corneau::data_point<T>>> typename Container,
				typename LinearFunction>
	T calculate_theta_one(const Container<corneau::data_point<T>>& values, LinearFunction hypothesis)
	{
		PrecisionType constant_term = 1 / (PrecisionType)values.size();
		
		T sum = 0;
		
		for(std::size_t i = 0; i < values.size(); ++i)
			sum += ((hypothesis(values[i].x)) - values[i].y) * values[i].x;
			
		return constant_term * sum;
	}
}
#endif