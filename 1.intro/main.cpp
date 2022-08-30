#include <benchmark/benchmark.h>
#include <cstdlib>
#include <random>


class string_data_fixture : public ::benchmark::Fixture {
public:
  void SetUp(const ::benchmark::State &st) {
    int digits = st.range(0);
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<> dis{0, 9};

    values.reserve(1000);
    for (int n = 0; n < 1000; ++n) {
      int res = 0;
      for (int i = 0; i < digits; i++) {
        res = res * 10 + dis(gen);
      }
      if (dis(gen) >= 5) {
        res *= -1;
      }
      values.emplace_back(std::to_string(res), res);
    }
  }

  void TearDown(const ::benchmark::State &) { values.clear(); }

  std::vector<std::pair<std::string, int>> values;
};

#define BENCH(test)                                                            \
  BENCHMARK_REGISTER_F(string_data_fixture, test)                              \
      ->Arg(1)                                                                 \
      ->Arg(2)                                                                 \
      ->Arg(3)                                                                 \
      ->Arg(4)                                                                 \
      ->Arg(5)                                                                 \
      ->Arg(6)                                                                 \
      ->Arg(7)                                                                 \
      ->Arg(8)                                                                 \
      ->Arg(9)                                                                 \
      ->Arg(10);


// Baseline 1
BENCHMARK_DEFINE_F(string_data_fixture, std_atoi)(benchmark::State &state) {
  for (auto _ : state) {
    for (const auto &[str, integer] : values) {
      const auto val = atoi(str.c_str());
      assert(val == integer);
      benchmark::DoNotOptimize(&val);
    }
  }
}

BENCH(std_atoi);


/** ----- Your implementation start here ----- */

// Replace *my* in 'my_str_to_int' with your username to avoid dupticates
static int my_str_to_int(const char *str)
{
  return 0;
}

// Replace *my* in 'my_sring_to_int' with your username to avoid dupticates
BENCHMARK_DEFINE_F(string_data_fixture, my_sring_to_int)(benchmark::State &state) {
  for (auto _ : state) {
    for (const auto &[str, integer] : values) {
      const auto val = my_str_to_int(str.c_str());
      assert(val == integer);
      benchmark::DoNotOptimize(&val);
    }
  }
}

BENCH(my_sring_to_int);


/** ----- Your implementation ends here ----- */


BENCHMARK_MAIN();
