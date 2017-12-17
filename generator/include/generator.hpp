#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <string>
#include <chrono>
#include <random>
#include <cstring>
#include <fstream>

#include "configuration.hpp"
#include "pcg_random.hpp"

namespace corneau {
	class generator {
		public :
			generator(configuration&&);
			
			const configuration& current_configuration() const;
						
			void generate_data(std::ostream&);
		private :
			char* generate_line();
		
			configuration config;
			
			std::random_device rd;
			
			pcg_extras::seed_seq_from<std::random_device> seed_source;
			pcg32 eng;
			
			double next_uniform_real();
			double next_normal_real();
			
			std::normal_distribution<> normal_dist;
			std::uniform_real_distribution<> uniform_real_dist;
	};
}
#endif