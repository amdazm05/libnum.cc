#include <libnum.tpp>
#include <benchmark/benchmark.h>

static void BENCH_MARK_INITIALISERLIST(benchmark::State& state) 
{
  for (auto _ : state)
  {
    mathcc::libnum<int> f({1,2,3,4,5,6,7,8,9,10,11,12},{1,2,3,4,5,6,7,8,9,10,11,12},{4,3},{4,3});    
  }
}
BENCHMARK(BENCH_MARK_INITIALISERLIST)->Iterations(200000);

static void BENCH_MARK_VECTOR_MOVE(benchmark::State& state) 
{
  for (auto _ : state)
  {
    std::vector<int> A = {1,2,3,4,5,6};
    std::vector<int> B = {1,2,3,4,5,6};
    
    std::pair<int,int> dimA = {3,2};
    std::pair<int,int> dimB = {3,2};

    mathcc::libnum<int> e(A,B,dimA,dimB);
  }
}
BENCHMARK(BENCH_MARK_VECTOR_MOVE)->Iterations(200000);
BENCHMARK_MAIN();