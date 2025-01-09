/*********************************************************************
 * @file        gme_cstrapi_3_make_frustum_bench.cpp
 * @brief       gme_api_make_frustum接口的性能测试文件
 * @details     比较gme_api_make_frustum与api_make_frustum的性能差异
 * @author      刘宝星
 * @date        2024.10.10
 *********************************************************************/
#include <benchmark/benchmark.h>

#include "acis/cstrapi.hxx"
#include "acis_utils.hpp"
#include "ctime"            // 用于生成随机数
#include "random"           // 用于生成随机数
#include "same_entity.hpp"  // same_entity所在头文件

class Constructors_Make_frustum : public benchmark::Fixture {
    int level = 0;

  protected:
    void SetUp(benchmark::State& state) override { level = initialize_acis(); }

    void TearDown(benchmark::State& state) override { terminate_acis(level); }
};

BENCHMARK_DEFINE_F(Constructors_Make_frustum, acis_api_make_frustum)(benchmark::State& state) {
    BODY* en = nullptr;
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(-1e4, 1e20);  // 左闭右闭区间，取点坐标的大小范围
    e.seed(time(0));
    double height = u(e);
    double radius1 = u(e);
    double radius2 = u(e);
    double top = u(e);
    for(auto _: state) {
        api_make_frustum(height, radius1, radius2, top, en);
    }
}

BENCHMARK_REGISTER_F(Constructors_Make_frustum, acis_api_make_frustum)->Unit(benchmark::kMillisecond);

BENCHMARK_DEFINE_F(Constructors_Make_frustum, gme_cstrapi_3_make_frustum)(benchmark::State& state) {
    BODY* en = nullptr;
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(-1e4, 1e20);  // 左闭右闭区间，取点坐标的大小范围
    e.seed(time(0));
    double height = u(e);
    double radius1 = u(e);
    double radius2 = u(e);
    double top = u(e);
    for(auto _: state) {
        gme_3_api_make_frustum(height, radius1, radius2, top, en);
    }
}

BENCHMARK_REGISTER_F(Constructors_Make_frustum, gme_cstrapi_3_make_frustum)->Unit(benchmark::kMillisecond);