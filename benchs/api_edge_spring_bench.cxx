/*********************************************************************
 * @file    api_edge_spring_bench.cxx
 * @brief  gme_api_edge_spring接口的性能测试文件
 * @details  比较gme_api_edge_spring与api_edge_spring的性能差异
 * @author  charynnc
 * @date    2024.7.10
 *********************************************************************/
#include <benchmark/benchmark.h>

// ACIS
#include "acis/cstrapi.hxx"
#include "acis_utils.hpp"
#include "same_entity.hpp"  // same_entity所在头文件

class api_edge_spring_bench : public benchmark::Fixture {
    int level = 0;

  protected:
    void SetUp(benchmark::State& state) override { level = initialize_acis(); }

    void TearDown(benchmark::State& state) override { terminate_acis(level); }
};

BENCHMARK_DEFINE_F(api_edge_spring_bench, api_edge_spring)(benchmark::State& state) {
    EDGE* spring = nullptr;
    SPAposition axis_point(0.0, 0.0, 0.0);
    SPAvector axis_vector(1.0, 1.0, 1.0);
    SPAposition start_point(1.0, 0.0, 0.0);
    logical right_handed = FALSE;
    int helix_count = 3;
    double thread_distance_array[5] = {1, 2, 3, 0, 0};
    double rotation_angle_array[5] = {4 * M_PI, 6 * M_PI, 8 * M_PI, 0, 0};
    double transition_height_array[5] = {5, 5, 0, 0, 0};
    double transition_angle_array[5] = {2 * M_PI, 2 * M_PI, 0, 0, 0};
    for(auto _: state) {
        api_edge_spring(axis_point, axis_vector, start_point, right_handed, helix_count, thread_distance_array, rotation_angle_array, transition_height_array, transition_angle_array, spring);
    }
}

BENCHMARK_REGISTER_F(api_edge_spring_bench, api_edge_spring)->Unit(benchmark::kMillisecond);

BENCHMARK_DEFINE_F(api_edge_spring_bench, gme_api_edge_spring)(benchmark::State& state) {
    EDGE* spring = nullptr;
    SPAposition axis_point(0.0, 0.0, 0.0);
    SPAvector axis_vector(1.0, 1.0, 1.0);
    SPAposition start_point(1.0, 0.0, 0.0);
    logical right_handed = FALSE;
    int helix_count = 3;
    double thread_distance_array[5] = {1, 2, 3, 0, 0};
    double rotation_angle_array[5] = {4 * M_PI, 6 * M_PI, 8 * M_PI, 0, 0};
    double transition_height_array[5] = {5, 5, 0, 0, 0};
    double transition_angle_array[5] = {2 * M_PI, 2 * M_PI, 0, 0, 0};
    for(auto _: state) {
        gme_api_edge_spring(axis_point, axis_vector, start_point, right_handed, helix_count, thread_distance_array, rotation_angle_array, transition_height_array, transition_angle_array, spring);
    }
}

BENCHMARK_REGISTER_F(api_edge_spring_bench, gme_api_edge_spring)->Unit(benchmark::kMillisecond);
