#include <iostream>
#include <atomic>
#include <cassert>
#include <thread>
#include <vector>

class Foo{};

void foo(int a, int b)
{
    std::cout << a << ", " << b << std::endl;
}

int get_num()
{
    static int i = 0;
    return ++i;
}

namespace sequentialy_consistent
{
    std::atomic<bool> x, y;
    std::atomic<int> z;
    void write_x()
    {
        x.store(true, std::memory_order_seq_cst);
    }

    void write_y()
    {
        y.store(true, std::memory_order_seq_cst);
    }

    void read_x_then_y()
    {
        while(!x.load(std::memory_order_seq_cst));
        if (y.load(std::memory_order_seq_cst)) { z++; std::cout << "y load true" << std::endl; }
    }

    void read_y_then_x()
    {
        while(!y.load(std::memory_order_seq_cst));
        if (x.load(std::memory_order_seq_cst)) { z++; std::cout << "x load true" << std::endl; }
    }
}

namespace order_relaxed
{
    std::atomic<bool> x, y;
    std::atomic<int> z;
    
    void write_x_then_y()
    {
        x.store(true, std::memory_order_relaxed);
        y.store(true, std::memory_order_relaxed);
    }

    void read_y_then_x()
    {
        while(!y.load(std::memory_order_relaxed));
        if (x.load(std::memory_order_relaxed)) { z++; std::cout << "x load true" << std::endl; }
    }
}

namespace order_relaxed_complex
{
    std::atomic<int> x(0), y(0), z(0);
    std::atomic<int> go(false);
    const unsigned loop_count = 10;
    void write_x_then_y();
    struct read_values
    {
        int x,y,z;
    };
    
    read_values values1[loop_count];
    read_values values2[loop_count];
    read_values values3[loop_count];
    read_values values4[loop_count];
    read_values values5[loop_count];

    void increment(std::atomic<int>* var_to_inc, read_values* values)
    {
        while (!go)
        {
            std::this_thread::yield();
        }

        for(unsigned i = 0; i < loop_count; ++i)
        {
            values[i].x = x.load(std::memory_order_relaxed);
            values[i].y = y.load(std::memory_order_relaxed);
            values[i].z = z.load(std::memory_order_relaxed);
            var_to_inc->store(i+1, std::memory_order_relaxed);
            std::this_thread::yield();
        }
    }

    void read_vals(read_values* values)
    {
        while (!go)
        {
            std::this_thread::yield();
        }
        
        for (unsigned i = 0; i < loop_count; ++i)
        {
            values[i].x = x.load(std::memory_order_relaxed);
            values[i].y = y.load(std::memory_order_relaxed);
            values[i].z = z.load(std::memory_order_relaxed);
            std::this_thread::yield();
        }
    }

    void print(read_values* v)
    {
        for (unsigned i = 0; i < loop_count; ++i)
        {
            if(i)
                std::cout << ",";
            std::cout << "(" << v[i].x << "," << v[i].y << "," << v[i].z << ")";
        }
        std::cout << std::endl;
    }
}

namespace acquire_release_ordering
{
    std::atomic<int> data[5];
    std::atomic<bool> sync1(false), sync2(false);
    void thread_1()
    {
        data[0].store(42, std::memory_order_relaxed);
        data[1].store(97, std::memory_order_relaxed);
        data[2].store(17, std::memory_order_relaxed);
        data[3].store(-141, std::memory_order_relaxed);
        data[4].store(2003, std::memory_order_relaxed);
        sync1.store(true, std::memory_order_release);
    }

    void thread_2()
    {
        while (!sync1.load(std::memory_order_acquire));
        sync2.store(true, std::memory_order_release);        
    }

    void thread_3()
    {
        while(!sync2.load(std::memory_order_acquire));
        assert(data[0].load(std::memory_order_relaxed)==42);
        assert(data[1].load(std::memory_order_relaxed)==97);
        assert(data[2].load(std::memory_order_relaxed)==17);
        assert(data[3].load(std::memory_order_relaxed)==-141);
        assert(data[4].load(std::memory_order_relaxed)==2003);
    }
}

namespace release_sequence
{
    std::vector<int> queue_data;
    std::atomic<int> count;

