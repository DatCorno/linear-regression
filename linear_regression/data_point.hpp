#ifndef DATA_POINT_HPP
#define DATA_POINT_HPP

namespace corneau {
	template<typename T>
	struct data_point {
		T x;
		T y;
		
		data_point<T>() : x(0), y(0)
		{}
		data_point<T>(const T& _x, const T& _y) : x(_x), y(_y)
		{}
	};
}
#endif