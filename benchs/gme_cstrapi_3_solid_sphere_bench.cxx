/*********************************************************************
 * @file    gme_cstrapi_solid_sphere_bench.cxx
 * @brief   基准测试 gme_3_api_solid_sphere 和 acis_api_solid_sphere 函数的性能
 * @details 通过不同参数创建球体，测量函数的执行时间
 * @author  王书瑶
 * @date    2024.10.16
 *********************************************************************/
#include <benchmark/benchmark.h>

// ACIS
#include "acis/cstrapi.hxx"
#include "acis_utils.hpp"
#include "same_entity.hpp"  // same_entity所在头文件

class Template2_Sample : public benchmark::Fixture {
    int level = 0;

  protected:
    void SetUp(benchmark::State& state) override { level = initialize_acis(); }

    void TearDown(benchmark::State& state) override { terminate_acis(level); }
};

BENCHMARK_DEFINE_F(Template2_Sample, acis_api_solid_sphere)(benchmark::State& state) {
    BODY* sph = nullptr;
    for(auto _: state) {
        api_solid_sphere(SPAposition(1, 2, -3), 12, sph);
    }
}

BENCHMARK_REGISTER_F(Template2_Sample, acis_api_solid_sphere)->Unit(benchmark::kMillisecond);

BENCHMARK_DEFINE_F(Template2_Sample, gme_3_api_solid_sphere)(benchmark::State& state) {
    BODY* sph = nullptr;
    for(auto _: state) {
        gme_3_api_solid_sphere(SPAposition(1, 2, -3), 12, sph);
    }
}

BENCHMARK_REGISTER_F(Template2_Sample, gme_3_api_solid_sphere)->Unit(benchmark::kMillisecond);