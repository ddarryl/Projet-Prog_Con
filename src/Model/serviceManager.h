#include <map>
#include <QMutex>
#include <string>

class ServiceManager {
public:
    ServiceManager();
    void consommer(const std::string& item, int quantite);
    void reapprovisionner(const std::string& item, int quantite);
    void ajouterArticle(const std::string& item, int quantiteInitiale);
    void chargerDepuisBDD(const std::string& fichier);
    void sauvegarderDansBDD(const std::string& fichier);
    int getStock(const std::string& item) const;
    bool alerteStock(const std::string& item) const;
    void afficherStock() const;
    void onStockChange(const std::function<void(const std::string&, int)>& callback);
    void marquerPlatPret(int tableId, const std::string& plat);
    void ajouterPlat(int tableId, const std::string& plat);
    void preparerPlat(int tableId, const std::string& plat);
    void servirTable(int tableId);

private:
    std::map<std::string, int> stock;
    const int seuilCritique = 5;
    mutable QRecursiveMutex mutexStock; // Remplacez std::mutex par QMutex
    std::vector<std::function<void(const std::string&, int)>> callbacks;
    void logAction(const std::string& action, const std::string& item, int quantite = 0) const;
    void notifyStockChange(const std::string& item, int quantite);
    std::map<int, std::vector<std::string>> tablePlats;
};
