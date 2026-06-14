#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "universitysystem.h"

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
    void on_btnAddStudent_clicked();
    void on_btnAddDorm_clicked();
    void on_btnAssignStudent_clicked();
    void on_btnRemoveStudent_clicked();
    void on_btnUpdateMenu_clicked();
    void on_btnShowMenu_clicked();
    void refreshTables();

private:
    Ui::MainWindow *ui;
    UniversitySystem system;
    QString savedMeal; //
};

#endif // MAINWINDOW_H