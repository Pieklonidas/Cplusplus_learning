#include <iostream>
#include "ObjectPool.hpp"
#include "ExpensiveObject.hpp"

ObjectPool<ExpensiveObject>::Object
    getExpensiveObject(ObjectPool<ExpensiveObject>& pool)
{
    auto object = pool.acquireObject();
    return object;   
}

void processExpensiveObject(ObjectPool<ExpensiveObject>::Object&)
{
    std::cout << " Processing..." << std::endl;
}

int main()
{
    ObjectPool<ExpensiveObject> requestPool;
    {
        std::vector<ObjectPool<ExpensiveObject>::Object> objects;
        for (size_t i = 0; i < 10; ++i)
        {
            objects.push_back(getExpensiveObject(requestPool));
        }
    }

    for(size_t i = 0; i < 15; ++i)
    {
        auto req = getExpensiveObject(requestPool);
        std::cout << i;
        processExpensiveObject(req);
    }
    
    return 0;
}