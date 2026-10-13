#ifndef GUEST_H
#define GUEST_H
#include <QString>

class Guest
{
private:
    int id;
    QString name;
    QString email;
    QString login;
    QString password;
    QString number;
    QString numberCard;
    int numberRoom;

public:
    Guest();
    Guest(int id, const QString& name, const QString& email,const QString& login,const QString& password,
          const QString& number, const QString& numberCard, int numberRoom);
    int getId() const;
    QString getName() const;
    QString getEmail() const;
    QString getLogin()const;
    QString getPassword() const;
    QString getNumber() const;
    QString getNumberCard() const;
    int getNumberRoom() const;
    void setName(const QString& n);
    void setEmail(const QString& e);
    void setLogin(const QString& l);
    void setPassword(const QString& p);
    void setNumber(const QString& n);
    void setNumberCard(const QString& c);
    void setNumberRoom(int n);
};

#endif // GUEST_H

