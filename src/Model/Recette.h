#ifndef RECETTE_H
#define RECETTE_H

#include "EtapeRecette.h"
#include <vector>
#include <memory>
#include <thread>
#include <chrono>
#include <iostream>

class Recette {
public:
    Recette(const std::string& nom) : nom(nom) {}

    void ajouterEtape(const std::shared_ptr<EtapeRecette>& etape) {
        etapes.push_back(etape);
    }

    void executer() {
        std::vector<std::thread> threads;
        for (auto& etape : etapes) {
            threads.emplace_back([etape, this]() {
                while (!etape->estPret()) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Attente active
                }
                std::cout << "Début de l'étape : " << etape->getNom() << "\n";
                std::this_thread::sleep_for(std::chrono::seconds(etape->getDuree()));
                etape->executer();
                std::cout << "Fin de l'étape : " << etape->getNom() << "\n";
            });
        }
        for (auto& t : threads) {
            t.join();
        }
    }

private:
    std::string nom;
    std::vector<std::shared_ptr<EtapeRecette>> etapes;
};

#endif // RECETTE_H
