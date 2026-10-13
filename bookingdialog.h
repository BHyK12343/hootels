#ifndef BOOKINGDIALOG_H
#define BOOKINGDIALOG_H
#include <QDialog>
#include <QCheckBox>
#include "guest.h"
#include "room.h"
#include "servise.h"

namespace Ui {
class BookingDialog;
}

class BookingDialog : public QDialog
{
    Q_OBJECT
public:
    explicit BookingDialog(Room* room, Guest* user, QWidget *parent = nullptr);
    ~BookingDialog();
private slots:
    void onConfirmClicked();
    void onCancelClicked();
    void onDateChanged();
private:
    Ui::BookingDialog *ui;
    Room* currentRoom;
    Guest* currentUser;
    QList<Servise*> allServices;
    QList<QCheckBox*> servicesCheckBox;
    void loadServices();
    double getServicesCost() const;
    int getNights();
    double calculateTotal();
    void updateInfo();
};

#endif // BOOKINGDIALOG_H
