#ifndef LINEAR_REGRESSION_HPP
#define LINEAR_REGRESSION_HPP

#include "batch_gradient_descent.hpp"
#include "data_point.hpp"
#include <iostream>

namespace corneau {
	//An hypothesis represent a linear function of scalar in the form f(x) = y-intercept + slope * x
	//We try to find the best hypothesis for our model
	template<typename T>
	class hypothesis {
		public :
			T y_intercept;
			T slope;
			
			hypothesis<T>(const T& _y, const T& _s) : y_intercept(_y), slope(_s)
			{}
			
			T operator()(const T& x_value)
			{
				return x_value * slope + y_intercept;
			}
	};

	template<typename T, typename A, typename Precision>
	class linear_regression {
		public :
			linear_regression<T, A, Precision>(A _a, T _y, T _s) : learning_rate(_a), hyp( _y, _s), converged(false),
																number_of_iterations(0)
			{}
		
			template< template<typename, typename = std::allocator<corneau::data_point<T>>> typename Container>
			const hypothesis<T>& operator()(const Container<corneau::data_point<T>>& values)
			{
				if(!converged)
					reach_convergence(values);
				
				return hyp;
			}
			
			std::size_t iterations() const
			{
				return number_of_iterations;
			}
			
		private :
			bool converged;
			std::size_t number_of_iterations;
				
			template< template<typename, typename = std::allocator<corneau::data_point<T>>> typename Container>
			void reach_convergence(const Container<corneau::data_point<T>> &values)
			{
				Precision temp0, temp1;
				
				while(!converged)
				{
					temp0 = hyp.y_intercept - (learning_rate * calculate_theta_zero<Precision>(values, hyp));
					temp1 = hyp.slope - (learning_rate * calculate_theta_one<Precision>(values, hyp));
					
					if(temp0 != hyp.y_intercept && temp1 != hyp.slope)
					{
						hyp.y_intercept = temp0;
						hyp.slope = temp1;
						number_of_iterations++;
					}
					else
						converged = true;
				}
			}
		
			A learning_rate;
			hypothesis<T> hyp;
			
	};
}
#endif