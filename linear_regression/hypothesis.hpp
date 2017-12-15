#ifndef HYPOTHESES_HPP
#define HYPOTHESES_HPP

#include <vector>

namespace corneau {
	//An hypothesis represent a linear function of scalar in the form f(x) = y-intercept + slope * x
	//We try to find the best hypothesis for our model
	template<typename T>
	class hypothesis {
		public :
			T y_intercept;
			T slope;
			
			std::vector<T> features;
			std::vector<T> parameters;
			
			hypothesis<T>(const T& _y, const T& _s) : y_intercept(_y), slope(_s)
			{}
			
			T operator()(const T& x_value)
			{
				return x_value * slope + y_intercept;
			}
	};
}
#endif