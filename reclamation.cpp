#include "reclamation.h"
#include <QDebug>

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
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Date"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Etat"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Contenu"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Categorie"));


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

Reclamation Reclamation::GetOneByID(int id)
{
    Reclamation reclamation;
    QSqlQuery query;
            query.prepare("SELECT * FROM reclamation WHERE id_rec = :id");
            query.bindValue(":id", id);

            // Execute the query
            if (query.exec() && query.next()) {
                // Assuming Reclamation class has id and description as data members
                reclamation.set_id(query.value("id_rec").toInt());
                reclamation.set_etat(query.value("etat").toString());
                reclamation.set_datea(query.value("date_a").toDate());
                reclamation.set_contenu(query.value("contenu").toString());
                reclamation.set_categorie(query.value("categorie").toString());
            } else {
                   qDebug() << "error";


}
return reclamation;
}

 QSqlQueryModel * Reclamation::recherche(QString cls)
 {
     QSqlQueryModel *model=new QSqlQueryModel();
        model->setQuery("SELECT * FROM reclamation WHERE ( id_rec LIKE '%"+cls+"%' OR etat LIKE '%"+cls+"%' OR categorie LIKE '%"+cls+"%' ) ");
        return model ;
 }

 QSqlQueryModel * Reclamation::Tri(QString cls,QString colonne)
 {
     QSqlQueryModel *model=new QSqlQueryModel();
        model->setQuery("SELECT * FROM reclamation ORDER BY " + colonne + " " + cls);
        return model;
 }









