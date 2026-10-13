#ifndef ROOMDIALOG_H
#define ROOMDIALOG_H
#include<QMessageBox>
#include<QPixmap>
#include <QDialog>
#include"room.h"
#include"guest.h"
namespace Ui {
class roomdialog;
}

class roomdialog : public QDialog
{
    Q_OBJECT

public:
    explicit roomdialog(Room* room,Guest* user ,QWidget *parent=nullptr);
    ~roomdialog();

private slots:
    void onBookClicked();
    void onCloseClicked();
private:
    Ui::roomdialog *ui;
    Room* currentRoom;
    Guest* currentUser;
};

#endif // ROOMDIALOG_H
