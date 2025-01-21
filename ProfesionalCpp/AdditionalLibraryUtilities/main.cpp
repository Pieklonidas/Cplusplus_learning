#include <iostream>
#include <ratio>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <cmath>
#include <random>
#include <functional>
#include <algorithm>
#include <vector>
#include <map>
#include <optional>


void rationExample()
{
    using r1 = std::ratio<1,60>;
    std::cout << "1) " << r1::num << "/" << r1::den << std::endl;

    std::intmax_t num = r1::num;
    std::intmax_t den = r1::den;
    std::cout << "2) " << num << "/" << den << std::endl;

    const std::intmax_t n = 1;
    const std::intmax_t d = 30;
    using r2 = std::ratio<n, d>;
    std::cout << "3) " << r2::num << "/" << r2::den << std::endl;

    using result = std::ratio_add<r1, r2>::type;
    std::cout << "4) " << result::num << "/" << result::den << std::endl;

    using boolRes = std::ratio_less<r2, r1>;
    std::cout << "5) " << std::boolalpha << boolRes::value << std::endl;

}

void durationExample()
{
    std::chrono::duration<long, std::ratio<60>> d1(123);
    std::cout << d1.count() << std::endl;

    std::chrono::duration<double> d2;
    d2 = d2.max();
    std::cout << d2.count() << std::endl;
    
    std::chrono::duration<long, std::ratio<60>> d3(10);
    std::chrono::duration<long, std::ratio<1>> d4(14);

    if(d3 > d4)
    {
        std::cout << "d3 > d4" << std::endl;
    }
    else
    {
        std::cout << "d4 >= d3" << std::endl;
    }

    ++d4;

    d4 *= 2;

    std::chrono::duration<double, std::ratio<60>> d5 = d3 + d4;
    std::chrono::duration<long, std::ratio<1>> d6 = d3 + d4;

    std::cout << d3.count() << " minutes + " << d4.count() << " seconds = "
              << d5.count() << " minutes or "
              << d6.count() << " seconds" << std::endl;
    
    std::chrono::duration<long> d7(30);
    std::chrono::duration<double, std::ratio<60>> d8(d7);
    std::cout << d7.count() << " seconds = " << d8.count() << " minutes" << std::endl;

    auto t = std::chrono::hours(1) + std::chrono::minutes(23) + std::chrono::seconds(45);
    std::cout << std::chrono::seconds(t).count() << " seconds" << std::endl;
}

void clockExample()
{
    std::chrono::system_clock::time_point tpoint = std::chrono::system_clock::now();
    time_t tt = std::chrono::system_clock::to_time_t(tpoint);
    tm* t = std::localtime(&tt);
    std::cout << std::put_time(t, "%H:%M:%S") << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    double d = 0;
    for(int i = 0; i < 1000000; ++i)
    {
        d += std::sqrt(std::sin(i)*std::cos(i));
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto diff = end - start;
    std::cout << std::chrono::duration<double, std::milli>(diff).count() << "ms" << std::endl;

    std::chrono::time_point<std::chrono::steady_clock> tp1;
    tp1 += std::chrono::minutes(10);
    auto  d1 = tp1.time_since_epoch();
    std::chrono::duration<double> d2(d1);
    std::cout << d2.count() << " seconds" << std::endl;

    using namespace std::literals::chrono_literals;
    std::chrono::time_point<std::chrono::steady_clock, std::chrono::seconds> tpSeconds(42s);
    std::chrono::time_point<std::chrono::steady_clock, std::chrono::milliseconds> tpMilliseconds(tpSeconds);
    std::cout << tpMilliseconds.time_since_epoch().count() << " ms" << std::endl;
}

void randomNumberEnginesExample()
{
    std::random_device rnd;
    std::cout << "Entropy: " << rnd.entropy() << std::endl;
    std::cout << "Min value: " << rnd.min()
              << ", Max value: " << rnd.max() << std::endl;
    std::cout << "Random number: " << rnd() << std::endl;

    const unsigned int kStart = 1;
    const unsigned int kEnd = 99;

    std::random_device seeder;
    const auto seed = seeder.entropy() ? seeder() : std::time(nullptr);
    std::mt19937 eng(static_cast<std::mt19937::result_type>(seed));
    std::uniform_int_distribution<int> dist(kStart, kEnd);
    std::cout << dist(eng) << std::endl;

    auto gen = std::bind(dist, eng);

    std::vector<int> vec(10);
    std::generate(begin(vec), end(vec), gen);
    for (auto i : vec) { std::cout << i << "  "; }
    std::cout << std::endl;

    const unsigned int kIterations = 1'000'000;

    std::map<int, int> m;
    for(unsigned int i = 0; i < kIterations; ++i)
    {
        int rnd = gen();
        ++(m[rnd]);
    }

    for (unsigned int i = kStart; i <= kEnd; ++i)
    {
        std::cout << i << ": " << m[i] << std::endl;
    }
}

std::optional<int> getData(bool giveIt)
{
    if(giveIt)
    {
        return 42;
    }
    return std::nullopt;
}

void optionalExample()
{
    auto data1 = getData(true);
    auto data2 = getData(false);

    std::cout << "data1.has_value = " << data1.has_value() << std::endl;
    if(data2)
    {
        std::cout << "data2 has a value." << std::endl;
    }

    std::cout << "data1.value = " << data1.value() << std::endl;
    std::cout << "data1.value = " << *data1 << std::endl;

    std::cout << "data2.value = " << data2.value_or(0) << std::endl;
}

int main()
{   
    // rationExample();
    // durationExample();
    // clockExample();
    // randomNumberEnginesExample();
    optionalExample();
    return 0;
}