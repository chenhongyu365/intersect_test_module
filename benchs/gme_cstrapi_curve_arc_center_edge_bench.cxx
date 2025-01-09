/*********************************************************************
 * @file    gme_cstrapi_curve_arc_center_edge_bench.cxx
 * @brief  gme_cstrapi_curve_arc_center_edge接口的性能测试文件
 * @details  比较gme_cstrapi_curve_arc_center_edge与api_curve_arc_center_edge的性能差异
 * @author  evertravel
 * @date    2024.9.25
 *********************************************************************/
#include <benchmark/benchmark.h>

#include <ctime>
#include <random>

// ACIS
#include "access.hpp"
#include "acis/cstrapi.hxx"
#include "acis_utils.hpp"
#include "same_entity.hpp"  // same_entity所在头文件

class Curve_Arc_Center_Edge_Sample : public benchmark::Fixture {
    int level = 0;

  protected:
    void SetUp(benchmark::State& state) override { level = initialize_acis(); }

    void TearDown(benchmark::State& state) override { terminate_acis(level); }
};

BENCHMARK_DEFINE_F(Curve_Arc_Center_Edge_Sample, acis_api_curve_arc_center_edge)(benchmark::State& state) {
    EDGE* acis_arc = nullptr;  // acis api创建的arc
    // 生成随机数种子
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(-10000, 10000);  // 坐标点的取值范围
    std::uniform_real_distribution<double> v(-10, 10);        // 法向向量的大小范围
    e.seed(time(0));
    // 生成随机center、pt1、pt2、norm
    SPAposition center = {u(e), u(e), u(e)};
    SPAposition pt1 = {u(e), u(e), u(e)};
    SPAposition pt2 = {u(e), u(e), u(e)};
    SPAunit_vector norm = {v(e), v(e), v(e)};
    for(auto _: state) {
        api_curve_arc_center_edge(center, pt1, pt2, &norm, acis_arc);
    }
}

BENCHMARK_REGISTER_F(Curve_Arc_Center_Edge_Sample, acis_api_curve_arc_center_edge)->Unit(benchmark::kMillisecond);

BENCHMARK_DEFINE_F(Curve_Arc_Center_Edge_Sample, gme_cstrapi_curve_arc_center_edge)(benchmark::State& state) {
    EDGE* gme_arc = nullptr;  // acis api创建的arc
    // 生成随机数种子
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(-10000, 10000);  // 坐标点的取值范围
    std::uniform_real_distribution<double> v(-10, 10);        // 法向向量的大小范围
    e.seed(time(0));
    // 生成随机center、pt1、pt2、norm
    SPAposition center = {u(e), u(e), u(e)};
    SPAposition pt1 = {u(e), u(e), u(e)};
    SPAposition pt2 = {u(e), u(e), u(e)};
    SPAunit_vector norm = {v(e), v(e), v(e)};
    for(auto _: state) {
        gme_api_curve_arc_center_edge(center, pt1, pt2, &norm, gme_arc);
    }
}

BENCHMARK_REGISTER_F(Curve_Arc_Center_Edge_Sample, gme_cstrapi_curve_arc_center_edge)->Unit(benchmark::kMillisecond);
