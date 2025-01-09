/*********************************************************************
 * @file    random.hpp
 * @brief   数据随机生成
 * @details
 * @author  duanshuiliu123@李冰
 * @date    2024.7.8
 *********************************************************************/
#pragma once

#include <algorithm>
#include <cfloat>
#include <random>

class SPAposition;
class SPAvector;

template <typename NumericType> using uniform_distribution = typename std::conditional<std::is_integral<NumericType>::value, std::uniform_int_distribution<NumericType>, std::uniform_real_distribution<NumericType>>::type;

template <typename RandomEngine = std::default_random_engine> class RandomNumberGenerator {
  private:
    RandomEngine m_engine;

  public:
    template <typename... Params> explicit RandomNumberGenerator(Params&&... params): m_engine(std::forward<Params>(params)...) {}

    template <typename... Params> void seed(Params&&... seeding) { m_engine.seed(std::forward<Params>(seeding)...); }

    template <typename DistributionFunc, typename... Params> typename DistributionFunc::result_type distribution(Params&&... params) {
        DistributionFunc dist(std::forward<Params>(params)...);
        return dist(m_engine);
    }

    template <typename NumericType> NumericType uniformDistribution(NumericType lower, NumericType upper) {
        if(lower == upper) {
            return lower;
        }
        return distribution<uniform_distribution<NumericType>>(lower, upper);
    }

    double uniformUnit() { return uniformDistribution(0.f, std::nextafter(1.f, FLT_MAX)); }

    double uniformSymmetry() { return uniformDistribution(-1.f, std::nextafter(1.f, FLT_MAX)); }

    double randomModelDouble() { return uniformDistribution<double>(-1e4, 1e4); }

    SPAposition randomPoint() {
        SPAposition result;
        result.set_x(randomModelDouble());
        result.set_y(randomModelDouble());
        result.set_z(randomModelDouble());
        return result;
    }

    SPAvector randomVector() {
        SPAvector result;
        result.set_x(randomModelDouble());
        result.set_y(randomModelDouble());
        result.set_z(randomModelDouble());
        return result;
    }

    bool bernoulliDistribution(double probability) { return distribution<std::bernoulli_distribution>(probability); }

    double normalDistribution(double mean, double stddev) { return distribution<std::normal_distribution<double>>(mean, stddev); }

    template <typename DistributionFunc, typename Range, typename... Params> void generator(Range&& range, Params&&... params) {
        // using ResultType = typename DistributionFunc::result_type;

        DistributionFunc dist(std::forward<Params>(params)...);
        return std::generate(std::begin(range), std::end(range), [&] { return dist(m_engine); });
    }
};

template <typename DistributionFunc, typename RandomEngine = std::default_random_engine, typename SeedType = std::seed_seq> class DistRandomNumberGenerator {
    using ResultType = typename DistributionFunc::result_type;

  private:
    RandomEngine m_engine;
    DistributionFunc* m_dist = nullptr;

  public:
    template <typename... Params> explicit DistRandomNumberGenerator(SeedType&& seeding, Params&&... /*params*/): m_engine(seeding) {}

    ~DistRandomNumberGenerator() {}

    template <typename... Params> void seed(Params&&... params) { m_engine.seed(std::forward<Params>(params)...); }

    ResultType next() { return (*m_dist)(m_engine); }
};

using DefaultRNG = RandomNumberGenerator<std::mt19937>;
