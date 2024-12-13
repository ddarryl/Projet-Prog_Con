#include "utils.h"
#include <iostream>
#include <thread>
#include <chrono>

std::shared_ptr<utils> createResource() {
    static int id = 1;
    return std::make_shared<utils>(id++);
}

void prepareDish(std::shared_ptr<utils> resource, const std::string& dish) {
    std::cout << "Preparing dish: " << dish << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Dish ready: " << dish << std::endl;
}
