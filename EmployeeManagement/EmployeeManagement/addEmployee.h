#ifndef ADDEMPLOYEE_H
#define ADDEMPLOYEE_H

#include <QDialog>
#include <QString>
#include <QPushButton>
#include <QPainter>
#include <QFile>
#include <QMessageBox>
#include <QSqlQuery>
#include "myPushButton.h"
#include <QTimer>
class MainScene;
namespace Ui {
class addasset;
}

class AddEmployee : public QDialog
{
    Q_OBJECT
public:
    explicit AddEmployee(QWidget *parent = nullptr);
signals:
    void back();
    void add_successfully();

public:
    void clear();
private:
    Ui::addasset *ui;
    bool check();
    int  usable;
    QString name, phonenumber, edubkg, dept_name, jobtitle, sex;
    double salary;

    int age;
    MyPushButton *btnBack, *btnConfirm;
    void setBtn();
public:
    void set_lineEdit();
    void set_combBox();
    void paintEvent(QPaintEvent*);

};

#endif // ADDEMPLOYEE_H
