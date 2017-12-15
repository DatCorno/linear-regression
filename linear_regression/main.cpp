#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>	
#include "linear_regression.hpp"

using std::cout;

int main(int argc, char** argv)
{
	std::string delimiter(",");
	double learning_rate = 0.1;
	
	if(argc < 2)
	{
		cout << "Missing filename\n";
		return -1;
	}
	
	std::ifstream istrm(argv[1]);
	
	if(!istrm.is_open())
	{
		cout << "Failed to open file\n";
		return -1;
	}
	
	if(argc > 2)
		learning_rate = atof(argv[2]);
	
	if(argc > 3)
		delimiter = std::string(argv[3]);
	
	std::vector<corneau::data_point<double>> data_points;
	std::string line, token;
	size_t pos = 0;

	//Read file
	while(getline(istrm, line))
	{
		try 
		{
			while ((pos = line.find(delimiter)) != std::string::npos) 
			{
				//Part before the delimiter is the x value
				corneau::data_point<double> point;
				token = line.substr(0, pos);
				point.x = stof(token);
				
				//Part after the delimiter is the y value
				line.erase(0, pos + delimiter.length());
				point.y = stof(line);
				
				data_points.push_back(point);
			}
		}
		catch(const std::invalid_argument& e) //Tried to parse headers
		{}
	}
	
	cout << "Loaded : " << data_points.size() << " data point\n";
	
	std::random_device rd{};
	std::mt19937 eng{rd()};
	
	if(!rd.entropy())
		eng.seed(time(0));
	
	std::uniform_real_distribution<> dis;
	std::uniform_int_distribution<> index_dis(0, data_points.size() - 1);
	
	//Generate random starting value for the y_intercept and the slope
	double random_y_intercept = data_points[index_dis(eng)].y;
	double random_slope = dis(eng);
		
	corneau::linear_regression<double, double, double> linear_reg(learning_rate, random_y_intercept, random_slope);
	
	const corneau::hypothesis<double>& final_hyp = linear_reg(data_points);
	
	cout << "random x : " << random_slope << "; random y " << random_y_intercept << '\n';
	cout << "y-intercept : " << final_hyp.y_intercept << "\nslope : " << final_hyp.slope << '\n';
	cout << "In " << linear_reg.iterations() << " iterations\n";
	
	return 0;
}