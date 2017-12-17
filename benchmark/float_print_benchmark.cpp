#include <random>
#include <chrono>

#define STB_SPRINTF_IMPLEMENTATION
#include "benchmark/benchmark.h"
#include "pcg_random.hpp"
#include "stb_sprintf.h"

static void BM_stb_sprintf(benchmark::State& state) {
	std::random_device rd{};
	pcg_extras::seed_seq_from<std::random_device> seed_source;
	
	pcg32 eng(seed_source);
	
	if(!rd.entropy())
		eng.seed(time(0));
	
	std::normal_distribution<> dist;
	char* buffer = new char[state.range(0) * state.range(1)];
	
	for (auto _ : state)
	{
		for(std::size_t i = 0; i < state.range(0); ++i)
		{
			//Calculates the offset where the current line begins (0, sizeof_line * 1, sizeof_line * 2, etc.)
			std::size_t line_offset = state.range(1) * i;
			
			//The actual numbers we want to output to the file
			double x = dist(eng);
			
			//Res is the number of character written. The character at buffer[res] is '\0', so we need
			//To get rid of it
			int res = stbsp_sprintf((buffer + line_offset), "%f", x);
			buffer[line_offset + res] = '0';
		}
		
		benchmark::DoNotOptimize(buffer);
	}
	
	delete[] buffer;
}
BENCHMARK(BM_stb_sprintf)->Args({100, 8})->Args({100'000, 8})->Args({100'000'000, 8});


static void BM_stb_snprintf(benchmark::State& state) {
	std::random_device rd{};
	pcg_extras::seed_seq_from<std::random_device> seed_source;
	
	pcg32 eng(seed_source);
	
	if(!rd.entropy())
		eng.seed(time(0));
	
	std::normal_distribution<> dist;
	char* buffer = new char[state.range(0) * state.range(1)];
	
	for (auto _ : state)
	{
		for(std::size_t i = 0; i < state.range(0); ++i)
		{
			//Calculates the offset where the current line begins (0, sizeof_line * 1, sizeof_line * 2, etc.)
			std::size_t line_offset = state.range(1) * i;
			
			//The actual numbers we want to output to the file
			double x = dist(eng);
			
			//Res is the number of character written. The character at buffer[res] is '\0', so we need
			//To get rid of it
			int res = stbsp_snprintf((buffer + line_offset), state.range(1), "%f", x);
			buffer[line_offset + res] = '0';
		}
		
		benchmark::DoNotOptimize(buffer);
	}
	
	delete[] buffer;
}
BENCHMARK(BM_stb_snprintf)->Args({100, 8})->Args({100'000, 8})->Args({100'000'000, 8});

// Define another benchmark
static void BM_sprintf(benchmark::State& state) {
	std::random_device rd{};
	pcg_extras::seed_seq_from<std::random_device> seed_source;
	
	pcg32 eng(seed_source);
	
	if(!rd.entropy())
		eng.seed(time(0));
	
	std::normal_distribution<> dist;
	char* buffer = new char[state.range(0) * state.range(1)];
	
	for (auto _ : state)
	{
		for(std::size_t i = 0; i < state.range(0); ++i)
		{
			//Calculates the offset where the current line begins (0, sizeof_line * 1, sizeof_line * 2, etc.)
			std::size_t line_offset = state.range(1) * i;
			
			//The actual numbers we want to output to the file
			double x = dist(eng);
			
			//Res is the number of character written. The character at buffer[res] is '\0', so we need
			//To get rid of it
			int res = sprintf((buffer + line_offset), "%f", x);
			buffer[line_offset + res] = '0';
		}
		
		benchmark::DoNotOptimize(buffer);
	}
	
	delete[] buffer;
}
BENCHMARK(BM_sprintf)->Args({100, 8})->Args({100'000, 8})->Args({100'000'000, 8});

BENCHMARK_MAIN();