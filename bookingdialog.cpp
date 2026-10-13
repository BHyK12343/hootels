#include "bookingdialog.h"
#include "ui_bookingdialog.h"
#include"database.h"
#include<QMessageBox>
#include<QDebug>
#include"QString"
#include "booking.h"
#include<QPixmap>
#include <QLayout>
#include <QVBoxLayout>
BookingDialog::BookingDialog(Room* room, Guest* user,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::BookingDialog)
    , currentRoom(room)
    , currentUser(user)
{
    ui->setupUi(this);
    QPixmap pix(currentRoom->getImagePath());
    if(!pix.isNull()){
        ui->label_5->setPixmap(pix);
        ui->label_5->setScaledContents(true);
    }
    ui->roomInfoLabel->setText("Номер:"+QString::number(currentRoom->getNumberRoom())+"-"+currentRoom->getNameRoom());
    ui->priceLabel->setText("Цена за ночь:"+QString::number(currentRoom->getPrise())+"Р");
    ui->checkInEdit->setDate(QDate::currentDate());
    ui->checkOutEdit->setDate(QDate::currentDate().addDays(1));
    connect(ui->checkInEdit,&QDateEdit::dateChanged,this,&BookingDialog::onDateChanged);
    connect(ui->confirmButton,&QPushButton::clicked,this,&BookingDialog::onConfirmClicked);
    connect(ui->cancelButton,&QPushButton::clicked,this,&BookingDialog::onCancelClicked);
    connect(ui->checkOutEdit,&QDateEdit::dateChanged,this,&BookingDialog::onDateChanged);
    loadServices();
}
int BookingDialog::getNights(){
    return ui->checkInEdit->date().daysTo(ui->checkOutEdit->date());
}
double BookingDialog::calculateTotal(){
    return currentRoom->getPrise()*getNights()+getServicesCost();
}
void BookingDialog::updateInfo(){
    int nights=getNights();
    double total=calculateTotal();
    ui->nightsLabel->setText("Ночей:"+QString::number(nights));
    ui->totalLabel->setText("Итого:"+QString::number(total));
}
void BookingDialog::onDateChanged(){
    if(ui->checkOutEdit->date()<=ui->checkInEdit->date()){
        ui->checkOutEdit->setDate(ui->checkInEdit->date().addDays(1));
    }
    updateInfo();
}
void BookingDialog::onCancelClicked(){
    reject();
}
void BookingDialog::onConfirmClicked(){
    if(currentRoom->getStatus()){
        QMessageBox::warning(this,"Ошибка бронирования","номер уже занят");
        return;
    }
    Booking* b=new Booking();
    b->setGuest(currentUser);
    b->setRoom(currentRoom);
    b->setCheckIn(ui->checkInEdit->date());
    b->setCheckOut(ui->checkOutEdit->date());
    b->setTotalCost(calculateTotal());
    int id=Database::addBooking(b);
    if(id<=0){
        QMessageBox::warning(this,"Ошибка","не удалось сохранить бронь");
        delete b;
        return;
    }
    b->setId(id);
    QMessageBox::information(this,"уведомление","бронь зарегестрирована");
    for (int i = 0; i < servicesCheckBox.size(); i++) {
        if (servicesCheckBox[i]->isChecked()) {
            Database::addServicesToBooking(id, allServices[i]->GetId());
        }
    }
    Database::UpdateRoomStatus(currentRoom->getId(), true);
    currentRoom->setStatus(true);
    QMessageBox::information(this, "Уведомление", "Бронь зарегистрирована");
    accept();
}
double BookingDialog::getServicesCost() const{
    double sum=0.0;
    for(int i=0;i<servicesCheckBox.size();i++){
        if(servicesCheckBox[i]->isChecked()){
            sum+=allServices[i]->GetPrise();
        }
    }
    return sum;
}
void BookingDialog::loadServices() {
    if (!ui->servicesGroup->layout()) {
        QVBoxLayout* layout = new QVBoxLayout(ui->servicesGroup);
        layout->setContentsMargins(5, 5, 5, 5);
        layout->setSpacing(3);
    }
    allServices = Database::getAllServise();
    //qDebug() << "Услуг:" << allServices.size();
    for (Servise* s : allServices) {
        QCheckBox* cb = new QCheckBox(s->GetName() + " — " + QString::number(s->GetPrise()) + " ₽");
        ui->servicesGroup->layout()->addWidget(cb);
        servicesCheckBox.append(cb);
        connect(cb,&QCheckBox::checkStateChanged,this,&BookingDialog::updateInfo);
    }
}
BookingDialog::~BookingDialog()
{
    delete ui;
}



