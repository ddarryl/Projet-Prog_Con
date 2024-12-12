#include "Ingredient.h"

Ingredient::Ingredient(std::string nom) : nom_(nom) {}

std::string Ingredient::getNom() const { return nom_; }