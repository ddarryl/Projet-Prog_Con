#include "ressourceGestion.h"
#include <chrono>
#include <iomanip>
#include <sstream>

RessourceGestion::RessourceGestion() {
    stock["Assiettes"] = 50;
    stock["Nappes"] = 20;
    stock["Verres"] = 50;
    stock["Corbeilles à pain"] = 15;

    for (int i = 1; i <= 10; ++i) {
        tables[i] = true;
    }
}

void RessourceGestion::ajouterStock(const std::string& ressource, int quantite) {
    std::lock_guard<std::mutex> lock(mutexStock);
    stock[ressource] += quantite;
    log("Added " + std::to_string(quantite) + " to " + ressource + ". New stock: " + std::to_string(stock[ressource]));
}

bool RessourceGestion::consommerRessource(const std::string& ressource, int quantite) {
    std::lock_guard<std::mutex> lock(mutexStock);
    if (verifierDisponibilite(ressource, quantite)) {
        stock[ressource] -= quantite;
        log("Consumed " + std::to_string(quantite) + " from " + ressource + ". Remaining stock: " + std::to_string(stock[ressource]));
        return true;
    }
    log("Error: Not enough " + ressource + " in stock.");
    return false;
}

int RessourceGestion::obtenirStock(const std::string& ressource) const {
    std::lock_guard<std::mutex> lock(mutexStock);
    return stock.count(ressource) ? stock.at(ressource) : 0;
}

bool RessourceGestion::verifierDisponibilite(const std::string& ressource, int quantite) const {
    std::lock_guard<std::mutex> lock(mutexStock);
    return stock.count(ressource) && stock.at(ressource) >= quantite;
}

bool RessourceGestion::reserverTable(int tableId) {
    std::lock_guard<std::mutex> lock(mutexTables);
    if (tables.count(tableId) && tables[tableId]) {
        tables[tableId] = false;
        log("Table " + std::to_string(tableId) + " reserved.");
        return true;
    }
    log("Error: Table " + std::to_string(tableId) + " is not available.");
    return false;
}

bool RessourceGestion::libererTable(int tableId) {
    std::lock_guard<std::mutex> lock(mutexTables);
    if (tables.count(tableId) && !tables[tableId]) {
        tables[tableId] = true;
        log("Table " + std::to_string(tableId) + " is now available.");
        return true;
    }
    log("Error: Table " + std::to_string(tableId) + " is already available.");
    return false;
}

bool RessourceGestion::estTableDisponible(int tableId) const {
    std::lock_guard<std::mutex> lock(mutexTables);
    return tables.count(tableId) && tables.at(tableId);
}

void RessourceGestion::log(const std::string& message) const {
    auto now = std::chrono::system_clock::now();
    auto nowTime = std::chrono::system_clock::to_time_t(now);
    std::ostringstream oss;
    oss << "[" << std::put_time(std::localtime(&nowTime), "%Y-%m-%d %H:%M:%S") << "] " << message;
    std::cout << oss.str() << std::endl;
}
