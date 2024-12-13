#ifndef RESOURCE_POOL_H
#define RESOURCE_POOL_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

template <typename T>
class ResourcePool {
public:
    ResourcePool(size_t size, std::function<T()> initializer); // Accept a function to create resources
    T acquire();
    void release(T resource);

private:
    std::queue<T> pool;                        // Available resources
    std::mutex mutexPool;                      // Protect pool access
    std::condition_variable condition;         // Synchronize threads
    std::function<T()> createResource;        // Store the resource creation function
};

#endif // RESOURCE_POOL_H