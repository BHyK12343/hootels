#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QList>
#include <QMainWindow>
#include"room.h"
#include"guest.h"
class Room;
class Servise;
class Guest;
class Booking;
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Guest* user, QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Guest* currentUser;
    Ui::MainWindow *ui;
    QList<Room*> rooms;
    QList<Servise*> servise;
    QList<Guest*> guests;
    QList<Booking*> bookings;
private slots:
    void onRefreshClicked();
    void onExitClicked();
    void onFilterChanged(int index);
    void onMyBookingCkicked();
    void onRoomDoubleClicked(int row,int column);
private:
    void loadRooms();
    void fillRoomsTable();
    void applyFilter(int index);

};
#endif // MAINWINDOW_H
