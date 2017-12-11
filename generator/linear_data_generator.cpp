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
	
	char delimiter = ',';
	
	if(argc > 1)
		number_of_value = atof(argv[1]);
	if(argc > 2)
		slope = atof(argv[2]);
	if(argc > 3)
		y_intercept = atof(argv[3]);
	if(argc > 4)
		precision = atoi(argv[4]);
	
	std::string filename = "linear_model_data.csv";
	
	std::random_device rd{};
	
	std::mt19937 eng{rd()};
	
	if(!rd.entropy()) //If random_device has no entropy it cannot seed the engine properly, we use time(0) as a fallback
		eng = std::mt19937{time(0)};
	
	std::normal_distribution<> error_rate;
	std::uniform_real_distribution<> x_distribution;
	
	std::size_t float_rep_size = precision + 3; //# after zero + '.' + '0' + '-'
	std::size_t sizeof_line = float_rep_size * 2 + sizeof(char) * 2; //Two float numbers + one delimiter + one \n
	
	{ //New scope so the file is closed at the end
		std::ofstream ostrm(filename);
		
		ostrm << ("X,Y\n"); //header line
		ostrm << std::fixed << std::setprecision(precision);
		
		//Buffer storing float representation and one '\0' character
		char* buffer = new char[(number_of_value * sizeof_line) + 1];
		
		//Initialize everything to zero
		for(std::size_t i = 0; i < number_of_value * sizeof_line; ++i)
			buffer[i] = '0';
		
		//Put a '\0' at the last location
		buffer[number_of_value * sizeof_line + 1] = '\0';
		
		//Loop over how much values with want
		for(std::size_t i = 0; i < number_of_value; ++i)
		{
			//Calculates the offset where the current line begins (0, sizeof_line * 1, sizeof_line * 2, etc.)
			std::size_t line_offset = sizeof_line * i;
			
			//The actual numbers we want to output to the file
			float x = x_distribution(eng);
			float y = y_intercept + slope * x + error_rate(eng);
			
			//Res is the number of character written. The character at buffer[res] is '\0', so we need
			//To get rid of it
			int res = snprintf((buffer + line_offset), float_rep_size, "%f", x);
			buffer[line_offset + res] = '0';
			
			//Since we written float_rep_size character, we put the delimiter at float_rep_size index
			buffer[line_offset + float_rep_size] = ',';
			
			res = snprintf((buffer + line_offset + float_rep_size + sizeof(char)), float_rep_size, "%f", y);
			
			buffer[line_offset + float_rep_size + sizeof(char) + res] = '0';
			
			buffer[line_offset + float_rep_size * 2 + sizeof(char)] = '\n';	
		}
		
		ostrm.write(buffer, number_of_value * sizeof_line);
	}
	
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;

	std::cout << diff.count() << '\n';

	return 0;
}