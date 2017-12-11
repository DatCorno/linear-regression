#include <random>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <iostream>

/*
	Generate some random data for a linear model
*/

int main(int argc, char** argv)
{
	auto start = std::chrono::high_resolution_clock::now();
	
	std::size_t number_of_value = 100;
	double slope = 1.0;
	double y_intercept = 0.0;
	std::size_t precision = 8;
	
	std::string delimiter(",");
	
	if(argc > 1)
		number_of_value = atof(argv[1]);
	if(argc > 2)
		slope = atof(argv[2]);
	if(argc > 3)
		y_intercept = atof(argv[3]);
	if(argc > 4)
		delimiter = std::string(argv[4]);
	if(argc > 5)
		precision = atoi(argv[5]);
	
	std::string filename = "linear_model_data.csv";
	
	std::random_device rd{};
	
	std::mt19937 eng{rd()};
	
	if(!rd.entropy()) //If random_device has no entropy it cannot seed the engine properly, we use time(0) as a fallback
		eng = std::mt19937{time(0)};
	
	std::normal_distribution<> error_rate;
	std::uniform_real_distribution<> x_distribution;
	
	{ //New scope so the file is closed at the end
		std::ofstream ostrm(filename);
		
		ostrm << ("X" + delimiter + "Y\n"); //header line
		ostrm << std::fixed << std::setprecision(precision);
		
		for(std::size_t i = 0; i < number_of_value; ++i)
		{
			double x = x_distribution(eng);
			auto buf = std::to_string(x);
			
			ostrm.write(buf.data(), buf.size());
			ostrm.write(delimiter.data(), delimiter.size());
			
			double y = y_intercept + slope * x + error_rate(eng);
			buf = std::to_string(y);
			
			ostrm.write(buf.data(), buf.size());			
			ostrm << '\n';
		}
	}
	
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;

	std::cout << diff.count() << '\n';

	return 0;
}