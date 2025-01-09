/*********************************************************************
 * @file    gme_cstrapi_fit_line_bench.cxx
 * @brief
 * @details
 * @author  全志成
 * @date    2024.7.22
 *********************************************************************/
#include <benchmark/benchmark.h>

// ACIS
#include "acis/cstrapi.hxx"
#include "acis/strdef.hxx"
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
BENCHMARK_DEFINE_F(Template1_Sample, acis_api_fit_line1)(benchmark::State& state) {
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
    straight acis_straight;
    for(auto _: state) {
        api_fit_line(point_list, acis_straight);
    }
}

BENCHMARK_REGISTER_F(Template1_Sample, acis_api_fit_line1)->Unit(benchmark::kMillisecond);

BENCHMARK_DEFINE_F(Template1_Sample, gme_api_fit_line1)(benchmark::State& state) {
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
    straight gme_straight;
    for(auto _: state) {
        gme_api_fit_line(point_list, gme_straight);
    }
}

BENCHMARK_REGISTER_F(Template1_Sample, gme_api_fit_line1)->Unit(benchmark::kMillisecond);

BENCHMARK_DEFINE_F(Template1_Sample, acis_api_fit_line2)(benchmark::State& state) {
    SPAposition_vector point_list;
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(-100, 100);  // 左闭右闭区间，取点坐标的大小范围
    e.seed(time(0));
    for(int i = 0; i < 100; i++) {
        // 根据生成随机数生成点
        SPAposition temp_pos;
        temp_pos.set_x(u(e));
        temp_pos.set_y(u(e));
        temp_pos.set_z(u(e));
        point_list.push_back(temp_pos);
    }
    straight acis_straight;
    for(auto _: state) {
        api_fit_line(point_list, acis_straight);
    }
}

BENCHMARK_REGISTER_F(Template1_Sample, acis_api_fit_line2)->Unit(benchmark::kMillisecond);

BENCHMARK_DEFINE_F(Template1_Sample, gme_api_fit_line2)(benchmark::State& state) {
    SPAposition_vector point_list;
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(-100, 100);  // 左闭右闭区间，取点坐标的大小范围
    e.seed(time(0));
    for(int i = 0; i < 100; i++) {
        // 根据生成随机数生成点
        SPAposition temp_pos;
        temp_pos.set_x(u(e));
        temp_pos.set_y(u(e));
        temp_pos.set_z(u(e));
        point_list.push_back(temp_pos);
    }
    straight gme_straight;
    for(auto _: state) {
        gme_api_fit_line(point_list, gme_straight);
    }
}

BENCHMARK_REGISTER_F(Template1_Sample, gme_api_fit_line2)->Unit(benchmark::kMillisecond);

BENCHMARK_DEFINE_F(Template1_Sample, acis_api_fit_line3)(benchmark::State& state) {
    SPAposition_vector point_list;
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(-100, 100);  // 左闭右闭区间，取点坐标的大小范围
    e.seed(time(0));
    for(int i = 0; i < 1000; i++) {
        // 根据生成随机数生成点
        SPAposition temp_pos;
        temp_pos.set_x(u(e));
        temp_pos.set_y(u(e));
        temp_pos.set_z(u(e));
        point_list.push_back(temp_pos);
    }
    straight acis_straight;
    for(auto _: state) {
        api_fit_line(point_list, acis_straight);
    }
}

BENCHMARK_REGISTER_F(Template1_Sample, acis_api_fit_line3)->Unit(benchmark::kMillisecond);

BENCHMARK_DEFINE_F(Template1_Sample, gme_api_fit_line3)(benchmark::State& state) {
    SPAposition_vector point_list;
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(-100, 100);  // 左闭右闭区间，取点坐标的大小范围
    e.seed(time(0));
    for(int i = 0; i < 1000; i++) {
        // 根据生成随机数生成点
        SPAposition temp_pos;
        temp_pos.set_x(u(e));
        temp_pos.set_y(u(e));
        temp_pos.set_z(u(e));
        point_list.push_back(temp_pos);
    }
    straight gme_straight;
    for(auto _: state) {
        gme_api_fit_line(point_list, gme_straight);
    }
}

BENCHMARK_REGISTER_F(Template1_Sample, gme_api_fit_line3)->Unit(benchmark::kMillisecond);

BENCHMARK_DEFINE_F(Template1_Sample, acis_api_fit_line4)(benchmark::State& state) {
    SPAposition_vector point_list;
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(-100, 100);  // 左闭右闭区间，取点坐标的大小范围
    e.seed(time(0));
    for(int i = 0; i < 10000; i++) {
        // 根据生成随机数生成点
        SPAposition temp_pos;
        temp_pos.set_x(u(e));
        temp_pos.set_y(u(e));
        temp_pos.set_z(u(e));
        point_list.push_back(temp_pos);
    }
    straight acis_straight;
    for(auto _: state) {
        api_fit_line(point_list, acis_straight);
    }
}

BENCHMARK_REGISTER_F(Template1_Sample, acis_api_fit_line4)->Unit(benchmark::kMillisecond);

BENCHMARK_DEFINE_F(Template1_Sample, gme_api_fit_line4)(benchmark::State& state) {
    SPAposition_vector point_list;
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(-100, 100);  // 左闭右闭区间，取点坐标的大小范围
    e.seed(time(0));
    for(int i = 0; i < 10000; i++) {
        // 根据生成随机数生成点
        SPAposition temp_pos;
        temp_pos.set_x(u(e));
        temp_pos.set_y(u(e));
        temp_pos.set_z(u(e));
        point_list.push_back(temp_pos);
    }
    straight gme_straight;
    for(auto _: state) {
        gme_api_fit_line(point_list, gme_straight);
    }
}

BENCHMARK_REGISTER_F(Template1_Sample, gme_api_fit_line4)->Unit(benchmark::kMillisecond);

BENCHMARK_DEFINE_F(Template1_Sample, acis_api_fit_line5)(benchmark::State& state) {
    SPAposition_vector point_list;
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(-100, 100);  // 左闭右闭区间，取点坐标的大小范围
    e.seed(time(0));
    for(int i = 0; i < 100000; i++) {
        // 根据生成随机数生成点
        SPAposition temp_pos;
        temp_pos.set_x(u(e));
        temp_pos.set_y(u(e));
        temp_pos.set_z(u(e));
        point_list.push_back(temp_pos);
    }
    straight acis_straight;
    for(auto _: state) {
        api_fit_line(point_list, acis_straight);
    }
}

BENCHMARK_REGISTER_F(Template1_Sample, acis_api_fit_line5)->Unit(benchmark::kMillisecond);

BENCHMARK_DEFINE_F(Template1_Sample, gme_api_fit_line5)(benchmark::State& state) {
    SPAposition_vector point_list;
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(-100, 100);  // 左闭右闭区间，取点坐标的大小范围
    e.seed(time(0));
    for(int i = 0; i < 100000; i++) {
        // 根据生成随机数生成点
        SPAposition temp_pos;
        temp_pos.set_x(u(e));
        temp_pos.set_y(u(e));
        temp_pos.set_z(u(e));
        point_list.push_back(temp_pos);
    }
    straight gme_straight;
    for(auto _: state) {
        gme_api_fit_line(point_list, gme_straight);
    }
}

BENCHMARK_REGISTER_F(Template1_Sample, gme_api_fit_line5)->Unit(benchmark::kMillisecond);