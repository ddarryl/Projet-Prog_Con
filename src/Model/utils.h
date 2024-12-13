#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <memory>
#include <string>
#include "serviceManager.h"

class utils {
public:
    explicit utils(int id) : id(id) {}
    int getId() const { return id; }
    void use() { std::cout << "Using resource " << id << std::endl; }
    void prepareDish(const std::string& dish);
    void preparerPlat(StockGestion& manager, int tableId, const std::string& plat);

private:
    int id;
};

std::shared_ptr<utils> createResource();

#endif
