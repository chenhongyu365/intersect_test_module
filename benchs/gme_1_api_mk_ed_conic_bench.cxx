/*********************************************************************
 * @file    gem_1_api_mk_ed_conic_bench.cxx
 * @brief   接口gme_1_api_mk_ed_conic的性能测试
 * @details
 * @author  赵川熠Ori
 * @date    2024.9.28
 *********************************************************************/
#include <benchmark/benchmark.h>

// GME
// #include "template_simple_api.hxx"

// ACIS
#include "acis/cstrapi.hxx"
#include "acis_utils.hpp"
#include "same_entity.hpp"  // same_entity所在头文件

class Gme1ApiMakeEdgeConic : public benchmark::Fixture {
    int level = 0;

  protected:
    void SetUp(benchmark::State& state) override { level = initialize_acis(); }

    void TearDown(benchmark::State& state) override { terminate_acis(level); }
};

BENCHMARK_DEFINE_F(Gme1ApiMakeEdgeConic, acis_api_mk_ed_conic)(benchmark::State& state) {
    EDGE* curve = nullptr;
    SPAposition start(2, 5, 8);
    SPAunit_vector start_tan(2, 7, 6);
    SPAposition end(489, 652, 7894);
    SPAunit_vector end_tan(5, 3, 2);
    double rho = 0.3;
    for(auto _: state) {
        api_mk_ed_conic(start, start_tan, end, end_tan, rho, curve, nullptr);
    }
}

BENCHMARK_REGISTER_F(Gme1ApiMakeEdgeConic, acis_api_mk_ed_conic)->Unit(benchmark::kMillisecond);

BENCHMARK_DEFINE_F(Gme1ApiMakeEdgeConic, gme_api_mk_ed_conic)(benchmark::State& state) {
    EDGE* curve = nullptr;
    SPAposition start(2, 5, 8);
    SPAunit_vector start_tan(2, 7, 6);
    SPAposition end(489, 652, 7894);
    SPAunit_vector end_tan(5, 3, 2);
    double rho = 0.3;
    for(auto _: state) {
        gme_1_api_mk_ed_conic(start, start_tan, end, end_tan, rho, curve, nullptr);
    }
}

BENCHMARK_REGISTER_F(Gme1ApiMakeEdgeConic, gme_api_mk_ed_conic)->Unit(benchmark::kMillisecond);
