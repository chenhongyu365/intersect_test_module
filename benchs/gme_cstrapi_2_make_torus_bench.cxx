/*********************************************************************
 * @file    gme_cstrapi_2_make_torus_bench.cxx
 * @brief
 * @details
 * @author  lichenyu
 * @date    2024.9.29
 *********************************************************************/

#include <benchmark/benchmark.h>

// ACIS
#include "acis/cstrapi.hxx"
#include "acis/entwray.hxx"
#include "acis_utils.hpp"
#include "ctime"
#include "random"
#include "same_entity.hpp"

class api_2_Make_Torus : public benchmark::Fixture {
    int level = 0;

  protected:
    void SetUp(benchmark::State& state) override { level = initialize_acis(); }

    void TearDown(benchmark::State& state) override { terminate_acis(level); }
};

BENCHMARK_DEFINE_F(api_2_Make_Torus, api_make_torus)(benchmark::State& state) {
    BODY* acis_body = nullptr;
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            for(auto _: state) {
                api_make_torus(i, j, acis_body);
            }
        }
    }
}
BENCHMARK_REGISTER_F(api_2_Make_Torus, api_make_torus)->Unit(benchmark::kMillisecond);

BENCHMARK_DEFINE_F(api_2_Make_Torus, gme_2_api_make_torus)(benchmark::State& state) {
    BODY* gme_body = nullptr;
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            for(auto _: state) {
                gme_api_make_torus(i, j, gme_body);
            }
        }
    }
}
BENCHMARK_REGISTER_F(api_2_Make_Torus, gme_2_api_make_torus)->Unit(benchmark::kMillisecond);