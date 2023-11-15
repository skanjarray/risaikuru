#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "reclamation.h"
#include "connection.h"
#include <QMessageBox>
#include "qrcode.h"
#include <QtSvg/QSvgRenderer>
#include <fstream>
#include <QPainter>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QtCharts>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setQR();
private slots:


    void on_update_iskander_clicked();

    void on_add_iskander_clicked();

    void on_delete_iskander_clicked();

    void on_pushButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButtonTrier_clicked();



    void on_pushButtonPdfrec_clicked();

    void on_pushButtonStat_clicked();

private:
    Ui::MainWindow *ui;
    Reclamation rmp;
};
#endif // MAINWINDOW_H
