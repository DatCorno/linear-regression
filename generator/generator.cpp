#include "generator.hpp"

#define STB_SPRINTF_IMPLEMENTATION
#include "stb_sprintf.h"


namespace corneau {
	
	generator::generator(configuration&& _config) : config(std::move(_config)), eng(seed_source)
	{			
		//If random_device has no entropy it cannot seed the engine properly, we use time(0) as a fallback
		if(!rd.entropy()) 
			eng.seed(time(0));	
	}
	
	const configuration& generator::current_configuration() const
	{
		return config;
	}
	
	void generator::generate_data(std::ostream& out)
	{
		char* buffer = nullptr;
		for(std::size_t i = 0; i < config.number_of_value; ++i)
		{
			buffer = generate_line();
			out.write(buffer, config.sizeof_line());
			delete[] buffer;
		}
	}
	
	char* generator::generate_line()
	{
		char* buffer = new char[config.sizeof_line()];
		
		std::memset(buffer, '0', config.sizeof_line());

		buffer[config.data_point_character_size()] = ',';
		buffer[config.data_point_character_size() * 2 + sizeof(char)] = '\n';		
		
		//The actual numbers we want to output to the file
		double x = next_uniform_real();
		double y = config.y_intercept + config.slope * x + next_normal_real();
		
		//Res is the number of character written. The character at buffer[res] is '\0', so we need
		//To get rid of it
		int res = stbsp_snprintf((buffer), config.precision, "%f", x);
		buffer[res] = '0';
		
		//Since we written double_rep_size character, we put the delimiter at double_rep_size index
		res = stbsp_snprintf((buffer + config.data_point_character_size() + sizeof(char)), config.precision, "%f", y);
		buffer[config.data_point_character_size() + sizeof(char) + res] = '0';
	
		return buffer;
	}
	
	double generator::next_uniform_real()
	{
		return uniform_real_dist(eng);
	}
	
	double generator::next_normal_real()
	{
		return normal_dist(eng);
	}
}