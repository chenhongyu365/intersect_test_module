/*********************************************************************
 * @file    gme_cstrapi_api_solid_block_bench.cxx
 * @brief   gme_cstrapi.cxx 中接口gme_api_solid_block的测试用例
 * @details 比较api_solid_block 与 gme_api_solid_block 的性能差异
 * @author  赵川熠
 * @date    2024.9.22
 *********************************************************************/
#include <benchmark/benchmark.h>

// GME
// #include "template_simple_api.hxx"

// ACIS
#include "acis/cstrapi.hxx"
#include "acis_utils.hpp"
#include "same_entity.hpp"  // same_entity所在头文件

class gme_api_solid_block_bench : public benchmark::Fixture {
    int level = 0;

  protected:
    void SetUp(benchmark::State& state) override { level = initialize_acis(); }

    void TearDown(benchmark::State& state) override { terminate_acis(level); }
};

BENCHMARK_DEFINE_F(gme_api_solid_block_bench, acis_api_solid_block)(benchmark::State& state) {
    BODY* solid_block = nullptr;
    SPAposition pt1(-1.0, -1.0, 0.0);
    SPAposition pt2(4.0, 5.0, 3.0);
    for(auto _: state) {
        api_solid_block(pt1, pt2, solid_block);
    }
}

BENCHMARK_REGISTER_F(gme_api_solid_block_bench, acis_api_solid_block)->Unit(benchmark::kMillisecond);

BENCHMARK_DEFINE_F(gme_api_solid_block_bench, gme_api_solid_block)(benchmark::State& state) {
    BODY* solid_block = nullptr;
    SPAposition pt1(-1.0, -1.0, 0.0);
    SPAposition pt2(4.0, 5.0, 3.0);
    for(auto _: state) {
        gme_api_solid_block(pt1, pt2, solid_block);
    }
}

BENCHMARK_REGISTER_F(gme_api_solid_block_bench, gme_api_solid_block)->Unit(benchmark::kMillisecond);
