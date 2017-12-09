#include <random>
#include <fstream>

/*
	Generate some random data for a linear model
*/

int main(int argc, char** argv)
{
	std::size_t number_of_value = 100;
	double slope = 1.0;
	double y_intercept = 0.0;
	
	std::string delimiter(",");
	
	if(argc > 1)
		number_of_value = atof(argv[1]);
	if(argc > 2)
		slope = atof(argv[2]);
	if(argc > 3)
		y_intercept = atof(argv[3]);
	if(argc > 4)
		delimiter = std::string(argv[4]);
	
	std::string filename = "linear_model_data.csv";
	
	std::random_device rd{};
	std::mt19937 eng{rd()};
	
	std::normal_distribution<> error_rate;
	std::uniform_real_distribution<> x_distribution;
	
	{ //New scope so the file is closed at the end
		std::ofstream ostrm(filename);
		
		ostrm << ("X" + delimiter + "Y\n"); //header line
	
		for(std::size_t i = 0; i < number_of_value; ++i)
		{
			double x = x_distribution(eng); //Generate some x's from a uniform distribution
			double y = y_intercept + slope * x + error_rate(eng); //Calculate the value of y corresponding the model while adding some noises
			
			ostrm << x << delimiter << y << '\n';
		}
	}
	
	return 0;
}