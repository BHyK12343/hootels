#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include<QString>
#include<QList>
class Booking;
class Room;
class Servise;
class Guest;
class Database
{

public:
    static bool connect();
    static void disconnect();
    static bool isConnect();
    static bool createTables();
    //
    static QList<Room*>getAllRoom();
    static Room* getRoomId(int id);
    static int addRoom(Room* room);
    static bool UpdateRoomStatus(int roomId,bool status);
    //
    static QList<Guest*>getAllGuest();
    static Guest* getGuestId(int id);
    static int addGuest(Guest* guest);
    static bool updateGuestRoom(int guestId,int numberRoom);
    static Guest* checklogin(const QString login,const QString password);
    static Guest* getGuestLogin(const QString& login);
    static int registerNewGuest(Guest*g);
    //
    static QList<Servise*> getAllServise();
    static int addServise(Servise* servise);
    //
    static QList<Booking*>getAllBooking(const QList<Guest*>&guests,const QList<Room*>&rooms);
    static int addBooking(Booking* booking);
    //
    static QList<Servise*> getServiseForBooking(int bookingId,const QList<Servise*>& allServices);
    static bool addServicesToBooking(int bookingId,int servicesId);
    static bool removeServicesFromBooking(int booking,int servicesId);
    static bool updateBookingTotal(int bookingid,double total);
    database();
};

#endif // DATABASE_H
