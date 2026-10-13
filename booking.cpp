#include "booking.h"
#include"servise.h"
class Servise;
Booking::Booking(){}
Booking::Booking(int id, Guest* guest, Room* room,const QDate& checkIn, const QDate& checkOut):id(id),guest(guest),room(room),checkIn(checkIn),
    checkOut(checkOut){}
int Booking::getId()const{return this->id;}
Guest* Booking::getGuest() const{return this->guest;}
Room* Booking::getRoom()const{return this->room;}
QDate Booking::getCheckIn()const{return this->checkIn;}
QDate Booking::getCheckOut() const{return this->checkOut;}
double Booking::gettotalCost() const{return this->totalCost;}
QList<Servise*>Booking::getServise() const{return this->services;}
double Booking::setServicesCost() const {
    double sum = 0.0;
    for (Servise* s : services) {
        if (s) sum += s->GetPrise();
    }
    return sum;
}
void Booking::setId(int neWid){this->id=neWid;}
void Booking::setGuest(Guest* g){this->guest=g;}
void Booking::setRoom(Room* r){room=r;}
void Booking::setCheckIn(QDate in){checkIn=in;}
void Booking::setCheckOut(QDate Out){checkOut=Out;}
void Booking::setTotalCost(double c){totalCost=c;}

