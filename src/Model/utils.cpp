#include "utils.h"
#include <iostream>
#include <thread>
#include <chrono>

std::shared_ptr<utils> createResource() {
    static int id = 1;
    return std::make_shared<utils>(id++);
}

void prepareDish(const std::string& dish) {
    std::cout << "Preparing dish: " << dish << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Dish ready: " << dish << std::endl;
}

void preparerPlat(StockGestion& manager, int tableId, const std::string& plat) {
    std::cout << "Preparing dish: " << plat << " for table " << tableId << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate preparation time
    manager.marquerPlatPret(tableId, plat);
}