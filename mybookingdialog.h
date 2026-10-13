#ifndef MYBOOKINGDIALOG_H
#define MYBOOKINGDIALOG_H
#include<QDialog>
#include"guest.h"
#include"room.h"
#include"booking.h"
#include <QDialog>
#include"database.h"

namespace Ui {
class mybookingdialog;
}

class mybookingdialog : public QDialog
{
    Q_OBJECT

public:
    explicit mybookingdialog(Guest* user,QWidget *parent = nullptr);
    ~mybookingdialog();


private:
    Ui::mybookingdialog *ui;
    Guest* currentUser;
    QList<Booking*> booking;
private slots:
    void onCloseClicked();
private:
    void loadBooking();
    void fillBookingTable();
};

#endif // MYBOOKINGDIALOG_H
