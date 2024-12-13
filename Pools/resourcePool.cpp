#include "resourcePool.h"
#include "../src/Model/assiette.h"
#include "../src/Model/table.h"
#include "../src/Model/utils.h"

// Implementation of ResourcePool methods

template <typename T>
ResourcePool<T>::ResourcePool(size_t size, std::function<T()> initializer) : createResource(initializer) {
    for (size_t i = 0; i < size; ++i) {
        pool.push(createResource()); // Call the function to create resources
    }
}

template <typename T>
T ResourcePool<T>::acquire() {
    std::unique_lock<std::mutex> lock(mutexPool);
    condition.wait(lock, [this]() { return !pool.empty(); });

    T resource = pool.front();
    pool.pop();
    return resource;
}

template <typename T>
void ResourcePool<T>::release(T resource) {
    {
        std::lock_guard<std::mutex> lock(mutexPool);
        pool.push(resource);
    }
    condition.notify_one();
}

// Explicit instantiation for shared_ptr<utils>
template class ResourcePool<std::shared_ptr<utils>>;
template class ResourcePool<Assiette*>; // Assurez-vous d'ajouter cette ligne pour Assiette
template class ResourcePool<Table*>; // Assurez-vous d'ajouter cette ligne pour Table