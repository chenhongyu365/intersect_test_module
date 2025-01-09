/*********************************************************************
 * @file    gme_api_edge_arclength_metric_bench.cxx
 * @brief
 * @details
 * @author  mshct
 * @date    2024.8.2
 *********************************************************************/
#include <benchmark/benchmark.h>

#include <iostream>

// ACIS
#include "acis/cstrapi.hxx"
#include "acis_utils.hpp"
#include "same_entity.hpp"  // same_entity所在头文件

class Edge_Arclength_Metric_Sample : public benchmark::Fixture {
    int level = 0;

  protected:
    void SetUp(benchmark::State& state) override { level = initialize_acis(); }

    void TearDown(benchmark::State& state) override { terminate_acis(level); }
};

BENCHMARK_DEFINE_F(Edge_Arclength_Metric_Sample, acis_api_edge_arclength_metric)(benchmark::State& state) {
    SPAposition p[3] = {SPAposition(-1, 0, 0), SPAposition(0, 1, 0), SPAposition(1, 0, 0)};
    double weight[3] = {0.5, 1, 2};
    EDGE* edge = nullptr;
    api_curve_spline2(3, p, weight, new SPAunit_vector(0, 1, 0), new SPAunit_vector(1, -1, 0), edge);
    double acis_m;
    for(auto _: state) {
        api_edge_arclength_metric(edge, acis_m);
    }
}

BENCHMARK_REGISTER_F(Edge_Arclength_Metric_Sample, acis_api_edge_arclength_metric)->Unit(benchmark::kMillisecond);

BENCHMARK_DEFINE_F(Edge_Arclength_Metric_Sample, gme_api_edge_arclength_metric0)(benchmark::State& state) {
    SPAposition p[3] = {SPAposition(-1, 0, 0), SPAposition(0, 1, 0), SPAposition(1, 0, 0)};
    double weight[3] = {0.5, 1, 2};
    EDGE* edge = nullptr;
    api_curve_spline2(3, p, weight, new SPAunit_vector(0, 1, 0), new SPAunit_vector(1, -1, 0), edge);
    double gme_m;
    for(auto _: state) {
        gme_api_edge_arclength_metric(edge, gme_m);
    }
}

BENCHMARK_REGISTER_F(Edge_Arclength_Metric_Sample, gme_api_edge_arclength_metric0)->Unit(benchmark::kMillisecond);
