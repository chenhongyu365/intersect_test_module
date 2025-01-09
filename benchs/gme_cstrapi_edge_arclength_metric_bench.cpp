/*********************************************************************
 * @file    gme_cstrapi_edge_arclength_metric_bench.cxx
 * @brief    gme_api_edge_arclength_metric的性能测试文件
 * @details   比较gme_api_edge_arclength_metric与api_edge_arclength_metric的性能差异
 * @author  Dubopei
 * @date    2024.9.24
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

BENCHMARK_DEFINE_F(Constructors_Sample, acis_api_edge_arclength_metric)(benchmark::State& state) {
    BODY* sph = nullptr;
    double acis_m;
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(-1e4, 1e20);  // 左闭右闭区间，取点坐标的大小范围
    e.seed(time(0));
    SPAposition p[3] = {SPAposition(u(e), u(e), u(e)), SPAposition(u(e), u(e), u(e)), SPAposition(u(e), u(e), u(e))};
    double weight[3] = {1.2, 2.5, 3.4};  // 需递增
    EDGE* edge = nullptr;
    api_curve_spline2(3, p, weight, new SPAunit_vector(0, 1, 0), new SPAunit_vector(1, -1, 0), edge);
    for(auto _: state) {
        api_edge_arclength_metric(edge, acis_m);
    }
}

BENCHMARK_REGISTER_F(Constructors_Sample, acis_api_edge_arclength_metric)->Unit(benchmark::kMillisecond);

BENCHMARK_DEFINE_F(Constructors_Sample, gme_cstrapi_edge_arclength_metric)(benchmark::State& state) {
    BODY* sph = nullptr;
    double gme_m;
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(-1e4, 1e20);  // 左闭右闭区间，取点坐标的大小范围
    e.seed(time(0));
    SPAposition p[3] = {SPAposition(u(e), u(e), u(e)), SPAposition(u(e), u(e), u(e)), SPAposition(u(e), u(e), u(e))};
    double weight[3] = {1.2, 2.5, 3.4};  // 需递增
    EDGE* edge = nullptr;
    api_curve_spline2(3, p, weight, new SPAunit_vector(0, 1, 0), new SPAunit_vector(1, -1, 0), edge);
    for(auto _: state) {
        gme_1_api_edge_arclength_metric(edge, gme_m);
    }
}

BENCHMARK_REGISTER_F(Constructors_Sample, gme_cstrapi_edge_arclength_metric)->Unit(benchmark::kMillisecond);