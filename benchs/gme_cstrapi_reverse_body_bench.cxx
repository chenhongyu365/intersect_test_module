/*********************************************************************
 * @file    gme_cstrapi_reverse_body_bench.cxx
 * @brief  gme_api_reverse_body接口的性能测试文件
 * @details  比较gme_api_reverse_body与api_reverse_body的性能差异
 * @author  charynnc
 * @date    2024.7.30
 *********************************************************************/
#include <benchmark/benchmark.h>

// ACIS
#include "acis/cstrapi.hxx"
#include "acis_utils.hpp"
#include "same_entity.hpp"  // same_entity所在头文件

class api_reverse_body_bench : public benchmark::Fixture {
    int level = 0;

  protected:
    void SetUp(benchmark::State& state) override { level = initialize_acis(); }

    void TearDown(benchmark::State& state) override { terminate_acis(level); }
};

BENCHMARK_DEFINE_F(api_reverse_body_bench, acis_api_reverse_body)(benchmark::State& state) {
    BODY* body = nullptr;
    api_make_cuboid(1, 3, 2, body);
    for(auto _: state) {
        api_reverse_body(body);
    }
}

BENCHMARK_REGISTER_F(api_reverse_body_bench, acis_api_reverse_body)->Unit(benchmark::kMillisecond);

BENCHMARK_DEFINE_F(api_reverse_body_bench, gme_api_reverse_body)(benchmark::State& state) {
    BODY* body = nullptr;
    api_make_cuboid(1, 3, 2, body);
    for(auto _: state) {
        gme_api_reverse_body(body);
    }
}

BENCHMARK_REGISTER_F(api_reverse_body_bench, gme_api_reverse_body)->Unit(benchmark::kMillisecond);
