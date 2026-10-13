#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "guest.h"
#include "database.h"
#include<QMessageBox>
#include<QString>
RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    connect(ui->okButton, &QPushButton::clicked,
            this, &RegisterDialog::onOkClicked);
    connect(ui->cancelButton, &QPushButton::clicked,
            this, &RegisterDialog::onCancelClicked);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::onOkClicked(){
    QString name =ui->nameEdit->text();
    QString email=ui->emailEdit->text();
    QString number=ui->numberEdit->text();
    QString login=ui->loginEdit->text();
    QString password=ui->passwordEdit->text();
    QString number_card=ui->number_cardLabel->text();
    if(name.isEmpty()||login.isEmpty()||password.isEmpty()){
        QMessageBox::warning(this,"ошибка","Заполните все поля");
        return;
    }
    Guest* exiting=Database::getGuestLogin(login);
    if(exiting){
        QMessageBox::warning(this,"ошибка","логин занят");
        return;
    }
    Guest *g=new Guest();
    g->setEmail(email);
    g->setLogin(login);
    g->setName(name);
    g->setNumber(number);
    g->setPassword(password);
    g->setNumberCard("");
    g->setNumberRoom(0);
    g->setNumberCard(number_card);
    int id=Database::registerNewGuest(g);
    if(id<=0){
        QMessageBox::warning(this,"ошибка","не удалось зарегестрироваться");
        return;
    }

    QMessageBox::information(this, "Успех", "Регистрация прошла успешно");
    accept();
}
void RegisterDialog::onCancelClicked(){
    reject();
}
