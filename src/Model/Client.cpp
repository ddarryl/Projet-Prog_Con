#include "Client.h"

Client::Client(std::string nom, std::string prenom) : nom_(nom), prenom_(prenom) {}

std::string Client::getNom() const { return nom_; }
std::string Client::getPrenom() const { return prenom_; }