#ifndef STOCKGESTION_H
#define STOCKGESTION_H

#include <map>
#include <string>
#include <vector>
#include <mutex> // Include for std::mutex
#include <functional> // Include for std::function

class StockGestion {
public:
    StockGestion();
    void consommer(const std::string& item, int quantite);
    void reapprovisionner(const std::string& item, int quantite);
    void ajouterArticle(const std::string& item, int quantiteInitiale);
    void chargerDepuisBDD(const std::string& fichier); // Load from a file or database
    void sauvegarderDansBDD(const std::string& fichier); // Save state to a file
    int getStock(const std::string& item) const;
    bool alerteStock(const std::string& item) const;
    void afficherStock() const;
    void onStockChange(const std::function<void(const std::string&, int)>& callback); // Add callback for stock changes
    void marquerPlatPret(int tableId, const std::string& plat);
    void ajouterPlat(int tableId, const std::string& plat);
    void preparerPlat(int tableId, const std::string& plat);
    void servirTable(int tableId);

private:
    std::map<std::string, int> stock;
    const int seuilCritique = 5;
    std::mutex mutexStock; // Declare mutex for thread safety (non-const)
    std::vector<std::function<void(const std::string&, int)>> callbacks; // Store callbacks
    void logAction(const std::string& action, const std::string& item, int quantite = 0) const;
    void notifyStockChange(const std::string& item, int quantite); // Notify callbacks of stock changes
    std::map<int, std::vector<std::string>> tablePlats;
};

#endif // STOCKGESTION_H