/*********************************************************************
 * @file    gme_cstrapi_curve_arc_diagonal_bench.cxx
 * @brief    gme_api_curve_arc_diagonal接口的性能测试文件
 * @details   比较gme_api_curve_arc_diagonal与api_curve_arc_diagonal的性能差异
 * @author  Dubopei
 * @date    2024.9.23
 *********************************************************************/
#include <benchmark/benchmark.h>

// ACIS
#include "acis/cstrapi.hxx"
#include "acis_utils.hpp"
#include "ctime"   // 用于生成随机数
#include "random"  // 用于生成随机数

class Constructors_Sample : public benchmark::Fixture {
    int level = 0;

  protected:
    void SetUp(benchmark::State& state) override { level = initialize_acis(); }

    void TearDown(benchmark::State& state) override { terminate_acis(level); }
};

BENCHMARK_DEFINE_F(Constructors_Sample, acis_api_curve_arc_full_diagonal)(benchmark::State& state) {
    EDGE* arc = nullptr;
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(-1e4, 1e20);  // 左闭右闭区间，取点坐标的大小范围
    e.seed(time(0));
    SPAposition pt1(u(e), u(e), u(e));
    SPAposition pt2(u(e), u(e), u(e));
    double radius = u(e);
    for(auto _: state) {
        api_curve_arc_diagonal(pt1, pt2, 1, arc);
    }
}

BENCHMARK_REGISTER_F(Constructors_Sample, acis_api_curve_arc_full_diagonal)->Unit(benchmark::kMillisecond);

BENCHMARK_DEFINE_F(Constructors_Sample, gme_api_curve_arc_full_diagonal)(benchmark::State& state) {
    EDGE* arc = nullptr;
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(-1e4, 1e20);  // 左闭右闭区间，取点坐标的大小范围
    e.seed(time(0));
    SPAposition pt1(u(e), u(e), u(e));
    SPAposition pt2(u(e), u(e), u(e));
    double radius = u(e);
    for(auto _: state) {
        gme_api_curve_arc_diagonal(pt1, pt2, 1, arc);
    }
}

BENCHMARK_REGISTER_F(Constructors_Sample, gme_api_curve_arc_full_diagonal)->Unit(benchmark::kMillisecond);

BENCHMARK_DEFINE_F(Constructors_Sample, acis_api_curve_arc_nofull_diagonal)(benchmark::State& state) {
    EDGE* arc = nullptr;
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(-1e4, 1e20);  // 左闭右闭区间，取点坐标的大小范围
    e.seed(time(0));
    SPAposition pt1(u(e), u(e), u(e));
    SPAposition pt2(u(e), u(e), u(e));
    double radius = u(e);
    for(auto _: state) {
        api_curve_arc_diagonal(pt1, pt2, 0, arc);
    }
}

BENCHMARK_REGISTER_F(Constructors_Sample, acis_api_curve_arc_nofull_diagonal)->Unit(benchmark::kMillisecond);

BENCHMARK_DEFINE_F(Constructors_Sample, gme_api_curve_arc_nofull_diagonal)(benchmark::State& state) {
    EDGE* arc = nullptr;
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(-1e4, 1e20);  // 左闭右闭区间，取点坐标的大小范围
    e.seed(time(0));
    SPAposition pt1(u(e), u(e), u(e));
    SPAposition pt2(u(e), u(e), u(e));
    double radius = u(e);
    for(auto _: state) {
        gme_api_curve_arc_diagonal(pt1, pt2, 0, arc);
    }
}

BENCHMARK_REGISTER_F(Constructors_Sample, gme_api_curve_arc_nofull_diagonal)->Unit(benchmark::kMillisecond);
