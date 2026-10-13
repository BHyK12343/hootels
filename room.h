#ifndef ROOM_H
#define ROOM_H
#include <QString>

class Room
{
private:
    int id;
    const QString nameRoom;
    const int numberRoom;
    const int floor;
    const int rooms;
    const double area;
    double prise;
    QString comment;
    bool status;
    QString imagePath;
public:
    Room();
    Room(int id, const QString& nameRoom,const int numberRoom,const int floor,const int rooms,const double area,double prise,const QString& comment,bool status
         ,QString imagePath);
    QString getNameRoom() const;
    int getNumberRoom() const;
    double getPrise() const;
    QString getComment() const;
    int getFloor() const;
    int getRooms() const;
    double getArea() const;
    bool getStatus() const;
    void setPrise(double newprise);
    void setStatus(bool newStatus);
    int getId() const;
    void setId(int newId);
    QString getImagePath() const ;
};

#endif // ROOM_H
