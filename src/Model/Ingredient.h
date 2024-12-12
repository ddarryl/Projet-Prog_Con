#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

class Ingredient {
public:
    Ingredient(std::string nom);
    std::string getNom() const;

private:
    std::string nom_;
};

#endif // INGREDIENT_H