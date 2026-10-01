
#include "uni_ptr.hpp"
#include "share_ptr.hpp"
#include "test.hpp"
#include "assertions.hpp"
#include <chrono>
#include <vector>
#include <iostream>
 
namespace {
 
using bench_clock = std::chrono::steady_clock;
 
double to_ms(bench_clock::duration d){
    return std::chrono::duration<double, std::milli>(d).count();
}
 
constexpr int N = 100000;
 
}

TEST(benchmark_raw_vs_uni_ptr_vs_share_ptr){//сырой
    auto raw_data = new int*[N];
    auto t0 = bench_clock::now();
    for (int i = 0; i < N; ++i) { raw_data[i] = new int(i); }
    auto t1 = bench_clock::now();
    for (int i = 0; i < N; ++i) { sum += *raw_data[i]; }
    auto t2 = bench_clock::now();
    for (int i = 0; i < N; ++i) { delete raw_data[i]; }
    auto t3 = bench_clock::now();
    delete[] raw_data;
 
    double raw_create = to_ms(t1 - t0);
    double raw_read = to_ms(t2 - t1);
    double raw_delete = to_ms(t3 - t2);
 
    std::vector<uni_ptr<int>> uni_data;  //uni_ptr
    uni_data.reserve(N);
    auto u0 = bench_clock::now();
    for (int i = 0; i < N; ++i) { uni_data.push_back(uni_ptr<int>(new int(i))); }
    auto u1 = bench_clock::now();
    sum = 0;
    for (int i = 0; i < N; ++i) { sum += *uni_data[i]; }
    auto u2 = bench_clock::now();
    uni_data.clear();
    auto u3 = bench_clock::now();
 
    double uni_create = to_ms(u1 - u0);
    double uni_read = to_ms(u2 - u1);
    double uni_delete = to_ms(u3 - u2);

    std::vector<share_ptr<int>> shr_data;//share_ptr
    shr_data.reserve(N);
    auto s0 = bench_clock::now();
    for (int i = 0; i < N; ++i) { shr_data.push_back(share_ptr<int>(new int(i))); }
    auto s1 = bench_clock::now();
    sum = 0;
    for (int i = 0; i < N; ++i) { sum += *shr_data[i]; }
    auto s2 = bench_clock::now();
    shr_data.clear();
    auto s3 = bench_clock::now();
 
    double shr_create = to_ms(s1 - s0);
    double shr_read = to_ms(s2 - s1);
    double shr_delete = to_ms(s3 - s2);
 
    std::cerr << "\n| Указатель   | Создание, мс | Чтение, мс | Удаление, мс |\n";
    std::cerr <<   "| ----------- | ------------ | ---------- | ------------ |\n";
    std::cerr <<   "| Raw         | " << raw_create << " | " << raw_read << " | " << raw_delete << " |\n";
    std::cerr <<   "| uni_ptr     | " << uni_create << " | " << uni_read << " | " << uni_delete << " |\n";
    std::cerr <<   "| share_ptr   | " << shr_create << " | " << shr_read << " | " << shr_delete << " |\n\n";
 
    expected_true("нагрузочный тест выполнен без падения", true);
}
 
