#include "database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVariant>
#include "guest.h"
#include "room.h"
#include "servise.h"
#include "booking.h"
class Guest;
class Room;
class Servise;
class Booking;
bool Database::connect(){
    QSqlDatabase db= QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setPort(5432);
    db.setDatabaseName("hootel_db");
    db.setUserName("postgres");
    db.setPassword("3105");
    if(!db.open()){
        qDebug()<<"Ошибка db"<<db.lastError().text();
        return false;
    }
    qDebug() << "База подключена!";
    return true;
}
void Database::disconnect(){
    QSqlDatabase db= QSqlDatabase::database();
    if(db.isOpen()) db.close();
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);

}
static bool isConnect(){
    return QSqlDatabase::database().isOpen();
}
bool Database::createTables(){
    QSqlQuery query;
    /*int id;
    const QString nameRoom;
    const int numberRoom;
    const int floor;
    const int rooms;
    const double area;
    double prise;
    QString comment;
    bool status;*/

    if(!query.exec("CREATE TABLE IF NOT EXISTS rooms"
                   "(id SERIAL PRIMARY KEY,"
                   "name_room VARCHAR(20),"
                   "number_room INTEGER NOT NULL,"
                   "floor INTEGER,"
                    "rooms INTEGER,"
                   "area DECIMAL(5,2),"
                   "prise DECIMAL(10,2),"
                   "comment VARCHAR(300),"
                   "status BOOLEAN DEFAULT FALSE,"
                    "image_path VARCHAR(200))"))
        {
        qDebug()<<"Ошибка базы данных room"<<query.lastError().text();
        return false;
        }
    /*int id;
    QString name;
    QString email;
    QString number;
    QString numberCard;
    int numberRoom;*/
    if(!query.exec("CREATE TABLE IF NOT EXISTS guests ("
                    "id SERIAL PRIMARY KEY,"
                    "name VARCHAR(100),"
                    "email VARCHAR(50),"
                    "login VARCHAR(30),"
                    "password VARCHAR(30),"
                    "number VARCHAR(20),"
                    "number_card VARCHAR(30),"
                    "number_room INTEGER DEFAULT 0)"
                ))
    {
        qDebug()<<"Ошибка базы данных guest"<<query.lastError().text();
        return false;
    }
    /*
    const QString nameServise;
    QDate in_servise;
    QDate out_servise;
    double prise;
    int id;
    const QString comment;*/
    if(!query.exec("CREATE TABLE IF NOT EXISTS services ("
                    "id INTEGER PRIMARY KEY,"
                    "name_servise VARCHAR(20),"
                    "in_servise DATE,"
                    "out_servise DATE,"
                    "prise DECIMAL(10,2),"
                    "comment VARCHAR(100))"))
    {
        qDebug()<<"Ошибка базы данных service"<<query.lastError().text();
        return false;
    }
    /*
    int id;
    Guest* guest;
    Room* room;
    QDate checkIn;
    QDate checkOut;
    QList<Servise*> services;
    double totalCost*/
    if(!query.exec("CREATE TABLE IF NOT EXISTS bookings ("
                    "id SERIAL PRIMARY KEY,"
                    "guest_id INTEGER REFERENCES guests(id) ON DELETE CASCADE,"
                    "room_id INTEGER REFERENCES rooms(id) ON DELETE CASCADE,"
                    "check_in DATE,"
                    "check_out DATE,"
                    "total_cost DECIMAL(10,2))"))
    {
        qDebug()<<"Ошибка базы данных bookings"<<query.lastError().text();
        return false;
    }
    if(!query.exec("CREATE TABLE IF NOT EXISTS booking_services ("
                   "booking_id INTEGER REFERENCES bookings(id) ON DELETE CASCADE,"
                   "service_id INTEGER REFERENCES services(id) ON DELETE CASCADE,"
                   "PRIMARY KEY(booking_id,service_id))"))
    {
        qDebug()<<"Ошибка базы данных booking_services"<<query.lastError().text();
        return false;
    }
    qDebug()<<"Таблицы созданы";
    return true;

}
//
QList<Room*> Database::getAllRoom(){
    QList<Room*> result;
    QSqlQuery query;
    if(!query.exec("SELECT id,name_room,number_room,floor,rooms,area,prise,comment,status,image_path FROM rooms")){
        qDebug()<<"Ошибка открытия таблицы rooms"<<query.lastError().text();
        return result;
    }
    while(query.next()){
        int id=query.value("id").toInt();
        QString nameRoom=query.value("name_room").toString();
        int numberRoom=query.value("number_room").toInt();
        int floor=query.value("floor").toInt();
        int rooms=query.value("rooms").toInt();
        double area=query.value("area").toDouble();
        double prise=query.value("prise").toDouble();
        QString comment=query.value("comment").toString();
        bool status=query.value("status").toBool();
        QString imagePath=query.value("image_path").toString();
        Room*r=new Room(id,nameRoom,numberRoom,floor,rooms,area,prise,comment,status,imagePath);
        result.append(r);
    }
    return result;
}
Room* Database::getRoomId(int id){
    QSqlQuery query;
    query.prepare("SELECT id,name_room,number_room,floor,rooms,area,prise,comment,status FROM rooms WHERE id=:id");
    query.bindValue(":id",id);
    if(!query.exec() || !query.next()){
        qDebug()<<"Комната не найдена"<<id;
        return nullptr;
    }
    Room* r=new Room(   query.value("id").toInt(),
                         query.value("name_room").toString(),
                         query.value("number_room").toInt(),
                         query.value("floor").toInt(),
                         query.value("rooms").toInt(),
                         query.value("area").toDouble(),
                         query.value("prise").toDouble(),
                         query.value("comment").toString(),
                         query.value("status").toBool(),
                        query.value("image_path").toString());

    return r;

}
int Database::addRoom(Room* room){
    QSqlQuery query;
    query.prepare("INSERT INTO rooms(name_room,number_room,floor,rooms,area,prise,comment,status) "
                  "Values(:name_room,:number_room,:floor,:rooms,:area,:prise,:comment,:status) ""RETURNING id");
    query.bindValue(":name_room",room->getNameRoom());
    query.bindValue(":number_room",room->getNumberRoom());
    query.bindValue(":floor",room->getFloor());
    query.bindValue(":rooms",room->getRooms());
    query.bindValue(":area",room->getArea());
    query.bindValue(":prise",room->getPrise());
    query.bindValue(":comment",room->getComment());
    query.bindValue(":status",room->getStatus());
    if(!query.exec()){
        qDebug()<<"Ошибка в addRoom"<<query.lastError().text();
        return -1;
    }
    if(query.exec()){
        return query.value("id").toInt();
    }
    return -1;
}
bool Database::UpdateRoomStatus(int roomId,bool status){
    QSqlQuery query;
    query.prepare("UPDATE rooms SET status=:status WHERE id=:id");
    query.bindValue(":status",status);
    query.bindValue(":id",roomId);
    if(!query.exec()){
        qDebug()<<"Ошибка update room"<<query.lastError().text();
        return false;
    }
    return true;
}
//
QList<Guest*>Database::getAllGuest(){
    QSqlQuery query;
    QList<Guest*> result;
    if(!query.exec("SELECT id,name,email,login,password,number,number_card,number_room FROM guests")){
        qDebug()<<"Ошибка в getguest"<<query.lastError().text();
        return result;
    }
    while(query.next()){
        Guest*r=new Guest(query.value("id").toInt(),query.value("name").toString(),query.value("email").toString(),query.value("login").toString(),query.value("password").toString(),
                             query.value("number").toString(),query.value("number_card").toString(),query.value("number_room").toInt());
        result.append(r);
    }
    return result;
}
Guest* Database::getGuestId(int id){
    QSqlQuery query;
    query.prepare("SELECT id,name,email,login,password,number,number_card,number_room FROM guests WHERE id=:id");
    query.bindValue(":id",id);
    if(query.exec()||!query.next()){
        qDebug()<<"Ошибка в getguest"<<query.lastError().text();
        return nullptr;
    }
    Guest*g=new Guest(query.value("id").toInt(),query.value("name").toString(),query.value("email").toString(),query.value("login").toString(),query.value("password").toString(),
                         query.value("number").toString(),query.value("number_card").toString(),query.value("number_room").toInt());
    return g;

}
int  Database::addGuest(Guest* guest){
    QSqlQuery query;
    query.prepare("INSERT INTO guests(name,email,login,password,number,number_card,number_room) "
                  "VALUES(:name,:email,:login,:password ,:number,:number_card,:number_room) ""RETURNING id");
    query.bindValue(":name",guest->getName());
    query.bindValue(":email",guest->getEmail());
    query.bindValue(":login",guest->getLogin());
    query.bindValue(":password",guest->getPassword());
    query.bindValue(":number",guest->getNumber());
    query.bindValue(":number_card",guest->getNumberCard());
    query.bindValue(":number_room",guest->getNumberRoom());
    if(!query.exec()){
        qDebug()<<"Ошибка в addGuest"<<query.lastError().text();
        return -1;
    }
    if(query.next()){
        return query.value("id").toInt();
    }
    return -1;

}
bool Database::updateGuestRoom(int guestId,int numberRoom){
    QSqlQuery query;
    query.prepare("UPDATE guests SET number_room=:number_room WHERE id=:id");
    query.bindValue(":id",guestId);
    query.bindValue(":number_room",numberRoom);
    if(!query.exec()){
        qDebug()<<"Ошибка в updateGuest"<<query.lastError().text();
        return false;
    }
    return true;
}
Guest* Database::checklogin(const QString login,const QString password){
    QSqlQuery query;
    query.prepare("SELECT id,name,email,login,password,number,number_card,number_room "
                  "FROM guests "
                  "WHERE password=:password AND login=:login ");
    query.bindValue(":password",password);
    query.bindValue(":login",login);
    if(!query.exec()||!query.next()){
        qDebug()<<"неверный логин или пароль";
        return nullptr;
    }
    Guest*g=new Guest(query.value("id").toInt(),query.value("name").toString(),query.value("email").toString(),query.value("login").toString(),query.value("password").toString(),
                         query.value("number").toString(),query.value("number_card").toString(),query.value("number_room").toInt());
    return g;
}
Guest* Database::getGuestLogin(const QString& login){
    QSqlQuery query;
    query.prepare("SELECT id,name,email,login,password,number,number_card,number_room "
                  "FROM guests "
                  "WHERE login=:login ");
    query.bindValue(":login",login);
    if(!query.exec()||!query.next()){
        qDebug()<<"логин занят";
        return nullptr;
    }
    Guest* g=new Guest(query.value("id").toInt(),query.value("name").toString(),query.value("email").toString(),query.value("login").toString(),query.value("password").toString(),
                        query.value("number").toString(),query.value("number_card").toString(),query.value("number_room").toInt());
    return g;
}
int Database::registerNewGuest(Guest*g){
    QSqlQuery query;
    query.prepare("INSERT INTO guests(name,email,login,password,number,number_card,number_room) "
                  "VALUES(:name,:email,:login,:password,:number,:number_card,:number_room) "
                  "RETURNING id");
    query.bindValue(":name",g->getName());
    query.bindValue(":email",g->getEmail());
    query.bindValue(":login",g->getLogin());
    query.bindValue(":password",g->getPassword());
    query.bindValue(":number",g->getNumber());
    query.bindValue(":number_card",g->getNumberCard());
    query.bindValue(":number_room",g->getNumberRoom());
    if(!query.exec()){
        return -1;
    }
    if(query.next()){
        return query.value("id").toInt();
    }
    return -1;
}
QList<Servise*> Database::getAllServise(){
    QSqlQuery query;
    QList<Servise*> result;
    if(!query.exec("SELECT id,name_servise,in_servise,out_servise,prise,comment FROM services")){
        qDebug()<<"Ошибка getservise"<<query.lastError().text();
        return result;
    }
    while(query.next()){
        Servise* s=new Servise(query.value("id").toInt(),query.value("name_servise").toString(),query.value("in_servise").toDate(),query.value("out_servise").toDate(),
            query.value("prise").toDouble(),query.value("comment").toString());
        result.append(s);
    }
    return result;
}
int Database::addServise(Servise* servise){
    QSqlQuery query;
    query.prepare("INSERT INTO services(name_servise,in_servise,out_servise,prise,comment) "
                  "VALUES(:name_servise,:in_servise,:out_servise,:prise,:comment) "
                  "RETURNING id");
    query.bindValue(":name_servise",servise->GetName());
    query.bindValue(":in_servise",servise->GetIn());
    query.bindValue(":out_servise",servise->GetOut());
    query.bindValue(":prise",servise->GetPrise());
    query.bindValue(":comment",servise->GetComment());
    if(!query.exec()){
        //qDebug()<<"Ошибка в addServise"<<query.lastError().text();
        return -1;
    }
    if(query.next()){
        return query.value("id").toInt();
    }
    return -1;
}

