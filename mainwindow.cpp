#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>

using qrcodegen::QrCode;
using qrcodegen::QrSegment;

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
    QString etat=ui->comboBoxEtatRec->currentText();
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



    Reclamation R(1,categorie,"En cours",contenu,d);

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

void MainWindow::on_pushButton_clicked()
{
    int id=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toInt();
    Reclamation r = rmp.GetOneByID(id);
    QString reference = QString::number(id) + " | " + r.get_etat() + " | " + r.get_datea().toString() + " | "
            + r.get_contenu() + " | " + r.get_categorie();
    QByteArray ba = reference.toLocal8Bit();
    const char *c_str2 = ba.data();
    const QrCode qr = QrCode::encodeText(/*std::to_string(reference).c_str()*/c_str2, QrCode::Ecc::LOW);
    std::ofstream myfile;
    myfile.open ("qrcode.svg") ;
    myfile << qr.toSvgString(1);
    myfile.close();
    QSvgRenderer svgRenderer(QString("qrcode.svg"));
    QPixmap pix( QSize(120, 120) );
    QPainter pixPainter( &pix );
    svgRenderer.render( &pixPainter );
    ui->label_QR->setPixmap(pix);
    bool inputsFocus = ui->label_QR->hasFocus();
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    ui->tableView->setModel(rmp.recherche(arg1));

}

void MainWindow::on_pushButtonTrier_clicked()
{
    QString champ = "id_rec" ;
       QString order = "asc";

      if (ui->comboBoxColonne->currentText().compare("Etat") == 0)
       {
           champ = "etat";
       }
       else if (ui->comboBoxColonne->currentText().compare("Date") == 0)
       {
           champ = "date_a";
       }
       if (ui->comboBoxOrder->currentText().compare("Descendant") == 0 )
       {
           order = "desc";
       }

       ui->tableView->setModel(rmp.Tri(order,champ));
}


void MainWindow::on_pushButtonPdfrec_clicked()
{
    QPdfWriter pdf("reclamations.pdf");
                  QPainter painter(&pdf);
                  int i = 4000;
                  painter.setPen(Qt::red);
                  painter.setFont(QFont("Arial", 30));
                  painter.drawText(2800,1200,"Liste des Reclamations");
                  painter.setPen(Qt::black);
                  painter.setFont(QFont("Arial", 50));
                  painter.drawRect(1500,200,7300,2600);
                  painter.drawRect(0,3000,9600,500);
                  painter.setFont(QFont("Arial", 9));
                  painter.drawText(1300,3300,"ID");
                  painter.drawText(2600,3300,"Date");
                  painter.drawText(4500,3300,"Etat");
                  painter.drawText(6000,3300,"Categorie");
                  painter.drawText(7500,3300,"Contenu");

                  QSqlQuery query;
                  query.prepare("select * from reclamation");
                  query.exec();
                  while (query.next())
                  {
                      painter.drawText(1300,i,query.value(0).toString());
                      painter.drawText(2600,i,query.value(1).toString());
                      painter.drawText(4500,i,query.value(2).toString());
                      painter.drawText(6000,i,query.value(3).toString());
                      painter.drawText(7500,i,query.value(4).toString());
                      i = i +500;
                  }

                  int reponse = QMessageBox::question(this, "Génerer PDF", "Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                  if (reponse == QMessageBox::Yes)
                  {
                      QDesktopServices::openUrl(QUrl::fromLocalFile("reclamations.pdf"));

                      painter.end();
                  }
                  if (reponse == QMessageBox::No)
                  {
                      painter.end();
                  }
}

void MainWindow::on_pushButtonStat_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
          model->setQuery("SELECT etat FROM reclamation WHERE etat='En cours' ");
          float count1=model->rowCount();
          model->setQuery("SELECT etat FROM reclamation WHERE etat='Fini' ");
          float count2=model->rowCount();

          float total=count1+count2;

                  QPieSeries *series = new QPieSeries();

                  series->append("Gestion1",count1);
                  series->append("Gestion2",count2);


                  if (count1!=0)
                  {QPieSlice *slice = series->slices().at(0);
                      slice->setLabel("En cours "+QString("%1%").arg(100*slice->percentage(),3,'f',1));
                      slice->setLabelVisible();
                      slice->setPen(QPen(Qt::black));}
                  if ( count2!=0)
                  {
                      // Add label, explode and define brush for 2nd slice
                      QPieSlice *slice1 = series->slices().at(1);
                      //slice1->setExploded();
                      slice1->setLabel("Fini "+QString("%1%").arg(100*slice1->percentage(),3,'f',1));
                      slice1->setLabelVisible();
                      slice1->setBrush(QColor(Qt::cyan));
                  }




                  // Create the chart widget
                  QChart *chart = new QChart();
                  // Add data to chart with title and hide legend
                  chart->addSeries(series);
                  chart->setTitle("Totale "+ QString::number(total));

                  // Used to display the chart
                  QChartView *chartView = new QChartView(chart);
                  chartView->setRenderHint(QPainter::Antialiasing);
                  chartView->resize(1000,500);


                  chart->legend()->hide();
                  chartView->show();
}
