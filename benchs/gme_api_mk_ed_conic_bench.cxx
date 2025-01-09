/*********************************************************************
 * @file    gme_api_mk_ed_conic_bench.cxx
 * @brief
 * @details
 * @author  mshct
 * @date    2024.7.31
 *********************************************************************/
#include <benchmark/benchmark.h>

#include <ctime>
#include <random>

// ACIS
#include "access.hpp"
#include "acis/cstrapi.hxx"
#include "acis_utils.hpp"
#include "same_entity.hpp"  // same_entity所在头文件

class Mk_Ed_Conic_Sample : public benchmark::Fixture {
    int level = 0;

  protected:
    void SetUp(benchmark::State& state) override { level = initialize_acis(); }

    void TearDown(benchmark::State& state) override { terminate_acis(level); }
};

BENCHMARK_DEFINE_F(Mk_Ed_Conic_Sample, acis_api_mk_ed_conic)(benchmark::State& state) {
    EDGE* acis_edge = nullptr;  // acis api创建的edge
    // 生成随机数种子
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(-10000, 10000);  // 点坐标的大小范围
    std::uniform_real_distribution<double> v(-10, 10);        // 方向向量的大小范围
    std::uniform_real_distribution<double> w(0, 1);           // ρ的大小范围
    std::uniform_int_distribution<int> ni(0, 999);
    e.seed(time(0));
    // 生成随机点、方向、ρ
    SPAposition start = {u(e), u(e), u(e)};
    SPAposition end = {u(e), u(e), u(e)};
    SPAunit_vector start_tan = {v(e), v(e), v(e)};
    SPAunit_vector end_tan = {v(e), v(e), v(e)};
    double rho = w(e);
    int i = ni(e);
    if(i % 3 == 0)
        end = start + u(e) * start_tan + u(e) * end_tan;
    else if(i % 3 == 1)
        end_tan = normalise(w(e) * (end - start) + u(e) * start_tan);
    else if(i % 3 == 2)
        start_tan = normalise(w(e) * (end - start) + u(e) * end_tan);
    for(auto _: state) {
        api_mk_ed_conic(start, start_tan, end, end_tan, rho, acis_edge);
    }
}

BENCHMARK_REGISTER_F(Mk_Ed_Conic_Sample, acis_api_mk_ed_conic)->Unit(benchmark::kMillisecond);

BENCHMARK_DEFINE_F(Mk_Ed_Conic_Sample, gme_api_mk_ed_conic0)(benchmark::State& state) {
    EDGE* gme_edge = nullptr;  // gme api创建的edge
    // 生成随机数种子
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(-10000, 10000);  // 点坐标的大小范围
    std::uniform_real_distribution<double> v(-10, 10);        // 方向向量的大小范围
    std::uniform_real_distribution<double> w(0, 1);           // ρ的大小范围
    std::uniform_int_distribution<int> ni(0, 999);
    e.seed(time(0));
    // 生成随机点、方向、ρ
    SPAposition start = {u(e), u(e), u(e)};
    SPAposition end = {u(e), u(e), u(e)};
    SPAunit_vector start_tan = {v(e), v(e), v(e)};
    SPAunit_vector end_tan = {v(e), v(e), v(e)};
    double rho = w(e);
    int i = ni(e);
    if(i % 3 == 0)
        end = start + u(e) * start_tan + u(e) * end_tan;
    else if(i % 3 == 1)
        end_tan = normalise(w(e) * (end - start) + u(e) * start_tan);
    else if(i % 3 == 2)
        start_tan = normalise(w(e) * (end - start) + u(e) * end_tan);
    for(auto _: state) {
        gme_api_mk_ed_conic(start, start_tan, end, end_tan, rho, gme_edge);
    }
}

BENCHMARK_REGISTER_F(Mk_Ed_Conic_Sample, gme_api_mk_ed_conic0)->Unit(benchmark::kMillisecond);
