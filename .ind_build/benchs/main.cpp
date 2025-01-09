/*********************************************************************
 * @file    main.cpp
 * @brief
 * @details
 * @author  Shivelino
 * @date    2023.10.4
 * @version 0.2.0
 * @par Copyright(c): Concloud Software Corporation
 * @par todo:
 * @par history:
 *********************************************************************/
#include <benchmark/benchmark.h>

#include <fstream>

int main(int argc, char** argv) {
    char arg0_default[] = "benchmark";
    char* args_default = arg0_default;
    if (!argv) {
        argc = 1;
        argv = &args_default;
    }
    ::benchmark::Initialize(&argc, argv);
    if (::benchmark::ReportUnrecognizedArguments(argc, argv))
        return 1;
    if (std::string(BENCHMARK_OUTPUT) == "csv" || std::string(BENCHMARK_OUTPUT) == "CSV") {
        std::ofstream output_file("benchmark_results.csv");
        ::benchmark::ConsoleReporter reporter;
        reporter.SetOutputStream(&output_file);
        ::benchmark::RunSpecifiedBenchmarks(&reporter);
    } else if (std::string(BENCHMARK_OUTPUT) == "json" || std::string(BENCHMARK_OUTPUT) == "JSON") {
        std::ofstream output_file("benchmark_results.json");
        ::benchmark::ConsoleReporter reporter;
        reporter.SetOutputStream(&output_file);
        ::benchmark::RunSpecifiedBenchmarks(&reporter);
    } else {
        ::benchmark::RunSpecifiedBenchmarks();
    }
    ::benchmark::Shutdown();
    return 0;
}