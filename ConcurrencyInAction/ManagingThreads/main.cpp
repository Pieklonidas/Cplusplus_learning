#include <iostream>
#include <thread>
#include <vector>
#include <stdexcept>

void do_something(int i)
{
    std::cout << i << std::endl;
}

void do_something_in_current_thread()
{
    std::cout << "doing something in current thread\n";
}

struct func
{
    int& i;
    func(int& i_) : i(i_) {}
    void operator()()
    {
        for (unsigned j = 0; j < 10; ++j)
        {
            do_something(i);
        }
    }
};

class thread_guard
{
public:
    explicit thread_guard(std::thread& t_) : t(t_) {}
    ~thread_guard()
    {
        if(t.joinable())
        {
            t.join();
        }
    }
    thread_guard(const thread_guard&)=delete;
    thread_guard& operator=(const thread_guard&) = delete;
private:
    std::thread& t;
};

void f()
{
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread t(my_func);
    thread_guard g(t);
    do_something_in_current_thread();
}

void print_string(std::string& str)
{
    str += " World!";
    std::cout << str << std::endl;
}

class scoped_thread
{
public:
    explicit scoped_thread(std::thread t_) :
        t(std::move(t_))
    {
        if(!t.joinable())
        {
            throw std::logic_error("No thread");
        }
    }
    ~scoped_thread()
    {
        t.join();
    }
    scoped_thread(const scoped_thread&) = delete;
    scoped_thread& operator=(const scoped_thread&) = delete;
private:
    std::thread t;
};

void f2()
{
    int some_local_state = 0;
    scoped_thread t{std::thread(func(some_local_state))};
    do_something_in_current_thread();
}

void do_work(int i)
{
    std::cout << "Doing work: " << i << std::endl;
}

int main()
{
    f();
    std::string hello = "Hello";
    std::thread t(print_string, std::ref(hello));
    thread_guard g(t);
    f2();
    std::vector<std::thread> threads;
    for(unsigned i = 0; i < 20; ++i)
    {
        threads.emplace_back(do_work);
    }

    for (auto& entry : threads)
    {
        entry.join();
    }
    return 0;
}