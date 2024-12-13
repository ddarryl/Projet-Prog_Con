#ifndef ETAPERECETTE_H
#define ETAPERECETTE_H

#include <string>
#include <functional>
#include <memory>

class EtapeRecette {
public:
    EtapeRecette(const std::string& nom, int duree, const std::function<void()>& action)
        : nom(nom), duree(duree), action(action), terminee(false) {}

    void executer() {
        action();
        terminee = true;
    }
    void ajouterDependance(const std::shared_ptr<EtapeRecette>& etape) {
        dependances.push_back(etape);
    }

    bool estPret() const {
        for (const auto& dep : dependances) {
            if (!dep->estTerminee()) return false;
        }
        return true;
    }

    bool estTerminee() const { return terminee; }
    int getDuree() const { return duree; }
    std::string getNom() const { return nom; }

private:
    std::vector<std::shared_ptr<EtapeRecette>> dependances;
    std::string nom;
    int duree;
    std::function<void()> action;
    bool terminee;
};

#endif
