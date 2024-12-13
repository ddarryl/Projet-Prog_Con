#ifndef RESOURCE_POOL_H
#define RESOURCE_POOL_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

template <typename T>
class ResourcePool {
public:
    ResourcePool(size_t size, std::function<T()> initializer);
    T acquire();
    void release(T resource);

private:
    std::queue<T> pool;
    std::mutex mutexPool;
    std::condition_variable condition;
    std::function<T()> createResource;
};

#endif // RESOURCE_POOL_H