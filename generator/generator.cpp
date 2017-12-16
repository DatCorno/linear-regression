#include "generator.hpp"

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
	
	char* generator::generate_data()
	{
		char* buffer = new char[config.number_of_value * config.sizeof_line()];
		
		std::memset(buffer, '0', config.number_of_value * config.sizeof_line());
		
		for(std::size_t i = 0; i < config.number_of_value; ++i)
		{
			buffer[i * config.sizeof_line() + config.data_point_character_size()] = ',';
			buffer[i * config.sizeof_line() + config.data_point_character_size() * 2 + sizeof(char)] = '\n';	
		}
		
		//Loop over how much values with want
		for(std::size_t i = 0; i < config.number_of_value; ++i)
		{
			//Calculates the offset where the current line begins (0, sizeof_line * 1, sizeof_line * 2, etc.)
			std::size_t line_offset = config.sizeof_line() * i;
			
			//The actual numbers we want to output to the file
			double x = next_uniform_real();
			double y = config.y_intercept + config.slope * x + next_normal_real();
			
			//Res is the number of character written. The character at buffer[res] is '\0', so we need
			//To get rid of it
			int res = sprintf((buffer + line_offset), "%f", x);
			buffer[line_offset + res] = '0';
			
			//Since we written double_rep_size character, we put the delimiter at double_rep_size index
			res = sprintf((buffer + line_offset + config.data_point_character_size() + sizeof(char)), "%f", y);
			buffer[line_offset + config.data_point_character_size() + sizeof(char) + res] = '0';
		}
		
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