/*********************************************************************
 * @file    gme_api_orient_wire_bench.cxx
 * @brief  gme_api_orient_wire接口的性能测试文件
 * @details  比较gme_api_orient_wire与api_orient_wire的性能差异
 * @author  charynnc
 * @date    2024.8.6
 *********************************************************************/
#include <benchmark/benchmark.h>

// ACIS
#include "acis/coverapi.hxx"
#include "acis/cstrapi.hxx"
#include "acis_utils.hpp"
#include "same_entity.hpp"  // same_entity所在头文件

class api_orient_wire_bench : public benchmark::Fixture {
    int level = 0;

  protected:
    void SetUp(benchmark::State& state) override { level = initialize_acis(); }

    void TearDown(benchmark::State& state) override { terminate_acis(level); }
};

BENCHMARK_DEFINE_F(api_orient_wire_bench, api_orient_wire)(benchmark::State& state) {
    BODY* body;
    BODY *body1, *body2;
    SPAposition p1(0, 0, 0), p2(1, 0, 0), p3(1, 1, 0), p4(2, 0, 0), p5(2, 1, 0);
    EDGE *e1, *e2, *e3, *e4;

    api_curve_line(p1, p2, e1);
    api_curve_line(p2, p3, e2);
    api_curve_line(p4, p5, e3);
    api_curve_line(p5, p3, e4);

    ENTITY* edges[4] = {e1, e2, e3, e4};
    ENTITY_LIST edges_list(4, edges);
    FILE* fp = nullptr;
    api_unite_edges(edges_list, body, fp);

    ENTITY_LIST ces;
    api_get_coedges(body, ces);
    COEDGE* ce = (COEDGE*)ces[0];
    for(auto _: state) {
        api_orient_wire(ce);
    }
}

BENCHMARK_REGISTER_F(api_orient_wire_bench, api_orient_wire)->Unit(benchmark::kMillisecond);

BENCHMARK_DEFINE_F(api_orient_wire_bench, gme_api_orient_wire)(benchmark::State& state) {
    BODY* body;
    BODY *body1, *body2;
    SPAposition p1(0, 0, 0), p2(1, 0, 0), p3(1, 1, 0), p4(2, 0, 0), p5(2, 1, 0);
    EDGE *e1, *e2, *e3, *e4;

    api_curve_line(p1, p2, e1);
    api_curve_line(p2, p3, e2);
    api_curve_line(p4, p5, e3);
    api_curve_line(p5, p3, e4);

    ENTITY* edges[4] = {e1, e2, e3, e4};
    ENTITY_LIST edges_list(4, edges);
    FILE* fp = nullptr;
    api_unite_edges(edges_list, body, fp);

    ENTITY_LIST ces;
    api_get_coedges(body, ces);
    COEDGE* ce = (COEDGE*)ces[0];
    for(auto _: state) {
        gme_api_orient_wire(ce);
    }
}

BENCHMARK_REGISTER_F(api_orient_wire_bench, gme_api_orient_wire)->Unit(benchmark::kMillisecond);
