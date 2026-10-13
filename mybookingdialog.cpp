#include "mybookingdialog.h"
#include "ui_mybookingdialog.h"
#include<QMessageBox>

mybookingdialog::mybookingdialog(Guest* user,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::mybookingdialog)
    , currentUser(user)
{
    ui->setupUi(this);
    loadBooking();
    fillBookingTable();
    connect(ui->closeButton,&QPushButton::clicked,this,&mybookingdialog::onCloseClicked);
    setWindowTitle("Мои брони-"+currentUser->getName());
}
void mybookingdialog::onCloseClicked(){
    reject();
}
void mybookingdialog::loadBooking(){
    QList<Guest*> allGuest=Database::getAllGuest();
    QList<Room*> allRoom=Database::getAllRoom();
    QList<Booking*> allBooking=Database::getAllBooking(allGuest,allRoom);
    for(Booking*b:allBooking){
        if(b->getGuest()->getId()==currentUser->getId()){
            booking.append(b);
        }
    }
}
void mybookingdialog::fillBookingTable(){
    ui->bookingTable->setRowCount(0);
    bool count=false;
    for(Booking* b:booking){
        int row=ui->bookingTable->rowCount();
        ui->bookingTable->insertRow(row);
        ui->bookingTable->setItem(row,0,new QTableWidgetItem(QString::number(b->getRoom()->getNumberRoom()
                                                                      )));
        ui->bookingTable->setItem(row,1,new QTableWidgetItem(b->getRoom()->getNameRoom()));
        ui->bookingTable->setItem(row,2,new QTableWidgetItem(b->getCheckIn().toString("dd.MM.yyyy")));
        ui->bookingTable->setItem(row,3,new QTableWidgetItem(b->getCheckOut().toString("dd.MM.yyyy")));
        ui->bookingTable->setItem(row,4,new QTableWidgetItem(QString::number(b->gettotalCost())));
        count=true;
    }
    if(!count){
        QMessageBox::information(this," ","У вас пока что нету бронирований");
    }
}
mybookingdialog::~mybookingdialog()
{
    delete ui;
}
