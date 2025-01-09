/*********************************************************************
 * @file      gme_cstrapi_1_make_sphere_bench.cxx
 * @brief     gme_1_api_make_sphere接口的性能测试文件
 * @details   比较gme_1_api_make_sphere与api_make_sphere的性能差异
 * @author    izhaoming
 * @date      2024.9.29
 *********************************************************************/
#include <benchmark/benchmark.h>

// ACIS
#include "acis/cstrapi.hxx"
#include "acis_utils.hpp"
#include "ctime"            // 用于生成随机数
#include "random"           // 用于生成随机数
#include "same_entity.hpp"  // same_entity所在头文件

class Gme_1_Api_Make_Sphere_Sample : public benchmark::Fixture {
    int level = 0;

  protected:
    // 初始化ACIS环境
    void SetUp(benchmark::State& state) override { level = initialize_acis(); }

    // 清理ACIS环境
    void TearDown(benchmark::State& state) override { terminate_acis(level); }
};

// 测试 api_make_sphere 的性能
BENCHMARK_DEFINE_F(Gme_1_Api_Make_Sphere_Sample, acis_api_make_sphere)(benchmark::State& state) {
    BODY* sph = nullptr;
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(0.1, 1e5);  // 左闭右闭区间，随机生成半径
    e.seed(time(0));                                     // 使用当前时间作为随机数种子
    double radius = u(e);                                // 生成随机半径
    for(auto _: state) {
        api_make_sphere(radius, sph);  // 调用 API 生成球体
    }
}

// 注册基准测试，并以毫秒为单位记录时间
BENCHMARK_REGISTER_F(Gme_1_Api_Make_Sphere_Sample, acis_api_make_sphere)->Unit(benchmark::kMillisecond);

// 测试 gme_1_api_make_sphere 的性能
BENCHMARK_DEFINE_F(Gme_1_Api_Make_Sphere_Sample, gme_cstrapi_1_make_sphere)(benchmark::State& state) {
    BODY* sph = nullptr;
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(0.1, 1e5);  // 左闭右闭区间，随机生成半径
    e.seed(time(0));                                     // 使用当前时间作为随机数种子
    double radius = u(e);                                // 生成随机半径
    for(auto _: state) {
        gme_1_api_make_sphere(radius, sph);  // 调用 API 生成球体
    }
}

// 注册基准测试，并以毫秒为单位记录时间
BENCHMARK_REGISTER_F(Gme_1_Api_Make_Sphere_Sample, gme_cstrapi_1_make_sphere)->Unit(benchmark::kMillisecond);
