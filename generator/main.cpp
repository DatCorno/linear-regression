#include <random>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string.h>

#include "generator.hpp"
#include "cxxopts.hpp"

/*
	Generate some random data for a linear model
*/

int main(int argc, char** argv)
{	
	//Construct the argument for the generator. All values are optional
	cxxopts::Options options(argv[0], "data generator");
	options.add_options()
	("n,number_of_value", "number of value to generate", 
			cxxopts::value<std::size_t>()->default_value("100000"))
	("p,precision", "precision of floating point value",
			cxxopts::value<std::size_t>()->default_value("8"))
	("f,filename", "name of the filename to output data",
			cxxopts::value<std::string>()->default_value("data.csv"))
	("s,slope", "the slope of the linear function to generate value from",
			cxxopts::value<double>()->default_value("1.0"))
	("y,y_intercept", "the y-intercept of the linear function to generate value from",
			cxxopts::value<double>()->default_value("5.0"))
	;
	
	auto result = options.parse(argc, argv);
	
	//A reference to the result object raises error so 
	corneau::generator data_generator(std::move(corneau::configuration(result["number_of_value"].as<std::size_t>(),
																		result["precision"].as<std::size_t>(),
																		result["slope"].as<double>(),
																		result["y_intercept"].as<double>(),
																		result["filename"].as<std::string>())));
	
	const corneau::configuration& current_configuration = data_generator.current_configuration();
	
	auto start = std::chrono::high_resolution_clock::now();

	{ //New scope so the file is closed at the end
		std::ofstream file_stream(current_configuration.filename);

		file_stream << current_configuration.header_line; //header line
		file_stream << std::fixed << std::setprecision(current_configuration.precision);
		
		data_generator.generate_data(file_stream);
	}
	
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;

	std::cout << diff.count() << '\n';
	
	return 0;
}