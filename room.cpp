#include "room.h"
#include <utility>

Room::Room()
    : nameRoom(""),
    numberRoom(0),
    floor(0),
    rooms(0),
    area(0.0),
    prise(0.0),
    comment(""),
    status(false),
    imagePath("")
{}
Room::Room(int id, const QString& nameRoom,const int numberRoom,const int floor,const int rooms,const double area,double prise,const QString& comment,bool status
           ,QString imagePath):
    id(id),
    nameRoom(nameRoom),
    numberRoom(numberRoom),
    floor(floor),
    rooms(rooms),
    area(area),
    prise(prise),
    comment(comment),
    status(status),
    imagePath(imagePath)
    {}
    QString Room::getNameRoom() const{return this->nameRoom;}
    int Room::getNumberRoom()const{return this->numberRoom;}
    double Room::getPrise() const{return this->prise;}
    QString Room::getComment() const{return this->comment;}
    int Room::getFloor() const{return this->floor;}
    int Room::getRooms() const{return this->rooms;}
    double Room::getArea() const{return this->area;}
    bool Room::getStatus() const{return this->status;}
    void Room::setPrise(double newprise){this->prise=newprise;}
    void Room::setStatus(bool newStatus){this->status=newStatus;}
    void Room::setId(int newid){this->id=newid;}
    int Room::getId() const{return id;}
    QString Room::getImagePath() const { return imagePath;}




