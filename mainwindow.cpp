#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(rmp.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_update_iskander_clicked()
{
    int id_upt=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toInt();
    QString categorie=ui->line_categorie->text();
    QString contenu=ui->line_contenu->text();
    QString etat=ui->line_etat->text();
    QDate d=ui->date->date();

    Reclamation R(id_upt,categorie,etat,contenu,d);



    bool test=R.modifier(id_upt);
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("update successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView->setModel(rmp.afficher());

    }
    else
       { QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("update failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel); }
}

void MainWindow::on_add_iskander_clicked()
{
    QString categorie=ui->line_categorie->text();
    QString contenu=ui->line_contenu->text();
    QDate d=ui->date->date();



    Reclamation R(1,categorie,"en cours",contenu,d);

    bool test=R.ajouter();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("ajout successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView->setModel(rmp.afficher());


}
    else
       { QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("ajout failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel); }




}

void MainWindow::on_delete_iskander_clicked()
{
    bool i;
    int id_del;
    id_del=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toInt();

    i=rmp.supprimer(id_del);
    if(i)
    {
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("delete successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView->setModel(rmp.afficher());

    }
    else
       { QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("delete failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel); }
}
