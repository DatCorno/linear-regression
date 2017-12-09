#include <fstream>
#include <iostream>
#include <vector>

#include "linear_regression.hpp"

using std::cout;
using namespace corneau;

int main(int argc, char** argv)
{
	std::string delimiter(",");
	double learning_rate = 0.1;
	
	if(argc < 2)
	{
		cout << "Missing filename\n";
		return -1;
	}
	
	if(argc > 2)
		learning_rate = atof(argv[2]);
	
	if(argc > 3)
		delimiter = std::string(argv[3]);
	
	std::ifstream istrm(argv[1]);
	
	std::vector<data_point<double>> data_points;
	std::string line;
	size_t pos = 0;
	std::string token;
	
	if(!istrm.is_open())
	{
		cout << "Failed to open file\n";
		return -1;
	}
	
	getline(istrm, line);	//Skip csv header

	//Read file
	while(getline(istrm, line))
	{
		while ((pos = line.find(delimiter)) != std::string::npos) 
		{
			//Part before the delimiter is the x value
			data_point<double> point;
			token = line.substr(0, pos);
			point.x = stof(token);
			
			//Part after the delimiter is the y value
			line.erase(0, pos + delimiter.length());
			point.y = stof(line);
		}
	}
	
	cout << "Loaded : " << data_points.size() << " data point\n";
	
	std::random_device rd{};
	std::mt19937 eng{rd()};
	
	std::uniform_real_distribution<> dis;
	
	//Generate random starting value for the y_intercept and the slope
	double random_y_intercept = dis(eng);
	double random_slope = dis(eng);
		
	
	linear_regression<double, double> linear_reg(0.1, random_y_intercept, random_slope);
	
	const hypothesis<double>& final_hyp = linear_reg(data_points);
	
	cout << "y-intercept : " << final_hyp.y_intercept << "\nslope : " << final_hyp.slope << '\n';
	
	return 0;
}