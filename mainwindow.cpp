#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QMessageBox>
#include"database.h"
#include "roomdialog.h"
#include"mybookingdialog.h"
MainWindow::MainWindow(Guest *user, QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
    ,currentUser(user)
{
    ui->setupUi(this);
    //ui->filterCombo->addItem("Все");
    //ui->filterCombo->addItem("Свободные");
    //ui->filterCombo->addItem("Занятые");
    connect(ui->myBookingButton, &QPushButton::clicked,this, &MainWindow::onMyBookingCkicked);
    connect(ui->refreshButton,&QPushButton::clicked,this,&MainWindow::onRefreshClicked);
    connect(ui->exitButton,&QPushButton::clicked,this,&MainWindow::onExitClicked);
    connect(ui->filterCombo,QOverload<int>::of(&QComboBox::currentIndexChanged),this,&MainWindow::onFilterChanged);
    connect(ui->roomsTable,&QTableWidget::cellDoubleClicked,this,&MainWindow::onRoomDoubleClicked);
    loadRooms();
    fillRoomsTable();
    setWindowTitle("Отель");
}
void MainWindow::onRefreshClicked() {
    loadRooms();
    fillRoomsTable();
    QMessageBox::information(this,"Обновленно","данные обновленны");
}
void MainWindow::loadRooms() {
    rooms=Database::getAllRoom();
}
void MainWindow::fillRoomsTable() {
    ui->roomsTable->setRowCount(0);
    for(Room* r:rooms){
        int row=ui->roomsTable->rowCount();
        ui->roomsTable->insertRow(row);
        ui->roomsTable->setItem(row,0,new QTableWidgetItem(QString::number(r->getNumberRoom())));
        ui->roomsTable->setItem(row,1,new QTableWidgetItem((r->getNameRoom())));
        ui->roomsTable->setItem(row,2,new QTableWidgetItem(QString::number(r->getFloor())));
        ui->roomsTable->setItem(row,3,new QTableWidgetItem(QString::number(r->getPrise())));
        ui->roomsTable->setItem(row,4,new QTableWidgetItem((r->getStatus()?"Занят":"Свободен")));

    }
}
void MainWindow::applyFilter(int index) {
    ui->roomsTable->setRowCount(0);
    for(Room* r:rooms){
        if(index==1 && r->getStatus()) continue;
        if(index==2&& !r->getStatus()) continue;
        int row=ui->roomsTable->rowCount();
        ui->roomsTable->insertRow(row);
        ui->roomsTable->setItem(row,0,new QTableWidgetItem(QString::number(r->getNumberRoom())));
        ui->roomsTable->setItem(row,1,new QTableWidgetItem((r->getNameRoom())));
        ui->roomsTable->setItem(row,2,new QTableWidgetItem(QString::number(r->getFloor())));
        ui->roomsTable->setItem(row,3,new QTableWidgetItem(QString::number(r->getPrise())));
        ui->roomsTable->setItem(row,4,new QTableWidgetItem((r->getStatus()?"Занят":"Свободен")));
    }
}
void MainWindow::onExitClicked()
{
    close();
}
void MainWindow::onMyBookingCkicked()
{
    mybookingdialog dlg(currentUser,this);
    dlg.exec();
}
void MainWindow::onFilterChanged(int index)
{
    applyFilter(index);
}
void MainWindow::onRoomDoubleClicked(int row,int column){
    Q_UNUSED(column);
    if(row<0||row>=rooms.size()) return;
    Room*r=rooms.at(row);
    roomdialog dlg(r,currentUser,this);
    dlg.exec();
}
MainWindow::~MainWindow()
{
    delete ui;
}
