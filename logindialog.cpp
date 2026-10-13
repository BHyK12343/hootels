#include "logindialog.h"
#include "ui_logindialog.h"
#include "guest.h"
#include <QMessageBox>
#include "registerdialog.h"
class Guest;
LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
    ,loginGuest(nullptr)
{
    ui->setupUi(this);

    connect(ui->LoginButton,&QPushButton::clicked,this,&LoginDialog::onLoginClicked);
    connect(ui->registrButton,&QPushButton::clicked,this,&LoginDialog::onRegisterClicked);
    connect(ui->exitButton,&QPushButton::clicked,this,&LoginDialog::onExitClicked);

}
Guest* LoginDialog::getNameUser() const {
    return loginGuest;
}
void LoginDialog::onLoginClicked(){
    QString login=ui->LoginEdit->text();
    QString password=ui->PasswordEdit->text();
    if(login.isEmpty()){
        QMessageBox::warning(this, "Ошибка", "Введите логин");
        return;
    }
    if(login.isEmpty()){
        QMessageBox::warning(this, "Ошибка", "Введите пароль");
        return;
    }
    Guest *g=Database::checklogin(login,password);
    if(g){
        loginGuest=g;
        accept();
    }
    else{
        QMessageBox::warning(this,"Ошибка","не верный логин или пароль");
    }
}
void LoginDialog::onRegisterClicked()
{
    RegisterDialog dlg(this);
    if(dlg.exec()==QDialog::Accepted){
        QMessageBox::information(this,"","теперь войдите");
    }
}
void LoginDialog::onExitClicked()
{
    reject();
}
LoginDialog::~LoginDialog()
{
    delete ui;
}