QList<Booking*> Database::getAllBooking(const QList<Guest*>&guests,const QList<Room*>&rooms){
    QSqlQuery query;
    QList<Booking*>result;
    if(!query.exec("SELECT id,guest_id,room_id,check_in,check_out,total_cost FROM bookings")){
        qDebug()<<"Ошибка в gatallBooking"<<query.lastError().text();
        return result;
    }

    while(query.next()){
        int id=query.value("id").toInt();
        int guest_id=query.value("guest_id").toInt();
        int room_id=query.value("room_id").toInt();
        QDate check_in=query.value("check_in").toDate();
        QDate check_out=query.value("check_out").toDate();
        double total_cost=query.value("total_cost").toDouble();
        Guest*guest=nullptr;
        for(Guest*g:guests){
            if(guest_id==g->getId()){
                guest=g;
                break;
            }
        }
        Room*room=nullptr;
        for(Room* r:rooms){
            if(r->getId()==room_id){
                room=r;
                break;
            }
        }
        if(!room || !guest){
            qDebug()<<"Бронь:"<<id<<" не найденна ";
            continue;
        }
        Booking*b=new Booking(id,guest,room,check_in,check_out);
        b->setTotalCost(total_cost);
        result.append(b);
    }
    return result;
}
int Database::addBooking(Booking* booking){
    QSqlQuery query;
    query.prepare("INSERT INTO bookings(guest_id,room_id,check_in,check_out,total_cost) "
                  "VALUES(:guest_id,:room_id,:check_in,:check_out,:total_cost) "
                  "RETURNING id");
    query.bindValue(":guest_id",booking->getGuest()->getId());
    query.bindValue(":room_id",booking->getRoom()->getId());
    query.bindValue(":check_in",booking->getCheckIn());
    query.bindValue(":check_out",booking->getCheckOut());
    query.bindValue(":total_cost",booking->gettotalCost());
    if(!query.exec()){
        qDebug()<<"Ошибка в addBooking"<<query.lastError().text();
        return -1;
    }
    if(query.next()){
        return query.value("id").toInt();
    }
    return -1;
}
bool Database::updateBookingTotal(int bookingid,double total){
    QSqlQuery query;
    query.prepare("UPDATE bookings SET total_cost=:total WHERE id=:id");
    query.bindValue(":total",total);
    query.bindValue(":id",bookingid);
    if(!query.exec()){
        qDebug()<<"Ошибка в update bookings"<<query.lastError().text();
        return false;
    }
    return true;
}
//
QList<Servise*> Database::getServiseForBooking(int bookingId,const QList<Servise*>& allServices){
    QSqlQuery query;
    QList<Servise*>result;
    query.prepare("SELECT service_id FROM booking_services WHERE booking_id=:id");
    query.bindValue(":id",bookingId);
    if(!query.exec()){
        qDebug()<<"ошибка в getservisebooking"<<query.lastError().text();
        return result;
    }
    while(query.next()){
        int service_id=query.value("service_id").toInt();
        for(Servise* s:allServices){
            if(s->GetId()==service_id){
                result.append(s);
                break;
            }
        }
    }
    return result;
}
bool Database::addServicesToBooking(int bookingId, int servicesId) {
    QSqlQuery query;
    query.prepare("INSERT INTO booking_services (booking_id, service_id) "
                  "VALUES (:booking_id, :service_id) "
                  "ON CONFLICT DO NOTHING");
    query.bindValue(":booking_id", bookingId);
    query.bindValue(":service_id", servicesId);
    if (!query.exec()) {
        qDebug() << "Ошибка sql addServices:" << query.lastError().text();
        return false;
    }
    return true;
}
bool Database::removeServicesFromBooking(int booking,int servicesId){
    QSqlQuery query;
    query.prepare("DELETE FROM booking_services"
                  "WHERE booking_id=:booking AND service_id=:servicesId ");
    query.bindValue(":booking",booking);
    query.bindValue(":servicesId",servicesId);
    if(!query.exec()){
        qDebug()<<"Ошибка sql removeServicesFromBooking"<<query.lastError().text();
        return false;
    }
    return true;
}
