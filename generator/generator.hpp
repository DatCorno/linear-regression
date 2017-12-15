#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <string>
#include <chrono>
#include <random>
#include <cstring>

#include "configuration.hpp"

namespace corneau {
	class generator {
		public :
			generator(configuration&&);
			
			const configuration& current_configuration() const;
			
			char* generate_data();
		private :
			configuration config;
			
			std::random_device rd;
			std::mt19937 eng;
			
			double next_uniform_real();
			double next_normal_real();
			
			std::normal_distribution<> normal_dist;
			std::uniform_real_distribution<> uniform_real_dist;
	};
}
#endif