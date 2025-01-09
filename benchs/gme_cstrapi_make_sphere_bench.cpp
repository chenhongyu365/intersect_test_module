/*********************************************************************
 * @file    gme_cstrapi_make_sphere_bench.cxx
 * @brief    gme_api_make_sphere接口的性能测试文件
 * @details   比较gme_api_make_sphere与api_make_sphere的性能差异
 * @author  Dubopei
 * @date    2024.9.19
 *********************************************************************/
#include <benchmark/benchmark.h>

// ACIS
#include "acis/cstrapi.hxx"
#include "acis_utils.hpp"
#include "ctime"            // 用于生成随机数
#include "random"           // 用于生成随机数
#include "same_entity.hpp"  // same_entity所在头文件

class Constructors_Sample : public benchmark::Fixture {
    int level = 0;

  protected:
    void SetUp(benchmark::State& state) override { level = initialize_acis(); }

    void TearDown(benchmark::State& state) override { terminate_acis(level); }
};

BENCHMARK_DEFINE_F(Constructors_Sample, acis_api_make_sphere)(benchmark::State& state) {
    BODY* sph = nullptr;
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(-1e4, 1e20);  // 左闭右闭区间，取点坐标的大小范围
    e.seed(time(0));
    double radius = u(e);
    for(auto _: state) {
        api_make_sphere(radius, sph);
    }
}

BENCHMARK_REGISTER_F(Constructors_Sample, acis_api_make_sphere)->Unit(benchmark::kMillisecond);

BENCHMARK_DEFINE_F(Constructors_Sample, gme_cstrapi_make_sphere)(benchmark::State& state) {
    BODY* sph = nullptr;
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(-1e4, 1e20);  // 左闭右闭区间，取点坐标的大小范围
    e.seed(time(0));
    double radius = u(e);
    for(auto _: state) {
        gme_api_make_sphere(radius, sph);
    }
}

BENCHMARK_REGISTER_F(Constructors_Sample, gme_cstrapi_make_sphere)->Unit(benchmark::kMillisecond);