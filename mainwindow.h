#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "reclamation.h"
#include "connection.h"
#include <QMessageBox>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:


    void on_update_iskander_clicked();

    void on_add_iskander_clicked();

    void on_delete_iskander_clicked();

private:
    Ui::MainWindow *ui;
    Reclamation rmp;
};
#endif // MAINWINDOW_H
