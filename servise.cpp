#include "servise.h"
#include<QString>
#include<QDate>
Servise::Servise():id(0),prise(0.0){}


Servise::Servise(int id,const QString& nameServise,QDate in_servise,QDate out_servise,double prise,const QString& comment):id(id), comment(comment),
        nameServise(nameServise),in_servise(in_servise),out_servise(out_servise)
                    {
    if(prise>0){
        this->prise=prise;
        }
}
QString Servise::GetName()const {return this->nameServise;}
QDate Servise::GetIn()const{return this->in_servise;}
QDate Servise::GetOut() const{return this->out_servise;}
double Servise::GetPrise() const{return this->prise;}
int Servise::GetId() const{return this->id;}
QString Servise::GetComment()const{return this->comment;}
void Servise::SetIn(QDate in_servise){this->in_servise=in_servise;}
void Servise::SetOut(QDate out_servise){this->out_servise=out_servise;}
void Servise::SetPrise(double prise){this->prise=prise;}


