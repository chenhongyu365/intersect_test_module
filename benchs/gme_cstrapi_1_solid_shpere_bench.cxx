/*********************************************************************
 * @file    gme_cstrapi_1_solid_sphere_bench.cxx
 * @brief
 * @details
 * @author  evertravel
 * @date    2024.9.20
 *********************************************************************/
#include <benchmark/benchmark.h>

// ACIS
#include "acis/cstrapi.hxx"
#include "acis_utils.hpp"
#include "same_entity.hpp"  // same_entity所在头文件

class Template1_Sample : public benchmark::Fixture {
    int level = 0;

  protected:
    void SetUp(benchmark::State& state) override { level = initialize_acis(); }

    void TearDown(benchmark::State& state) override { terminate_acis(level); }
};

BENCHMARK_DEFINE_F(Template1_Sample, acis_api_solid_sphere)(benchmark::State& state) {
    BODY* sph = nullptr;
    for(auto _: state) {
        api_solid_sphere(SPAposition(1, 2, -3), 12, sph);
    }
}

BENCHMARK_REGISTER_F(Template1_Sample, acis_api_solid_sphere)->Unit(benchmark::kMillisecond);

BENCHMARK_DEFINE_F(Template1_Sample, gme_1_api_solid_sphere)(benchmark::State& state) {
    BODY* sph = nullptr;
    for(auto _: state) {
        gme_1_api_solid_sphere(SPAposition(1, 2, -3), 12, sph);
    }
}

BENCHMARK_REGISTER_F(Template1_Sample, gme_1_api_solid_sphere)->Unit(benchmark::kMillisecond);
