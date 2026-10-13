#include "guest.h"
#include <stdexcept>

Guest::Guest()
    : id(0), numberRoom(0)
{
}

Guest::Guest(int id, const QString& name, const QString& email,const QString& login, const QString& password,
             const QString& number, const QString& numberCard, int numberRoom)
    : id(id), name(name),login(login),password(password), email(email), number(number),
    numberCard(numberCard), numberRoom(numberRoom)
{
    if (id <= 0)
        throw std::invalid_argument("ID must be > 0");
    if (numberRoom < 0)
        throw std::invalid_argument("Room number must be >= 0");
}

int Guest::getId() const { return id; }
QString Guest::getName() const { return name; }
QString Guest::getEmail() const { return email; }
QString Guest::getNumber() const { return number; }
QString Guest::getNumberCard() const { return numberCard; }
int Guest::getNumberRoom() const { return numberRoom; }
QString Guest::getLogin()const{return login;}
QString Guest::getPassword() const{return password;}

void Guest::setName(const QString& n) { name = n; }
void Guest::setEmail(const QString& e) { email = e; }
void Guest::setLogin(const QString& l){login=l;}
void Guest::setPassword(const QString& p){password=p;}
void Guest::setNumber(const QString& n) { number = n; }
void Guest::setNumberCard(const QString& c) { numberCard = c; }
void Guest::setNumberRoom(int n) { numberRoom = n; }
