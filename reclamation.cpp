#include "reclamation.h"

Reclamation::Reclamation()
{

}
Reclamation::Reclamation(int a, QString b,QString c,QString d,QDate e)
{
    id_rec=a;
    categorie=b;
    etat=c;
    contenu=d;
    date_a=e;

}
QSqlQueryModel * Reclamation::afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM reclamation ORDER by id_rec ASC");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_rec"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("catrgorie"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("etat"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("contenu"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("date_a"));


    return model;
}
bool Reclamation::ajouter()
{
    QSqlQuery query;
    //QString res = QString::number(id_rec);
    query.prepare("INSERT INTO reclamation(categorie,etat,contenu,date_a)""VALUES (:categorie,:etat,:contenu,:date_a)");
    //query.bindValue(":id_rec",res);
    query.bindValue(":categorie",categorie);
    query.bindValue(":etat",etat);
    query.bindValue(":contenu",contenu);
    query.bindValue(":date_a",date_a);

    return query.exec();
}
bool Reclamation::supprimer(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("DELETE FROM reclamation WHERE id_rec= :id");
    query.bindValue(":id",res);
    return query.exec();
}
bool Reclamation::modifier(int id)
{
    QSqlQuery query;
    //QString res=QString::number(id);
    query.prepare("UPDATE reclamation SET categorie=:categorie,etat=:etat,contenu=:contenu,date_a=:date_a WHERE id_rec=:id");
    query.bindValue(":categorie",categorie);
    query.bindValue(":etat",etat);
    query.bindValue(":contenu",contenu);
    query.bindValue(":date_a",date_a);

    query.bindValue(":id",id);

    return query.exec();
}






