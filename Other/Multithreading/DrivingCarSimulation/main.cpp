#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

std::mutex m;

void drivingCar(const std::string& name)
{
    std::unique_lock lock(m);
    std::cout << name << " is driving now" << std::endl;
    std::this_thread::sleep_for(2s);
    std::cout << name << " stopped driving" << std::endl;
    lock.unlock();
}

int main()
{
    std::thread t1(drivingCar, "Anna");
    std::thread t2(drivingCar, "Caro");

    t1.join();
    t2.join();
    return 0;
}