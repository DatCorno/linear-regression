#include <random>
#include <chrono>

#include "benchmark/benchmark.h"
#include "pcg_random.hpp"

static void BM_mt19937_gen(benchmark::State& state) {
	std::random_device rd{};
	
	std::mt19937 eng{rd()};
	
	if(!rd.entropy())
		eng.seed(time(0));
		
	std::normal_distribution<> dist;
	std::uniform_real_distribution<> real_dist;
	
	double sum = 0.0;
	double other_sum = 0.0;
	
	for (auto _ : state)
	{
		for(std::size_t i = 0; i < state.range(0); i++)
		{
			sum += dist(eng);
			other_sum += real_dist(eng);
		}
		
		benchmark::DoNotOptimize(sum);
	}
}
// Register the function as a benchmark
BENCHMARK(BM_mt19937_gen)->RangeMultiplier(10)->Range(100, 100'000'000);

// Define another benchmark
static void BM_pcg32_gen(benchmark::State& state) {
	std::random_device rd{};
	pcg_extras::seed_seq_from<std::random_device> seed_source;
	
	pcg32 eng(seed_source);
	
	if(!rd.entropy())
		eng.seed(time(0));
	
	std::normal_distribution<> dist;
	std::uniform_real_distribution<> real_dist;
	
	double sum = 0.0;
	double other_sum = 0.0;
	
	for (auto _ : state)
	{
		for(std::size_t i = 0; i < state.range(0); i++)
		{
			sum += dist(eng);
			other_sum += real_dist(eng);
		}
		
		benchmark::DoNotOptimize(sum);
	}
}
BENCHMARK(BM_pcg32_gen)->RangeMultiplier(10)->Range(100, 100'000'000);

static void BM_minstd_rand0(benchmark::State& state) {	
	std::random_device rd{};
	
	std::minstd_rand0 eng{rd()};
	
	if(!rd.entropy())
		eng.seed(time(0));
	
	std::normal_distribution<> dist;
	std::uniform_real_distribution<> real_dist;
	
	double sum = 0.0;
	double other_sum = 0.0;
	
	for (auto _ : state)
	{
		for(std::size_t i = 0; i < state.range(0); i++)
		{
			sum += dist(eng);
			other_sum += real_dist(eng);
		}
		
		benchmark::DoNotOptimize(sum);
	}
}
BENCHMARK(BM_minstd_rand0)->RangeMultiplier(10)->Range(100, 100'000'000);

static void BM_minstd_rand(benchmark::State& state) {	
	std::random_device rd{};
	
	std::minstd_rand0 eng{rd()};
	
	if(!rd.entropy())
		eng.seed(time(0));
	
	std::normal_distribution<> dist;
	std::uniform_real_distribution<> real_dist;
	
	double sum = 0.0;
	double other_sum = 0.0;
	
	for (auto _ : state)
	{
		for(std::size_t i = 0; i < state.range(0); i++)
		{
			sum += dist(eng);
			other_sum += real_dist(eng);
		}
		
		benchmark::DoNotOptimize(sum);
	}
}
// Register the function as a benchmark
BENCHMARK(BM_minstd_rand)->RangeMultiplier(10)->Range(100, 100'000'000);

BENCHMARK_MAIN();