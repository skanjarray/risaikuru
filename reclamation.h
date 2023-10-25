#ifndef RECLAMATION_H
#define RECLAMATION_H
#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Reclamation
{
    int id_rec;
    QString categorie;
    QString etat;
    QString contenu;
    QDate date_a;

public:
    //Constructeurs
    Reclamation();
    Reclamation(int, QString,QString,QString,QDate);
    //Getters
    int get_id(){return id_rec;}
    QString get_categorie(){return categorie;}
    QString get_etat(){return etat;}
    QString get_contenu(){return contenu;}
    QDate get_datea(){return date_a;}

    //Setters
    void set_id(int a){id_rec=a;}
    void set_categorie(QString a){categorie=a;}
    void set_etat(QString b){etat=b;}
    void set_contenu(QString c){contenu=c;}
    void set_datea(QDate d){date_a=d;}
   //other functions
    QSqlQueryModel * afficher();
    bool ajouter();
    bool supprimer(int);
    bool modifier(int);



};

#endif // RECLAMATION_H
