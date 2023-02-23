#include <libnum.tpp>
#include <benchmark/benchmark.h>

static void BENCH_MARK_CONSTRUCTOR_INITALISERLIST_INPUT(benchmark::State& state) 
{
  for (auto _ : state)
  {
    mathcc::libnum<int> f({1,2,3,4,5,6,7,8,9,10,11,12},{1,2,3,4,5,6,7,8,9,10,11,12},{4,4},{4,3});    
  }
}
BENCHMARK(BENCH_MARK_CONSTRUCTOR_INITALISERLIST_INPUT)->Iterations(200000);

static void BENCH_MARK_CONTRUCTOR_VECTOR_INPUT_4BYTE_INTEGERAL(benchmark::State& state) 
{
  for (auto _ : state)
  {
    std::vector<int> A = {1,2,3,4,5,6};
    std::vector<int> B = {1,2,3,4,5,6};
    mathcc::libnum<int> e(A,B,{3,3},{3,2});
  }
}
BENCHMARK(BENCH_MARK_CONTRUCTOR_VECTOR_INPUT_4BYTE_INTEGERAL)->Iterations(200000);

static void BENCH_MARK_CONTRUCTOR_VECTOR_INPUT_8BYTE_INTEGERAL(benchmark::State& state) 
{
  for (auto _ : state)
  {
    std::vector<uint64_t> A = {1,2,3,4,5,6};
    std::vector<uint64_t> B = {1,2,3,4,5,6};
    mathcc::libnum<uint64_t> e(A,B,{3,3},{3,2});
  }
}
BENCHMARK(BENCH_MARK_CONTRUCTOR_VECTOR_INPUT_8BYTE_INTEGERAL)->Iterations(200000);

static void BENCH_MARK_CONTRUCTOR_VECTOR_INPUT_4BYTE_FLOATINGPOINT(benchmark::State& state) 
{
  for (auto _ : state)
  {
    std::vector<float> A = {1,2,3,4,5,6};
    std::vector<float> B = {1,2,3,4,5,6};
    mathcc::libnum<float> e(A,B,{3,3},{3,2});
  }
}

BENCHMARK(BENCH_MARK_CONTRUCTOR_VECTOR_INPUT_4BYTE_FLOATINGPOINT)->Iterations(200000);

static void BENCH_MARK_CONTRUCTOR_VECTOR_INPUT_8BYTE_FLOATINGPOINT(benchmark::State& state) 
{
  for (auto _ : state)
  {
    std::vector<double> A = {1,2,3,4,5,6};
    std::vector<double> B = {1,2,3,4,5,6};
    mathcc::libnum<double> e(A,B,{3,3},{3,2});
  }
}
BENCHMARK(BENCH_MARK_CONTRUCTOR_VECTOR_INPUT_8BYTE_FLOATINGPOINT)->Iterations(200000);

static void BENCH_MARK_SOLVE_UNOPTIMISED_GAUSIAN_INEGERAL(benchmark::State& state) 
{
  std::vector<int> sol;
  mathcc::libnum<int> h({1,2,6,4},{5,13},{2,2},{2,1});
  for (auto _ : state)
  {
    sol = h.solve();
  }
}
BENCHMARK(BENCH_MARK_SOLVE_UNOPTIMISED_GAUSIAN_INEGERAL)->Iterations(200000);


static void BENCH_MARK_SOLVE_UNOPTIMISED_GAUSIAN_FLOATS(benchmark::State& state) 
{
  std::vector<float> sol;
  mathcc::libnum<float> h({1,2,6,4},{5,13},{2,2},{2,1});
  for (auto _ : state)
  {
    sol = h.solve();
  }
}

BENCHMARK(BENCH_MARK_SOLVE_UNOPTIMISED_GAUSIAN_FLOATS)->Iterations(200000);


BENCHMARK_MAIN();