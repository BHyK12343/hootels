#include "mainwindow.h"
#include <QSqlDatabase>
#include <QDebug>
#include "database.h"
#include <QApplication>
#include "guest.h"
#include "logindialog.h"
#include"room.h"
#include"booking.h"
#include"servise.h"
#include <QImageReader>
class Database;
class Guest;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << QSqlDatabase::drivers();
    if(!Database::connect()) return -1;
    if(!Database::createTables()) return -1;
    LoginDialog LoginDlg;
    if(LoginDlg.exec()!=QDialog::Accepted){
        return 0;
    }
    Guest* user=LoginDlg.getNameUser();
    if(!user){
        return 0;
    }
    qDebug()<<"вошел"<<user->getName();
    qDebug() << "Поддерживаемые форматы:" << QImageReader::supportedImageFormats();

    /*int newId = Database::registerNewGuest(g);
    qDebug() << "Зарегистрирован, id =" << newId;*/


    MainWindow w(user);
    w.show();
    return QApplication::exec();
}
