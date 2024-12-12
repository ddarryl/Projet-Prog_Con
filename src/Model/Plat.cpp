#include "Plat.h"

Plat::Plat(std::string nom, std::vector<Ingredient> ingredients) : nom_(nom), ingredients_(ingredients) {}

std::string Plat::getNom() const { return nom_; }
std::vector<Ingredient> Plat::getIngredients() const { return ingredients_; }