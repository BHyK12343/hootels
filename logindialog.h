#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include "guest.h"
#include <QDialog>
#include "database.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private:
    Ui::LoginDialog *ui;
    Guest* loginGuest;
private slots:
    void onLoginClicked();
    void onRegisterClicked();
    void onExitClicked();
public:
    Guest* getNameUser() const ;
};

#endif // LOGINDIALOG_H
