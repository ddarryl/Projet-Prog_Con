#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client {
public:
    Client(std::string nom, std::string prenom);
    std::string getNom() const;
    std::string getPrenom() const;

private:
    std::string nom_;
    std::string prenom_;
};

#endif