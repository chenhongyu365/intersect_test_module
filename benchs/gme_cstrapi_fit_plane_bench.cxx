/*********************************************************************
 * @file    gme_cstrapi_fit_plane_bench.cxx
 * @brief
 * @details
 * @author  linchforever
 * @date    2024.8.5
 *********************************************************************/
#include <benchmark/benchmark.h>

// ACIS
#include "acis/cstrapi.hxx"
#include "acis/pladef.hxx"
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
BENCHMARK_DEFINE_F(Template1_Sample, acis_api_fit_plane)(benchmark::State& state) {
    SPAposition_vector point_list;
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(-100, 100);  // 左闭右闭区间，取点坐标的大小范围
    e.seed(time(0));
    for(int i = 0; i < 10; i++) {
        // 根据生成随机数生成点
        SPAposition temp_pos;
        temp_pos.set_x(u(e));
        temp_pos.set_y(u(e));
        temp_pos.set_z(u(e));
        point_list.push_back(temp_pos);
    }
    plane acis_plane;
    for(auto _: state) {
        api_fit_plane(point_list, acis_plane);
    }
}

BENCHMARK_REGISTER_F(Template1_Sample, acis_api_fit_plane)->Unit(benchmark::kMillisecond);

BENCHMARK_DEFINE_F(Template1_Sample, gme_api_fit_plane)(benchmark::State& state) {
    SPAposition_vector point_list;
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(-100, 100);  // 左闭右闭区间，取点坐标的大小范围
    e.seed(time(0));
    for(int i = 0; i < 10; i++) {
        // 根据生成随机数生成点
        SPAposition temp_pos;
        temp_pos.set_x(u(e));
        temp_pos.set_y(u(e));
        temp_pos.set_z(u(e));
        point_list.push_back(temp_pos);
    }
    plane gme_plane;
    for(auto _: state) {
        gme_api_fit_plane(point_list, gme_plane);
    }
}

BENCHMARK_REGISTER_F(Template1_Sample, gme_api_fit_plane)->Unit(benchmark::kMillisecond);