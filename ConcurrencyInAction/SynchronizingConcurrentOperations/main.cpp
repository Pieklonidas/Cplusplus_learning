#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <queue>
#include <memory>
#include <future>
#include <utility>
#include <deque>
#include <list>
#include <algorithm>
#include <latch>
#include <barrier>

namespace Task1
{
std::mutex mut;
std::queue<int> data_queue;
std::condition_variable data_cond;
} // namespace Task1

void data_preparation_thread()
{
    int i = 1;
    while (i <= 10)
    {
        const int data = i++;
        {
            std::lock_guard lk(Task1::mut);
            std::cout << "pushing data to the queue: " << data << std::endl; 
            Task1::data_queue.push(data);
        }
        Task1::data_cond.notify_one();
    }
}

void process(int data)
{
    std::cout << "current data is: " << data << std::endl;
}

void data_processing_thread()
{
    while (true)
    {
        std::unique_lock lk(Task1::mut);
        Task1::data_cond.wait(
            lk, []{ return !Task1::data_queue.empty(); }
        );
        int data = Task1::data_queue.front();
        Task1::data_queue.pop();
        lk.unlock();
        process(data);
        if(data == 10)
            break;
    }
    
}

template <typename T>
class threadsafe_queue
{
private:
    mutable std::mutex mut;
    std::queue<T> data_queue;
    std::condition_variable data_cond;
public:
    threadsafe_queue() {}
    
    threadsafe_queue(const threadsafe_queue& other)
    {
        std::lock_guard lk(other.mut);
        data_queue = other.data_queue;
    }
    
    void push(T new_value)
    {
        std::lock_guard lk(mut);
        data_queue.push(new_value);
        data_cond.notify_one();
    }
    
    void wait_and_pop(T& value)
    {
        std::unique_lock lk(mut);
        data_cond.wait(lk, [this]{ return !data_queue.empty(); });
        value = data_queue.front();
        data_queue.pop();
    }
    
    std::shared_ptr<T> wait_and_pop()
    {
        std::unique_lock lk(mut);
        data_cond.wait(lk, [this]{ return !data_queue.empty(); });
        std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
        data_queue.pop();
        return res;
    }

    bool try_pop(T& value)
    {
        std::lock_guard lk(mut);
        if(data_queue.empty()) return false;

        value = data_queue.front();
        data_queue.pop;
        return true;
    }

    std::shared_ptr<T> try_pop()
    {
        std::lock_guard lk(mut);
        if(data_queue.empty()) return std::shared_ptr<T>();

        std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
        data_queue.pop();
        return res;
    }

    bool empty() const
    {
        std::lock_guard lk(mut);
        return data_queue.empty();
    }
};

int find_the_answer_to_ltuae()
{
    std::cout << "Looking for the answer..." << std::endl;
    return 42;
}

std::mutex m;
std::deque<std::packaged_task<void()>> tasks;
void get_and_process_gui_message();

void gui_thread()
{
    int i = 0;
    while(i++ <= 10)
    {
        get_and_process_gui_message();
        std::packaged_task<void()> task;
        {
            std::lock_guard lk(m);
            if(tasks.empty()) continue;

            task = std::move(tasks.front());
            tasks.pop_front();
        }
        task();
    }
}

template<typename Func>
std::future<void> post_task_for_gui_thread(Func f)
{
    std::packaged_task<void()> task(f);
    std::future<void> res = task.get_future();
    std::lock_guard lk(m);
    tasks.push_back(std::move(task));
    return res;
}

void get_and_process_gui_message()
{
    auto fut = post_task_for_gui_thread([]{ std::cout << "posting task for gui" << std::endl; });
}

template<typename T>
std::list<T> parralel_quick_sort(std::list<T> input)
{
    if(input.empty())
    {
        return input;
    }
    std::list<T> result;
    result.splice(result.begin(), input, input.begin());
    const T& pivot = *result.begin();
    auto divide_point = std::partition(input.begin(), input.end(),
        [&](const T& t){ return t < pivot; });
    std::list<T> lower_part;
    lower_part.splice(lower_part.end(), input, input.begin(), divide_point);
    std::future<std::list<T>> new_lower(
        std::async(&parralel_quick_sort<T>, std::move(lower_part)));
    auto new_higher(parralel_quick_sort(std::move(input)));
    result.splice(result.end(), new_higher);
    result.splice(result.begin(), new_lower.get());
    return result;
}

void foo()
{
    const unsigned thread_count = 5;
    std::latch done(thread_count);
    int data[thread_count];
    std::vector<std::future<void>> threads;
    for(unsigned i = 0; i < thread_count; ++i)
    {
        threads.push_back(std::async(std::launch::async, [&,i]{
            data[i] = i;
            done.count_down();
            std::cout << "Currently at task: " << i << std::endl;
        }));
    }
    done.wait();
    for(unsigned i = 0; i < thread_count; ++i)
    {
        std::cout << "Data: " << i << std::endl;
    }
}

int main()
{
    std::thread t1(data_preparation_thread);
    std::thread t2(data_processing_thread);
    t1.join();
    t2.join();

    std::future<int> the_answer = std::async(find_the_answer_to_ltuae);
    std::cout << "Don't need the answer yet" << std::endl;
    std::cout << "The answer is " << the_answer.get() << std::endl;

    auto fut = post_task_for_gui_thread([]{ std::cout << "Main task processing" << std::endl; });
    std::thread gui_bg_thread(gui_thread);
    fut.wait();
    gui_bg_thread.join();

    std::list l = {9, 2, 3, 1, 0, 4, 6, 5, 7, 8};

    std::list res = parralel_quick_sort(l);
    for(auto&& r : res)
    {
        std::cout << r << " ";
    }
    std::cout << std::endl;

    foo();

    return 0;
}