#include "EtapeRecette.h"

#include <iostream>
#include <thread>
#ifndef RECETTE_H
#define RECETTE_H

#include <vector>
#include <memory>
#include "EtapeRecette.h"

class Recette {
public:
    Recette(const std::string& nom) : nom(nom) {}

    void ajouterEtape(std::shared_ptr<EtapeRecette> etape) {
        etapes.push_back(etape);
    }

    void executer() {
        std::cout << "Executing recipe: " << nom << std::endl;
        for (auto& etape : etapes) {
            etape->executer();
        }
        std::cout << "Recipe completed: " << nom << std::endl;
    }

    void executerEnParallele() {
        std::cout << "Executing recipe in parallel: " << nom << std::endl;
        std::vector<std::thread> threads;
        for (auto& etape : etapes) {
            threads.emplace_back([etape]() { etape->executer(); });
        }
        for (auto& thread : threads) {
            thread.join();
        }
        std::cout << "Recipe completed in parallel: " << nom << std::endl;
    }

private:
    std::string nom;
    std::vector<std::shared_ptr<EtapeRecette>> etapes;
};

#endif // RECETTE_H
