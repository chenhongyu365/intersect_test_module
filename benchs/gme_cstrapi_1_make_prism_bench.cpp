/*********************************************************************
 * @file    gme_cstrapi_1_make_prism_bench.cpp
 * @brief    gme_1_api_make_sphere接口的性能测试文件
 * @details   比较gme_1_api_make_sphere与api_make_prism的性能差异
 * @author  THEYIG
 * @date    2024.9.25
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
// 定义棱柱构造基准测试
BENCHMARK_DEFINE_F(Constructors_Sample, gme_1_api_make_prism)(benchmark::State& state) {
    BODY* prism_body = nullptr;
    std::default_random_engine generator(time(0));                   // 随机数生成器
    std::uniform_real_distribution<double> height_dist(1.0, 100.0);  // 高度分布
    std::uniform_real_distribution<double> radius_dist(1.0, 50.0);   // 半径分布
    std::uniform_int_distribution<int> sides_dist(3, 10);            // 边数分布，最少3边，最多10边

    // 随机生成棱柱的参数
    double height = height_dist(generator);
    double radius1 = radius_dist(generator);
    double radius2 = radius_dist(generator);
    int nsides = sides_dist(generator);

    for(auto _: state) {
        gme_1_api_make_prism(height, radius1, radius2, nsides, prism_body);
    }
}

// 注册基准测试
BENCHMARK_REGISTER_F(Constructors_Sample, gme_1_api_make_prism)->Unit(benchmark::kMillisecond);
