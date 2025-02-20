#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <utility>
#include <map>

using namespace std::chrono_literals;

void updateWeather(std::map<std::string, int>& weather)
{
    while (true)
    {
        for(auto& [_, temp] : weather)
        {
            ++temp;
        }
        std::this_thread::sleep_for(2000ms);
    }
}

void showWeather(std::map<std::string, int>& weather)
{
    while (true)
    {
        std::string place;
        std::cout << "Please choose the place: \n";
        std::cin >> place;
        if(auto it = weather.find(place); it != weather.end())
        {
            std::cout << "The weather for " << place << " is " << weather[place] << std::endl;
        }
    }
}

int main()
{
    std::map<std::string, int> weather
    {
        {"City", 15},
        {"Town", 18},
        {"Village", 25}
    };
    std::thread t1(updateWeather, std::ref(weather));
    std::thread t2(showWeather, std::ref(weather));

    t1.join();
    t2.join();

    return 0;
}