#ifndef SERVISE_H
#define SERVISE_H
#include<QString>
#include<QDate>
class Servise
{
private:
    const QString nameServise;
    QDate in_servise;
    QDate out_servise;
    double prise;
    int id;
    const QString comment;
public:
    Servise();
    Servise(int id,const QString& nameServise,QDate in_servise,QDate out_servise,double prise,const QString& comment);
    QString GetName()const;
    QDate GetIn()const;
    QDate GetOut() const;
    double GetPrise() const;
    int GetId() const;
    QString GetComment()const;
    void SetIn(QDate in_servise);
    void SetOut(QDate out_servise);
    void SetPrise(double prise);
};

#endif // SERVISE_H
