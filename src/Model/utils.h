#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <memory>
#include <string>

class utils {
public:
    explicit utils(int id) : id(id) {}
    int getId() const { return id; }
    void use() { std::cout << "Using resource " << id << std::endl; }
    void prepareDish(std::shared_ptr<utils> resource, const std::string& dish);

private:
    int id;
};

std::shared_ptr<utils> createResource();

#endif
