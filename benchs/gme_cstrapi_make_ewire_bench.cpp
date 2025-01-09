/*********************************************************************
 * @file    gme_cstrapi_make_ewire_bench.cxx
 * @brief
 * @details
 * @author  王书瑶
 * @date    2024.11.14
 *********************************************************************/

#include <benchmark/benchmark.h>

// ACIS
#include "acis/cstrapi.hxx"
#include "acis_utils.hpp"
#include "same_entity.hpp"  // same_entity所在头文件

class Template3_Sample : public benchmark::Fixture {
    int level = 0;

  protected:
    void SetUp(benchmark::State& state) override { level = initialize_acis(); }

    void TearDown(benchmark::State& state) override { terminate_acis(level); }
};

BENCHMARK_DEFINE_F(Template3_Sample, acis_api_make_ewire)(benchmark::State& state) {
    int num_edges = 5;  // 你可以根据需要调整边的数量
    EDGE* edges[5];     // 这里需要初始化 edges 数组
    BODY* en = nullptr;

    // 初始化边的内容
    for(int i = 0; i < num_edges; ++i) {
        APOINT* start_apoint = ACIS_NEW APOINT(i, 0, 0);    // 起始点参数
        APOINT* end_apoint = ACIS_NEW APOINT(i + 1, 0, 0);  // 结束点参数
        VERTEX* start_vertex = ACIS_NEW VERTEX(start_apoint);
        VERTEX* end_vertex = ACIS_NEW VERTEX(end_apoint);
        edges[i] = ACIS_NEW EDGE(start_vertex, end_vertex, nullptr, FORWARD);  // 初始化边
    }

    for(auto _: state) {
        api_make_ewire(num_edges, edges, en);
    }
}

BENCHMARK_REGISTER_F(Template3_Sample, acis_api_make_ewire)->Unit(benchmark::kMillisecond);

BENCHMARK_DEFINE_F(Template3_Sample, gme_cstrapi_make_ewire)(benchmark::State& state) {
    int num_edges = 5;  // 你可以根据需要调整边的数量
    EDGE* edges[5];     // 这里需要初始化 edges 数组
    BODY* en = nullptr;

    // 初始化边的内容
    for(int i = 0; i < num_edges; ++i) {
        APOINT* start_apoint = ACIS_NEW APOINT(i, 0, 0);    // 起始点参数
        APOINT* end_apoint = ACIS_NEW APOINT(i + 1, 0, 0);  // 结束点参数
        VERTEX* start_vertex = ACIS_NEW VERTEX(start_apoint);
        VERTEX* end_vertex = ACIS_NEW VERTEX(end_apoint);
        edges[i] = ACIS_NEW EDGE(start_vertex, end_vertex, nullptr, FORWARD);  // 初始化边
    }

    for(auto _: state) {
        gme_api_make_ewire(num_edges, edges, en);
    }
}

BENCHMARK_REGISTER_F(Template3_Sample, gme_cstrapi_make_ewire)->Unit(benchmark::kMillisecond);
