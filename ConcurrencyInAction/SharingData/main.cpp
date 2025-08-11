#include <iostream>
#include <thread>
#include <mutex>
#include <list>
#include <algorithm>
#include <exception>
#include <memory>
#include <stack>
#include <vector>
#include <shared_mutex>
#include <map>
#include <string>

std::mutex some_mutex;
void add_to_list(std::list<int>& some_list, int new_value)
{
    std::lock_guard<std::mutex> guard(some_mutex);
    some_list.push_back(new_value);
}

void list_contains(const std::list<int>& some_list, int value_to_find)
{
    std::lock_guard guard(some_mutex);
    if (std::find(begin(some_list), end(some_list), value_to_find) != end(some_list))
    {
        std::cout << "Found " << value_to_find << std::endl;
    }
    else
    {
        std::cout << "Couldn't find " << value_to_find << std::endl;
    }
}

struct empty_stack : std::exception
{
    const char* what() const throw()
    {
        return "The stack is empty";
    }
};

template<typename T>
class threadsafe_stack
{
public:
    threadsafe_stack(){}
    threadsafe_stack(const threadsafe_stack& other)
    {
        std::lock_guard lock(other.m);
        data = other.data;
    }
    threadsafe_stack& operator=(const threadsafe_stack&) = delete;
    void push(T new_value)
    {
        std::lock_guard lock(m);
        data.push(std::move(new_value));
    }
    std::shared_ptr<T> pop()
    {
        std::lock_guard lock(m);
        if(data.empty()) throw empty_stack();
        const std::shared_ptr<T> res(std::make_shared<T>(data.top()));
        data.pop();
        return res;
    }
    void pop(T& value)
    {
        std::lock_guard lock(m);
        if(data.empty()) throw empty_stack();
        value = data.top();
        data.pop();
    }
    bool empty() const
    {
        std::lock_guard lock(m);
        return data.empty();
    }
private:
    std::stack<T> data;
    mutable std::mutex m;
};

template <typename T>
void add_to_stack(threadsafe_stack<T>& stack, T value)
{
    stack.push(value);
}

template <typename T>
void pop_from_stack(threadsafe_stack<T>& stack, T& value)
{
    try
    {
        stack.pop(value);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

template <typename T>
std::shared_ptr<T> pop_from_stack_ptr(threadsafe_stack<T>& stack)
{
    try
    {
        return stack.pop();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return std::make_shared<T>();
}

class X
{
public:
    X(int sd) : some_detail(sd) {}
    friend void swap(X& lhs, X& rhs)
    {
        if(&lhs == &rhs) return;

        // std::lock(lhs.m, rhs.m);
        // std::lock_guard lock_a(lhs.m, std::adopt_lock);
        // std::lock_guard lock_b(rhs.m, std::adopt_lock);
        std::scoped_lock guard(lhs.m, rhs.m);
        std::swap(lhs.some_detail, rhs.some_detail);
    }
private:
    int some_detail;
    std::mutex m;
};

class hierarchical_mutex
{
public:
    explicit hierarchical_mutex(unsigned long value)
        : hierarchy_value(value), previous_hierarchy_value(0)
    {}
    void lock()
    {
        check_for_hierarchy_violation();
        internal_mutex.lock();
        update_hierarchy_value();
    }

    void unlock()
    {
        if(this_thread_hierarchy_value != hierarchy_value)
            throw std::logic_error("mutex hierarchy violated");
        this_thread_hierarchy_value = previous_hierarchy_value;
        internal_mutex.unlock();
    }
    bool try_lock()
    {
        check_for_hierarchy_violation();
        if(!internal_mutex.try_lock())
            return false;
        update_hierarchy_value();
        return true;
    }
private:
    std::mutex internal_mutex;
    unsigned long const hierarchy_value;
    unsigned long previous_hierarchy_value;
    static thread_local unsigned long this_thread_hierarchy_value;
    void check_for_hierarchy_violation()
    {
        if(this_thread_hierarchy_value <= hierarchy_value)
        {
            throw std::logic_error("mutex hierarchy violated");
        }
    }
    void update_hierarchy_value()
    {
        previous_hierarchy_value = this_thread_hierarchy_value;
        this_thread_hierarchy_value = hierarchy_value;
    }
};

thread_local unsigned long hierarchical_mutex::this_thread_hierarchy_value(ULONG_MAX);

std::shared_ptr<int> resource_ptr;
std::once_flag resource_flag;
void init_resource()
{
    std::cout << "Initializing resources" << std::endl;
    resource_ptr.reset(new int{42});
}
void foo()
{
    std::call_once(resource_flag, init_resource);
    std::cout << *resource_ptr << std::endl;
}

class dns_entry {};
class dns_cache
{
public:
    dns_entry find_entry(const std::string& domain) const
    {
        std::shared_lock<std::shared_mutex> lk(entry_mutex);
        const auto it = entries.find(domain);
        return (it == entries.end()) ? dns_entry() : it->second;
    }
    void update_or_add_entry(const std::string& domain, const dns_entry& dns_details)
    {
        std::lock_guard lk(entry_mutex);
        entries[domain] = dns_details;
    }
private:
    std::map<std::string, dns_entry> entries;
    mutable std::shared_mutex entry_mutex;
};

int main()
{
    std::list<int> my_list;
    
    std::thread t1(add_to_list, std::ref(my_list), 2);
    std::thread t2(list_contains, std::ref(my_list), 2);
    
    t1.join();
    t2.join();

    threadsafe_stack<int> stack;

    std::vector<std::thread> threads;

    for(int i = 1; i <= 5; ++i)
    {
        threads.emplace_back(add_to_stack<int>, std::ref(stack), i);
    }

    int res_val;
    std::thread t3(pop_from_stack<int>, std::ref(stack), std::ref(res_val));
    std::shared_ptr<int> val = pop_from_stack_ptr(stack);
    t3.join();
    for(auto& thread : threads)
    {
        thread.join();
    }
    std::cout << "Res_val: " << res_val << " val: " << *val << std::endl;

    std::thread t4(foo);
    std::thread t5(foo);
    t4.join();
    t5.join();
    return 0;
}