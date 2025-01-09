/*********************************************************************
 * @file    gme_cstrapi_1_make_frustum_bench.cxx
 * @brief
 * @details
 * @author  linchforever
 * @date    2024.7.26
 *********************************************************************/
#include <benchmark/benchmark.h>

// GME
// #include "template_simple_api.hxx"

// ACIS
#include "acis/cstrapi.hxx"
#include "acis_utils.hpp"
#include "ctime"            // 用于生成随机数
#include "random"           // 用于生成随机数
#include "same_entity.hpp"  // same_entity所在头文件

class Template1_Sample : public benchmark::Fixture {
    int level = 0;

  protected:
    void SetUp(benchmark::State& state) override { level = initialize_acis(); }

    void TearDown(benchmark::State& state) override { terminate_acis(level); }
};

BENCHMARK_DEFINE_F(Template1_Sample, acis_api_make_frustum)(benchmark::State& state) {
    BODY* en = nullptr;
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(-1e4, 1e20);  // 左闭右闭区间，取点坐标的大小范围
    e.seed(time(0));
    double height = u(e);
    double radius1 = u(e);
    double radius2 = u(e);
    double top = u(e);
    for(auto _: state) {
        api_make_frustum(height, radius1, radius2, top, en);
    }
}

BENCHMARK_REGISTER_F(Template1_Sample, acis_api_make_frustum)->Unit(benchmark::kMillisecond);

BENCHMARK_DEFINE_F(Template1_Sample, gme_cstrapi_1_make_frustum)(benchmark::State& state) {
    BODY* en = nullptr;
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(-1e4, 1e20);  // 左闭右闭区间，取点坐标的大小范围
    e.seed(time(0));
    double height = u(e);
    double radius1 = u(e);
    double radius2 = u(e);
    double top = u(e);
    for(auto _: state) {
        gme_1_api_make_frustum(height, radius1, radius2, top, en);
    }
}

BENCHMARK_REGISTER_F(Template1_Sample, gme_cstrapi_1_make_frustum)->Unit(benchmark::kMillisecond);
