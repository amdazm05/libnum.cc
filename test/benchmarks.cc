#include <libnum.tpp>
#include <benchmark/benchmark.h>

static void BENCH_MARK_INITIALISERLIST(benchmark::State& state) 
{
  for (auto _ : state)
  {
    mathcc::libnum<int> f({1,2,3,4,5,6,7,8,9,10,11,12},{1,2,3,4,5,6,7,8,9,10,11,12},{4,4},{4,3});    
  }
}
BENCHMARK(BENCH_MARK_INITIALISERLIST)->Iterations(200000);

static void BENCH_MARK_VECTOR_MOVE(benchmark::State& state) 
{
  for (auto _ : state)
  {
    std::vector<int> A = {1,2,3,4,5,6};
    std::vector<int> B = {1,2,3,4,5,6};

    mathcc::libnum<int> e(A,B,{3,3},{3,2});
  }
}
BENCHMARK(BENCH_MARK_VECTOR_MOVE)->Iterations(200000);

static void BENCH_MARK_SOLVE_BASIC(benchmark::State& state) 
{
  std::vector<int> sol;
  for (auto _ : state)
  {
    mathcc::libnum<int> h({1,2,6,4},{5,13},{2,2},{2,1});
    sol = h.solve();
  }
}
BENCHMARK(BENCH_MARK_SOLVE_BASIC)->Iterations(200000);


static void BENCH_MARK_SOLVE_FLOATS(benchmark::State& state) 
{
  std::vector<float> sol;
  for (auto _ : state)
  {
    mathcc::libnum<float> h({1,2,6,4},{5,13},{2,2},{2,1});
    sol = h.solve();
  }
}

BENCHMARK(BENCH_MARK_SOLVE_FLOATS)->Iterations(200000);


BENCHMARK_MAIN();