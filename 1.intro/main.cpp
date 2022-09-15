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

int ssedov_str_to_int(const char *str) {
  if (str[0] == '-')
    return -ssedov_str_to_int(str + 1);
  int x = 0;
  int i = 0;
  while ((str[i] & 0xf0) == 0x30 && (str[i] < 0x3a))
    x = x * 10 + str[i++] - 0x30;
  return x;
}

BENCHMARK_DEFINE_F(string_data_fixture, ssedov_str_to_int)
(benchmark::State &state) {
  for (auto _ : state) {
    for (const auto &[str, integer] : values) {
      const auto val = ssedov_str_to_int(str.c_str());
      assert(val == integer);
      benchmark::DoNotOptimize(&val);
    }
  }
}

BENCH(ssedov_str_to_int);

static int michael_str_to_int(const char *str) {
  int val = 0;
  short sign = 1;
  size_t i = 0;
  if (str[0] == '-') {
    i++;
    sign = -1;
  }
  for (; str[i] != '\0'; i++) {
    val = (val << 3) + (val << 1) + (str[i] - '0');
  }
  return val * sign;
}

BENCHMARK_DEFINE_F(string_data_fixture, michael_sring_to_int)
(benchmark::State &state) {
  for (auto _ : state) {
    for (const auto &[str, integer] : values) {
      const auto val = michael_str_to_int(str.c_str());
      assert(val == integer);
      benchmark::DoNotOptimize(&val);
    }
  }
}

BENCH(michael_sring_to_int);

static int jlane71_str_to_int(const char *str, int length) {
  int output = 0;
  bool negative = false;

  if (*str == '-') {
    negative = true;
    ++str;
    --length;
  }

  switch (length) {
  case 10:
    output += 1000000000 * (str[length - 10] - '0');
  case 9:
    output += 100000000 * (str[length - 9] - '0');
  case 8:
    output += 10000000 * (str[length - 8] - '0');
  case 7:
    output += 1000000 * (str[length - 7] - '0');
  case 6:
    output += 100000 * (str[length - 6] - '0');
  case 5:
    output += 10000 * (str[length - 5] - '0');
  case 4:
    output += 1000 * (str[length - 4] - '0');
  case 3:
    output += 100 * (str[length - 3] - '0');
  case 2:
    output += 10 * (str[length - 2] - '0');
  case 1:
    output += (str[length - 1] - '0');
  }

  return negative ? -output : output;
}

// Replace *my* in 'my_sring_to_int' with your username to avoid dupticates
BENCHMARK_DEFINE_F(string_data_fixture, jlane71_sring_to_int)
(benchmark::State &state) {
  for (auto _ : state) {
    for (const auto &[str, integer] : values) {
      const auto val = jlane71_str_to_int(str.c_str(), str.length());
      assert(val == integer);
      benchmark::DoNotOptimize(&val);
    }
  }
}

BENCH(jlane71_sring_to_int);

static int yzhu631_str_to_int(const char *str) {
  char const *ptr = str;
  int rlt = 0;
  int sign = 1;
  if (*ptr == '-') {
    sign = -1;
    ptr++;
  }
  while (*ptr) {
    rlt = *ptr - '0' + (rlt << 3) + (rlt << 1);
    ptr++;
  }
  return sign * rlt;
}

BENCHMARK_DEFINE_F(string_data_fixture, yzhu631_str_to_int)
(benchmark::State &state) {
  for (auto _ : state) {
    for (const auto &[str, integer] : values) {
      const auto val = yzhu631_str_to_int(str.c_str());
      assert(val == integer);
      benchmark::DoNotOptimize(&val);
    }
  }
}

BENCH(yzhu631_str_to_int);

static int mzambotti1_string_to_int(const char *first) {
  int result{0};
  int sign{1};
  if (((*first == '-'))) {
    sign = -1;
    ++first;
  }
  for (; *first != '\0'; ++first) {
    if ((!(('0' <= *first) && (*first <= '9'))))
      throw std::exception();
    result = result * 10 + unsigned(*first - '0');
  }
  return sign * result;
}

BENCHMARK_DEFINE_F(string_data_fixture, mzambotti1_string_to_int)
(benchmark::State &state) {
  for (auto _ : state) {
    for (const auto &[str, integer] : values) {
      const auto val = mzambotti1_string_to_int(str.c_str());
      assert(val == integer);
      benchmark::DoNotOptimize(&val);
    }
  }
}

BENCH(mzambotti1_string_to_int);

static int tej_str_to_int(const char *str) {
  int val = 0;
  while (*str) {
    val = val * 10 + (*str++ - '0');
  }
  return val;
}

// Replace *my* in 'my_sring_to_int' with your username to avoid dupticates
BENCHMARK_DEFINE_F(string_data_fixture, tej_sring_to_int)
(benchmark::State &state) {
  for (auto _ : state) {
    for (const auto &[str, integer] : values) {
      const auto val = tej_str_to_int(str.c_str());
      assert(val == integer);
      benchmark::DoNotOptimize(&val);
    }
  }
}

BENCH(tej_sring_to_int);

int jz_sring_to_int(const char *str) {
  if (str == nullptr)
    return 0;

  int res = 0;  // Initialize result
  int sign = 1; // Initialize sign as positive

  // If number is negative, then update sign
  if (*str == '-') {
    sign = -1;
    str++; // Also update index of first digit
  }

  // Iterate through all digits of input string and update result
  for (uint8_t c = uint8_t(*str) - '0'; c <= 9; c = uint8_t(*++str) - '0') {
    res = res * 10 + int(c);
  }

  // Return result with sign
  return (*str == '\0' ? res * sign : 0);
}

BENCHMARK_DEFINE_F(string_data_fixture, jz_sring_to_int)
(benchmark::State &state) {

  for (auto _ : state) {
    for (const auto &[str, integer] : values) {
      const auto val = jz_sring_to_int(str.c_str());
      assert(val == integer);
      benchmark::DoNotOptimize(&val);
    }
  }
}

BENCH(jz_sring_to_int);

BENCHMARK_MAIN();
