/*********************************************************************
 * @file    gme_cstrapi_api_loop_external_bench.cxx
 * @brief   接口 gme_api_loop_external 的性能测试
 * @details
 * @author  赵川熠
 * @date    2024.10.5
 *********************************************************************/
#include <benchmark/benchmark.h>

// ACIS
#include "acis/cstrapi.hxx"
#include "acis_utils.hpp"
#include "same_entity.hpp"  // same_entity所在头文件

class gme_api_loop_external_bench : public benchmark::Fixture {
    int level = 0;

  protected:
    void SetUp(benchmark::State& state) override { level = initialize_acis(); }

    void TearDown(benchmark::State& state) override { terminate_acis(level); }
};

BENCHMARK_DEFINE_F(gme_api_loop_external_bench, acis_api_loop_external)(benchmark::State& state) {
    logical* acis_external = nullptr;
    BODY* cube = nullptr;
    LOOP* loop = nullptr;
    // 创建一个方块，取其中一个边
    api_make_cuboid(5, 6, 4, cube, nullptr);
    loop = cube->lump()->shell()->face()->loop();

    for(auto _: state) {
        api_loop_external(loop, acis_external, nullptr);
    }
}

BENCHMARK_REGISTER_F(gme_api_loop_external_bench, acis_api_loop_external)->Unit(benchmark::kMillisecond);

BENCHMARK_DEFINE_F(gme_api_loop_external_bench, gme_api_loop_external)(benchmark::State& state) {
    logical* gme_external = nullptr;
    BODY* cube = nullptr;
    LOOP* loop = nullptr;
    // 创建一个方块，取其中一个边
    api_make_cuboid(5, 6, 4, cube, nullptr);
    loop = cube->lump()->shell()->face()->loop();

    for(auto _: state) {
        gme_api_loop_external(loop, gme_external, nullptr);
    }
}

BENCHMARK_REGISTER_F(gme_api_loop_external_bench, gme_api_loop_external)->Unit(benchmark::kMillisecond);
