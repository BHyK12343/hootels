#ifndef BOOKING_H
#define BOOKING_H
#include <QString>
#include<QDate>
#include<QList>
class Servise;
class Room;
class Guest;
class Booking
{
private:
    int id;
    Guest* guest;
    Room* room;
    QDate checkIn;
    QDate checkOut;
    QList<Servise*> services;
    double totalCost;

public:
    Booking();
    Booking(int id, Guest* guest, Room* room,const QDate& checkIn, const QDate& checkOut);
    int getId()const;
    Guest* getGuest() const;
    Room* getRoom()const;
    QDate getCheckIn()const;
    QDate getCheckOut() const;
    double gettotalCost() const;
    QList<Servise*>getServise() const;
    double setServicesCost() const;
    void setId(int neWid);
    void setGuest(Guest* g);
    void setRoom(Room* r);
    void setCheckIn(QDate in);
    void setCheckOut(QDate Out);
    void setTotalCost(double c);
};

#endif // BOOKING_H