    void process(int x)
    {
        std::cout << "processing: " << x << std::endl;
    }

    void populate_queue()
    {
        const unsigned number_of_items = 20;
        queue_data.clear();
        for(unsigned i = 0; i < number_of_items; ++i)
        {
            queue_data.push_back(i);
        }

        count.store(number_of_items, std::memory_order_release);
    }

    void consume_queue_items()
    {
        int iteration = 0;
        while (true)
        {
            int item_index;
            if((item_index = count.fetch_sub(1, std::memory_order_acquire)) <= 0)
            {
                continue;
            }
            process(queue_data[item_index - 1]);
            iteration++;
            if(iteration >= 9)
            {
                break;
            }
        }
        
    }
}

namespace fence
{
    std::atomic<bool> x, y;
    std::atomic<int> z;
    
    void write_x_then_y()
    {
        x.store(true, std::memory_order_relaxed);
        std::atomic_thread_fence(std::memory_order_release);
        y.store(true, std::memory_order_relaxed);
    }

    void read_y_then_x()
    {
        while(!y.load(std::memory_order_relaxed));
        std::atomic_thread_fence(std::memory_order_acquire);
        if(x.load(std::memory_order_relaxed)) ++z;
    }
}

int main()
{
    {
        std::atomic<bool> b;
        bool x = b.load(std::memory_order_acquire);
        std::cout << "x: " << x << std::endl;
        b.store(true);
        x = b.exchange(false, std::memory_order_acq_rel);
        std::cout << "x: " << x << std::endl;
        std::cout << "b: " << b.load() << std::endl;
        b.store(true);
        bool expected = false;
        while (!b.compare_exchange_weak(expected, false))
        {
            std::cout << "b.compare_exchange_weak: " << b.load() << " expected: " << expected << std::endl;
        }
        
        x = b.load();
        std::cout << "x: " << x << std::endl;
        std::cout << "expected: " << expected << std::endl;
        
        Foo some_array[5];
        std::atomic<Foo*> p(some_array);
        Foo* xFoo = p.fetch_add(2);
        assert(xFoo == some_array);
        assert(p.load() == &some_array[2]);

        xFoo = (p-=1);
        assert(xFoo == &some_array[1]);
        assert(p.load() == &some_array[1]);
    }

    foo(get_num(), get_num());

    {
        using namespace sequentialy_consistent;
        x = false;
        y = false;
        z = 0;
        std::thread a(write_x);
        std::thread b(write_y);
        std::thread c(read_x_then_y);
        std::thread d(read_y_then_x);
        a.join();
        b.join();
        c.join();
        d.join();
        assert(z.load() != 0);
        std::cout << "z: " << z << std::endl;
    }

    {
        using namespace order_relaxed;
        x = false;
        y = false;
        z = 0;
        std::thread b(read_y_then_x);
        std::thread a(write_x_then_y);
        b.join();
        a.join();
        // assert(z.load() != 0);
        std::cout << "z: " << z << std::endl;
    }

    {
        using namespace order_relaxed_complex;
        std::thread t1(increment,&x,values1);
        std::thread t2(increment,&y,values2);
        std::thread t3(increment,&z,values3);
        std::thread t4(read_vals,values4);
        std::thread t5(read_vals,values5);
        go=true;
        t5.join();
        t4.join();
        t3.join();
        t2.join();
        t1.join();
        print(values1);
        print(values2);
        print(values3);
        print(values4);
        print(values5);
    }

    {
        using namespace acquire_release_ordering;
        std::thread t1(thread_1);
        std::thread t2(thread_2);
        std::thread t3(thread_3);
        t1.join();
        t2.join();
        t3.join();
    }

    {
        using namespace release_sequence;
        std::thread a(populate_queue);
        std::thread b(consume_queue_items);
        std::thread c(consume_queue_items);
        a.join();
        b.join();
        c.join();
    }

    {
        using namespace fence;
        x = false;
        y = false;
        z = 0;
        std::thread a(write_x_then_y);
        std::thread b(read_y_then_x);
        a.join();
        b.join();
        assert(z.load() != 0);
        std::cout << "Fence z: " << std::endl;
    }
    
    return 0;
}