#ifndef PLAT_H
#define PLAT_H

#include <string>
#include <vector>
#include "Ingredient.h"

class Plat {
public:
    Plat(std::string nom, std::vector<Ingredient> ingredients);
    std::string getNom() const;
    std::vector<Ingredient> getIngredients() const;

private:
    std::string nom_;
    std::vector<Ingredient> ingredients_;
};

#endif // PLAT_H