#include "configuration.hpp"

namespace corneau {

	configuration::configuration(std::size_t n, std::size_t p, double s,
											double y, const std::string& f) :
		header_line("X,Y\n")
	{
		number_of_value = n;
		precision = p;
		slope = s;
		y_intercept = y;
		filename = f;
	}

	configuration::configuration(configuration&& _config) : filename(std::move(_config.filename))
	{
		precision = std::move(_config.precision);
		number_of_value = std::move(_config.number_of_value);
		y_intercept = std::move(_config.y_intercept);
		slope = std::move(_config.slope);
	}
}