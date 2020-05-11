#include <benchmark/benchmark.h>
#include <boost/regex.hpp>
#ifndef _MSC_VER
#include <ctre.hpp>
#endif
#include <re2/re2.h>
#include <regex>

const std::string g_s = []() {
  const std::size_t n = 100000;
  return std::string(n, 'a') + 'b' + std::string(n, 'a');
}();

static void bench_boost(benchmark::State& state)
{
  const boost::regex pattern{ "a*ba*", boost::regex::optimize };
  for (auto _ : state) {
    const auto m = boost::regex_match(g_s, pattern);
    benchmark::DoNotOptimize(m);
  }
}
BENCHMARK(bench_boost);

#ifndef _MSC_VER
static void bench_ctre(benchmark::State& state)
{
  static constexpr auto pattern = ctll::fixed_string{ "a*ba*" };
  for (auto _ : state) {
    const auto m = ctre::match<pattern>(g_s);
    benchmark::DoNotOptimize(m);
  }
}
BENCHMARK(bench_ctre);
#endif

static void bench_re2(benchmark::State& state)
{
  RE2::Options options{ RE2::Quiet };
  options.set_never_capture(true);
  options.set_posix_syntax(true);
  const RE2 re("a*ba*", options);
  for (auto _ : state) {
    const auto m = RE2::FullMatch(g_s, re);
    benchmark::DoNotOptimize(m);
  }
}
BENCHMARK(bench_re2);

static void bench_std(benchmark::State& state)
{
  const std::regex pattern{ "a*ba*", std::regex::optimize };
  for (auto _ : state) {
    const auto m = std::regex_match(g_s, pattern);
    benchmark::DoNotOptimize(m);
  }
}
BENCHMARK(bench_std);
