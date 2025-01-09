/*********************************************************************
 * @file    gme_split_edge_at_disc_bench.cxx
 * @brief
 * @details
 * @author  mshct
 * @date    2024.7.24
 *********************************************************************/
#include <benchmark/benchmark.h>

#include <filesystem>
#include <fstream>
#include <iostream>

// ACIS
#include "access.hpp"
#include "acis/cstrapi.hxx"
#include "acis_utils.hpp"
#include "same_entity.hpp"  // same_entity所在头文件

class Split_Edge_at_Disc_Sample : public benchmark::Fixture {
    int level = 0;

  protected:
    void SetUp(benchmark::State& state) override { level = initialize_acis(); }

    void TearDown(benchmark::State& state) override { terminate_acis(level); }
};

BENCHMARK_DEFINE_F(Split_Edge_at_Disc_Sample, acis_api_split_edge_at_disc)(benchmark::State& state) {
    using namespace std::filesystem;
    ENTITY* temp_entity = nullptr;
    ENTITY_LIST list;
    path test_path = current_path();
    test_path = test_path.parent_path().parent_path().parent_path() / "tests" / "split_edge_at_disc" / "edgeof4_order2.sat";
    acis_api_restore_entity(test_path.string().c_str(), temp_entity);
    for(auto _: state) {
        api_split_edge_at_disc(((BODY*)temp_entity)->lump()->shell()->wire()->coedge()->edge(), list, 2);
    }
}

BENCHMARK_REGISTER_F(Split_Edge_at_Disc_Sample, acis_api_split_edge_at_disc)->Unit(benchmark::kMillisecond);

BENCHMARK_DEFINE_F(Split_Edge_at_Disc_Sample, gme_api_split_edge_at_disc0)(benchmark::State& state) {
    using namespace std::filesystem;
    ENTITY* temp_entity = nullptr;
    ENTITY_LIST list;
    path test_path = current_path();
    test_path = test_path.parent_path().parent_path().parent_path() / "tests" / "split_edge_at_disc" / "edgeof4_order2.sat";
    acis_api_restore_entity(test_path.string().c_str(), temp_entity);
    for(auto _: state) {
        gme_api_split_edge_at_disc(((BODY*)temp_entity)->lump()->shell()->wire()->coedge()->edge(), list, 2);
    }
}

BENCHMARK_REGISTER_F(Split_Edge_at_Disc_Sample, gme_api_split_edge_at_disc0)->Unit(benchmark::kMillisecond);
