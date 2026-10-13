#include "roomdialog.h"
#include "ui_roomdialog.h"
#include "roomdialog.h"
#include <QPixmap>
#include <QMessageBox>
#include<QString>
#include<QDir>
#include <QImageReader>
#include"bookingdialog.h"
roomdialog::roomdialog(Room* room,Guest* guest,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::roomdialog)
    ,currentRoom(room)
    ,currentUser(guest)

{

    ui->setupUi(this);
    ui->nameLabel->setText("Название:"+currentRoom->getNameRoom());
    ui->commentLabel->setText("Описание:"+currentRoom->getComment());
    ui->areaLabel->setText("Площадь"+QString::number(currentRoom->getArea())+" кв.м.");
    ui->floorLabel->setText("Этаж:"+QString::number(currentRoom->getFloor()));
    ui->priceLabel->setText("Стоимость:"+QString::number(currentRoom->getPrise())+" р");
    QImageReader reader(currentRoom->getImagePath());
    qDebug() << "Формат:" << reader.format();
    qDebug() << "Ошибка:" << reader.errorString();
    qDebug() << "Существует:" << QFile::exists(currentRoom->getImagePath());
    QPixmap pix(currentRoom->getImagePath());
    if(!pix.isNull()){
        ui->label_5->setPixmap(pix);
        ui->label_5->setScaledContents(true);
    }
    connect(ui->bookButton,&QPushButton::clicked,this,&roomdialog::onBookClicked);
    connect(ui->closeButton,&QPushButton::clicked,this,&roomdialog::onCloseClicked);
    qDebug() << "Текущая папка:" << QDir::currentPath();
    qDebug() << "Путь к фото:" << currentRoom->getImagePath();
    qDebug() << "Размер метки:" << ui->label_5->size();
    qDebug() << "Pixmap пустой:" << ui->label_5->pixmap().isNull();
}

void roomdialog::onBookClicked(){
    BookingDialog dlg(currentRoom,currentUser,this);
    if(dlg.exec()==QDialog::Accepted){
        accept();
    }
}
void roomdialog::onCloseClicked(){
    reject();
}
roomdialog::~roomdialog()
{
    delete ui;
}
