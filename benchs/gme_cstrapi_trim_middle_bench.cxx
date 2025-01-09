/*********************************************************************
 * @file    gme_cstrapi_trim_middle_bench.cxx
 * @brief
 * @details
 * @author  linchforever
 * @date    2024.8.10
 *********************************************************************/
#include <benchmark/benchmark.h>

// GME
// #include "template_simple_api.hxx"

// ACIS
#include "acis/cstrapi.hxx"
#include "acis/entwray.hxx"
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

BENCHMARK_DEFINE_F(Template1_Sample, acis_api_trim_middle)(benchmark::State& state) {
    EDGE* crv_edge = nullptr;
    EDGE* acis_edge = nullptr;
    EDGE* gme_edge = nullptr;
    EDGE* trimr1_edge = nullptr;
    EDGE* trimr2_edge = nullptr;
    api_curve_bezier(SPAposition(-9.0, 2.0, 0.0), SPAposition(0.0, 3.0, 0.0), SPAposition(3.0, 1.0, 0.0), SPAposition(9.0, 2.0, 0.0), crv_edge);
    api_curve_bezier(SPAposition(6.0, 6.0, 0.0), SPAposition(4.0, 3.0, 0.0), SPAposition(6.0, -2.0, 0.0), SPAposition(3.0, -5.0, 0.0), trimr1_edge);
    api_curve_bezier(SPAposition(-4.0, 4.0, 0.0), SPAposition(-2.0, -4.0, 0.0), SPAposition(2.0, 9.0, 0.0), SPAposition(5.0, -1.0, 0.0), trimr2_edge);
    // 点坐标
    SPAposition_vector randpoint;
    std::vector<SPAunit_vector> randunit_vector;
    std::default_random_engine e;
    std::uniform_real_distribution<double> x_p(-10.5, 10.5);  // 点x轴区间
    std::uniform_real_distribution<double> y_p(-10.5, 10.5);  // 点y轴区间
    std::uniform_real_distribution<double> z_p(-5, 5);        // 点z轴区间
    std::uniform_real_distribution<double> x_v(-1, 1);        // 向量x轴区间
    std::uniform_real_distribution<double> y_v(-1, 1);        // 向量y轴区间
    std::uniform_real_distribution<double> z_v(-1, 1);        // 向量z轴区间
    e.seed(time(0));
    for(int i = 0; i < 3; i++) {
        SPAposition tmp_pos;
        tmp_pos.set_x(x_p(e));
        tmp_pos.set_y(y_p(e));
        tmp_pos.set_z(z_p(e));
        randpoint.push_back(tmp_pos);
        SPAunit_vector tmp_vec;
        tmp_vec.set_x(x_v(e));
        tmp_vec.set_y(y_v(e));
        tmp_vec.set_z(z_v(e));
        randunit_vector.push_back(tmp_vec);
    }
    // pick_ray的起始点
    SPAposition p1 = randpoint[0];
    SPAposition p2 = randpoint[1];
    SPAposition p3 = randpoint[2];
    // pick_ray的方向
    SPAunit_vector v1 = randunit_vector[0];
    SPAunit_vector v2 = randunit_vector[1];
    SPAunit_vector v3 = randunit_vector[2];
    // entity_with_ray
    entity_with_ray acis_crv = entity_with_ray(crv_edge, p1, v1);
    entity_with_ray e1 = entity_with_ray(trimr1_edge, p2, v2);
    entity_with_ray* trimr1 = &e1;
    entity_with_ray e2 = entity_with_ray(trimr2_edge, p3, v3);
    entity_with_ray* trimr2 = &e2;
    for(auto _: state) {
        api_trim_middle(acis_crv, NULL, trimr1, NULL, trimr2, acis_edge);
    }
}

BENCHMARK_REGISTER_F(Template1_Sample, acis_api_trim_middle)->Unit(benchmark::kMillisecond);

BENCHMARK_DEFINE_F(Template1_Sample, gme_api_trim_middle)(benchmark::State& state) {
    EDGE* crv_edge = nullptr;
    EDGE* acis_edge = nullptr;
    EDGE* gme_edge = nullptr;
    EDGE* trimr1_edge = nullptr;
    EDGE* trimr2_edge = nullptr;
    api_curve_bezier(SPAposition(-9.0, 2.0, 0.0), SPAposition(0.0, 3.0, 0.0), SPAposition(3.0, 1.0, 0.0), SPAposition(9.0, 2.0, 0.0), crv_edge);
    api_curve_bezier(SPAposition(6.0, 6.0, 0.0), SPAposition(4.0, 3.0, 0.0), SPAposition(6.0, -2.0, 0.0), SPAposition(3.0, -5.0, 0.0), trimr1_edge);
    api_curve_bezier(SPAposition(-4.0, 4.0, 0.0), SPAposition(-2.0, -4.0, 0.0), SPAposition(2.0, 9.0, 0.0), SPAposition(5.0, -1.0, 0.0), trimr2_edge);
    // 点坐标
    SPAposition_vector randpoint;
    std::vector<SPAunit_vector> randunit_vector;
    std::default_random_engine e;
    std::uniform_real_distribution<double> x_p(-10.5, 10.5);  // 点x轴区间
    std::uniform_real_distribution<double> y_p(-10.5, 10.5);  // 点y轴区间
    std::uniform_real_distribution<double> z_p(-5, 5);        // 点z轴区间
    std::uniform_real_distribution<double> x_v(-1, 1);        // 向量x轴区间
    std::uniform_real_distribution<double> y_v(-1, 1);        // 向量y轴区间
    std::uniform_real_distribution<double> z_v(-1, 1);        // 向量z轴区间
    e.seed(time(0));
    for(int i = 0; i < 3; i++) {
        SPAposition tmp_pos;
        tmp_pos.set_x(x_p(e));
        tmp_pos.set_y(y_p(e));
        tmp_pos.set_z(z_p(e));
        randpoint.push_back(tmp_pos);
        SPAunit_vector tmp_vec;
        tmp_vec.set_x(x_v(e));
        tmp_vec.set_y(y_v(e));
        tmp_vec.set_z(z_v(e));
        randunit_vector.push_back(tmp_vec);
    }
    // pick_ray的起始点
    SPAposition p1 = randpoint[0];
    SPAposition p2 = randpoint[1];
    SPAposition p3 = randpoint[2];
    // pick_ray的方向
    SPAunit_vector v1 = randunit_vector[0];
    SPAunit_vector v2 = randunit_vector[1];
    SPAunit_vector v3 = randunit_vector[2];
    // entity_with_ray
    entity_with_ray gme_crv = entity_with_ray(crv_edge, p1, v1);
    entity_with_ray e1 = entity_with_ray(trimr1_edge, p2, v2);
    entity_with_ray* trimr1 = &e1;
    entity_with_ray e2 = entity_with_ray(trimr2_edge, p3, v3);
    entity_with_ray* trimr2 = &e2;
    for(auto _: state) {
        gme_api_trim_middle(gme_crv, NULL, trimr1, NULL, trimr2, gme_edge);
    }
}

BENCHMARK_REGISTER_F(Template1_Sample, gme_api_trim_middle)->Unit(benchmark::kMillisecond);
