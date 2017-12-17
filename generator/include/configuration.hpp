#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <utility>
#include <stdlib.h>
#include <string>

namespace corneau {
	struct configuration {
		configuration(std::size_t, std::size_t, double, double, const std::string&);
		configuration(configuration&&);
		
		std::size_t number_of_value;
		std::size_t precision;
		
		double slope;
		double y_intercept;
		
		std::string filename;
		std::string header_line;
		
		//Returns the number of characters use to represent the current double with given precision
		//So precision + 1 (for the '.') + 1 for an eventual '-' sign
		inline std::size_t data_point_character_size() const
		{
			return precision + 2;
		}
		
		//Returns the size of a line inside the filebuf
		//currently, config only supports two value so we return the size taken by two data points
		//We also account for the size of one delimiter character ',' and one end line character '\n'
		inline std::size_t sizeof_line() const
		{
			return data_point_character_size() * 2 + sizeof(char) * 2;
		}
	};
}
#endif